#include "import.h"
#include <QDebug>
#include <QSqlQuery>
#include <QxtStdio>
#include <QXmlFormatter>
#include <QBuffer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QSqlError>
#include <QTextStream>
#define dDebug() qDebug()<<qPrintable(QString(state->deepnes, '\t'))

#define eDebug() qDebug()<<"."<<qPrintable(QString(state->deepnes-1, '\t'))




Receivers::Row::Row(StateEngine * s,Analyser::Table* t,Row*p)
{
    parent=p;
    state=s;
    table=t;
    delegate=0;
    qualified=false;
}

Receivers::Row::~Row()
{
    qualify();
}
void Receivers::Row::qualify()
{
    if(qualified)
        return;
    if(!parent)
        return;

    foreach(Analyser::Key* key, table->keys)
    {

        qualified_keys<<key;
        if(key->type==Analyser::PrimaryKey)
        {
            dDebug()<<qPrintable(QString()+"PRIMARY");
        }
        else if(key->type==Analyser::IndexKey)
        {
            continue;
        }
        else if(key->type==Analyser::UniqueKey)
        {
            dDebug()<<qPrintable(QString()+"UNIQUE");
        }

        bool qualifiedkey=true;
        foreach(Analyser::Field* field, key->fields)
        {
            dDebug()<<qPrintable("\t> "+field->name);

            if(member_fields.contains(field->name))
            {
                dDebug()<<"\t  by member";

            }
            else if(parent->canQualify(field->name))
            {
                dDebug()<<"\t  by parent";
            }
            else if(sub_eval_result.contains(field->name))
            {
                dDebug()<<"\t  by sub";
            }


            else
            {
                dDebug()<<"\t  X no";
                qualifiedkey=false;
            }
        }
        if(qualifiedkey && !qualified)
        {
            qualificator=key;
            qualified=true;
        }
    }
}

bool Receivers::Row::canQualify(QString fieldname)
{
    if(member_fields.contains(fieldname))
        return true;

    if(!qualified)
        return false;

    foreach(Analyser::Key* key, table->keys)
    {
        foreach(Analyser::Field* field, key->fields)
        {
            if(field->name==fieldname)
                return true;
        }
    }

    return false;

}


void Receivers::Row::startElement ( const QXmlName & name )
{
    if(delegate)
    {
        delegate->startElement(name);
        return;
    }

    if(parent)
        qualify();

    //try plural
    QString ndel=Analyser::table_plural(name.localName(state->namePool));
    foreach(Analyser::Table* table, state->scheme)
    {
        if (table->name==ndel)
        {
            delegate=new Row(state,table,this);
            dDebug()<<qPrintable("#"+ndel);
            state->deepnes++;
            return;
        }
    }



    //try as is
    ndel=name.localName(state->namePool);

    foreach(Analyser::Table* table, state->scheme)
    {
        if (table->name==ndel)
        {
            delegate=new Row(state,table,this);
            dDebug()<<qPrintable("#"+ndel);
            state->deepnes++;
            return;
        }
    }



    dDebug()<<"cannot find any delegate for"<<ndel;
    abort();
}


/**
    This is most of Stage1 where we ensure that all tables are qualified (a row can be identified)
    This function is called for each attribute, means for each column/field
*/
void Receivers::Row::attribute ( const QXmlName & name, const QStringRef & value )
{
    if(delegate)
    {
        delegate->attribute(name,value);
        return;
    }


    QString fieldname=name.localName(state->namePool);



    dDebug()<<qPrintable("."+fieldname);
    bool routed=false;
    foreach(Analyser::Field* field, table->fields)
    {
        if (field->name==fieldname)
        {
            dDebug()<<" => member";
            routed=true;
            break;
        }
    }

    foreach(Analyser::Key* key, table->keys)
    {

        foreach(Analyser::Field* field, key->fields)
        {
            if (field->name==fieldname)
            {
                dDebug()<<" => partial key";
                break;
            }
        }
    }

    if(routed)
    {
        member_fields[fieldname]=value.toString();
    }
    else
    {
            dDebug()<<" X no relation found";
    }

}

void Receivers::Row::endElement ()
{
    if(delegate)
    {
        if (delegate->hasDelegate())
        {
            delegate->endElement();
        }
        else
        {
            sub_eval_result=delegate->finalyEval();
            state->deepnes--;
            qualify();
            state->deepnes++;
            delete delegate;
            state->deepnes--;
            delegate=0;
        }
        return;
    }
}


bool Receivers::Row::hasDelegate()
{
    return delegate;
}



