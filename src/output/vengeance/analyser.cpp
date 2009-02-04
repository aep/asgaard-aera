#include "analyser.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QStringList>
#include <QXmlStreamWriter>

Analyser::Analyser(QObject * parent):QObject(parent)
{
    
}

QList<Analyser::Table *>  Analyser::analyse()
{
    QSqlQuery qst("show tables;",QSqlDatabase::database("vengeance") );
    while (qst.next()) 
    {
        QSqlQuery stc ("show create table "+qst.value(0).toString(),QSqlDatabase::database("vengeance") );
        while (stc.next())
        {
            parseShowCreate(stc.value(1).toString());
        }
    }
    return tables;
}



void Analyser::parseShowCreate(QString sc)
{

    Table * table= new Table;

    bool expectmorefields=false;

    foreach(QString line,sc.split("\n"))
    {
        line=line.trimmed();
        if(line.toLower().startsWith("create"))
        {
            foreach(QString linesub,line.split(" "))
            {
                linesub=linesub.trimmed();
                if(linesub.toLower()=="create")
                    continue;
                if(linesub.toLower()=="table")
                    continue;


                table->name=linesub.replace("`","");
                break;
            }
            expectmorefields=true;
            continue;
        }
        else if(line.toLower().startsWith(")"))
        {
            expectmorefields=false;
            break;
        }
        else if(line.toLower().startsWith("unique") ||  line.toLower().startsWith("primary") || line.toLower().startsWith("key"))
        {

            Key *key=new Key;
            key->type=UnknownKeyType;

            foreach(QString linesub,line.split("(").at(0).split(" "))
            {
                linesub=linesub.trimmed();
                if(linesub.toLower()=="primary")
                {
                    if(key->type==UnknownKeyType)
                        key->type=PrimaryKey;
                    continue;
                }
                if(linesub.toLower()=="unique")
                {
                    if(key->type==UnknownKeyType)
                        key->type=UniqueKey;
                    continue;
                }
                if(linesub.toLower()=="key")
                {
                    if(key->type==UnknownKeyType)
                        key->type=IndexKey;
                    continue;
                }

                break;
            }

            foreach(QString keyfield,line.split(")").at(0).split("(").at(1).split(","))
            {

                keyfield=keyfield.replace("`","");
                foreach(Field* f,table->fields)
                {
                    if(f->name==keyfield)
                    {
                        key->fields<<f;
                        break;
                    }
                }
            }

            table->keys<<key;

            expectmorefields=false;
            continue;
        }
        else if(expectmorefields)
        {
            Field * field= new Field;
            field->name=line.split(" ").at(0).trimmed().replace("`",""); 
            field->datatype=line.split(" ").at(1).trimmed();
            table->fields<<field;
        }

    }

    tables<<table;


}





QString Analyser::table_plural(QString s)
{
    if(s.endsWith("us"))
    {
        s.chop(2);
        s.append("i");
    }
    else if(s.endsWith("y"))
    {
        s.chop(1);
        s.append("ies");
    }
    else if(s.endsWith("ss"))
    {
        s.append("es");
    }
    else if(!s.endsWith("s"))
    {
        s.append("s");
    }
    return s;
}

QString Analyser::table_singular(QString p)
{
    if(p.endsWith("i"))
    {
        p.chop(2);
        p.append("us");
    }
    else if(p.endsWith("ies"))
    {
        p.chop(3);
        p.append("y");
    }
    else if(p.endsWith("sses"))
    {
        p.chop(2);
    }
    else if(p.endsWith("s") && !p.endsWith("ss"))
    {
        p.chop(1);
    }
    return p;
}