/**
this is stage2. It is usually called after stage1 has run unless it is called reverse for a parent relation.
this is why we call qualify() at the beginning.

*/
QHash<QString,QString> Receivers::Row::finalyEval(bool reverse)
{
    qualify();
    eDebug()<<"=====eval====";
    if(!qualified)
    {
        qCritical(qPrintable(table->name+" is not qualified and cannot be used for stage2 evaluation."));
        abort();
    }



    QStringList keys;
    QStringList values;


    /** 
        we propably want to include fields as well are generated by subnodes (1:N), 
        but not if this is a reverse evaluation where we dont care anyway.
    */
    if(delegate && !reverse && sub_eval_result.isEmpty())
        sub_eval_result=delegate->finalyEval();


    /** walk through the qualificator key and find all values for the key*/

    foreach(Analyser::Field* field, qualificator->fields)
    {
        keys<<field->name;
        eDebug()<<field->name;


        /** 
            easiest case:  it's just an attribute
        */
        if(member_fields.contains(field->name))
        {
            values<<member_fields[field->name];
            eDebug()<<"\t  by member";
        }
        /** 
            a subnode has generated the key to qualify this field. 
            this is usually an 1 to N relation where the parent can have multiple rows like this.
        */
        else if(sub_eval_result.contains(field->name))
        {
            eDebug()<<"\t  by sub";
            values<<sub_eval_result[field->name];
        }
        /** 
            a parent node has the field i need to insert this row.  
            this is an N:1  relation where this row can be linked to many different parents.
        */
        else if(parent->canQualify(field->name))
        {
            eDebug()<<"\t  by parent";
            eDebug()<<"\t  using reverse double eval. hope that doesn't break";
            state->deepnes+=2;
            QHash<QString,QString> e= parent->finalyEval(true);
            values<<e[field->name];
            state->deepnes-=2;
        }
        /**
            well this isn't supposed to happen
        */
        else
        {
            eDebug()<<"\t  X no";
            qCritical("stage1 and stage2 disagree");
            abort();
        }
    }


    /** built my sql strings from the keys */
    QString sqlk;
    QString sqlv;
    QString sqlu;
    QString sqls;

    for(int i=0;i<keys.count();i++)
    {
        sqlk+=" `"+keys.at(i)+"` ,";
        sqlv+=" '"+values.at(i)+"' ,";
        sqlu+=" `"+keys.at(i)+"` = '"+values.at(i)+"' ,";
        sqls+=" `"+keys.at(i)+"` = '"+values.at(i)+"' and";
    }


    /** also include all member fields */
    foreach(QString k,member_fields.keys())
    {
        if(keys.contains(k))
            continue;
        sqlk+=" `"+k+"` ,";
        sqlv+=" '"+member_fields[k]+"' ,";
        sqlu+=" `"+k+"` = '"+member_fields[k]+"' ,";
    }


    /** get all fields from the subnode that might be relevant */

    foreach(QString k,sub_eval_result.keys())
    {
        if(keys.contains(k))
            continue;


        foreach(Analyser::Field * field,table->fields)
        {
            if(field->name==k)
            {
                sqlk+=" `"+k+"` ,";
                sqlv+=" '"+sub_eval_result[k]+"' ,";
                sqlu+=" `"+k+"` = '"+sub_eval_result[k]+"' ,";
            }
        }
    }

    sqlk.chop(1);
    sqlv.chop(1);
    sqlu.chop(1);
    sqls.chop(3);



    /** This is just for user feedback (insert or update)*/
    QSqlQuery queryus("select * from "+table->name+" where "+sqls,QSqlDatabase::database("vengeance"));
    if(!queryus.exec())
    {
        qDebug()<<"select * from "+table->name+" where "+sqls;
        qDebug()<<queryus.lastError().text();
        abort();
    }
    bool willInsertNewRow=(queryus.size()==0);

    /** insert or update */

    QString sql=" replace into `"+table->name+"` ( "+sqlk+" ) "
                " values ( "+sqlv+" )"; 
                
                
    QSqlQuery queryi(sql,QSqlDatabase::database("vengeance"));
    if(!queryi.exec())
    {
        qDebug()<<sql;
        qDebug()<<queryi.lastError().text();
        abort();
    }

    /** and get the entire row back, so we can feed parents with our generated or found values*/

    QHash<QString,QString> r;
    QSqlQuery querys("select * from "+table->name+" where "+sqls ,QSqlDatabase::database("vengeance"));
    if(!querys.exec())
    {
        qDebug()<<"select * from "+table->name+" where "+sqls;
        qDebug()<<querys.lastError().text();
        abort();
    }
    querys.next();

    foreach(Analyser::Field* field,table->fields)
    {
        r[field->name]=querys.record().value(field->name).toString();
    }


    if(willInsertNewRow)
    {
        state->uf_inserted[table->name]++;

    }
    else
    {
        state->uf_updated[table->name]++;
    }
    
    eDebug()<<"============";
    return r;
}




Import::Import(QList<Analyser::Table *> scheme ):QObject()
{   
    m_scheme=scheme;

}


void Import::import(QByteArray data)
{
    QBuffer io(&data);
    io.open(QBuffer::ReadOnly);

    foreach(Analyser::Table* table, m_scheme)
    {
        io.reset();
        query.bindVariable("stdin",&io);
        query.setQuery("declare variable $stdin external; doc($stdin)/"+table->name+"/*");

        Receivers::StateEngine st;
        st.deepnes=0;
        st.namePool=query.namePool();
        st.scheme=m_scheme;
        Receivers::Row recvr(&st,table);
        query.evaluateTo(&recvr);

        foreach(QString k,st.uf_updated.keys())
        {
            QTextStream(stdout)<<"updated "<<st.uf_updated[k]<<" "<<k<<endl;
        }
        foreach(QString k,st.uf_inserted.keys())
        {
            QTextStream(stdout)<<"added "<<st.uf_inserted[k]<<" new "<<k<<endl;
        }
    }
}


