#include <cstdio>
#include "db.h"
#include "analyser.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <cstdio>
#include <stack>
#include <cassert>
#include "expat.h"
#include <stdexcept>


using namespace std;
using namespace boost;


#define IFDEBUG(term) 
#define NDEBUG(term)  IFDEBUG(cout<<deepnessprefix<< term <<endl;)

void xml_start  (void * data, const char *el, const char **attr);
void xml_end    (void * data, const char *el);

struct Item
{
    Item():qualificator(0),table(0),qualified(false),parent(0),evald(false)  {}
    Analyser::Key* qualificator;
    Analyser::Table* table;
    map<string,string> member_fields;
    map<string,string> sub_result;
    bool qualified;
    Item * parent;
    bool evald;
    map<string,string> evalresult;
};

std::stack<Item*> items;
IFDEBUG( string deepnessprefix);
std::vector<Analyser::Table *> scheme;

int main(int argc, char ** argv)
{
    cout<<"vengeance2 xml2mysql\r\n(c) 2009 Asgaard Technologies\r\n\r\n";

    if(argc<4){
        printf(
        "usage: vengeance2 user password scheme\r\n"
        "reads vengeance xml stream from stdin\r\n"
        "\r\n");
        return 1;
    }


    cout<<"connecting"<<endl;
    connection = mysql_init(NULL);
    mysql_options(connection,MYSQL_READ_DEFAULT_GROUP,"vengeance2");
    if (!mysql_real_connect(connection,"localhost",argv[1],argv[2],argv[3],0,NULL,0))
    {
        throw new mysql::error();
    }

    cout<<"analyzing"<<endl;
    scheme=Analyser().analyse();

    XML_Parser p = XML_ParserCreate(NULL);
    assert(p);
    XML_SetElementHandler(p, xml_start, xml_end);

    cout<<"reading vengeance stream from stdin"<<endl;
    while(cin)
    {
        string line;
        getline(cin, line);
        line+="\r\n";
        if (! XML_Parse(p, line.c_str(), line.length(), false)) {
            fprintf(stderr, "Parse error at line %d:\n%s\n",
            XML_GetCurrentLineNumber(p),
            XML_ErrorString(XML_GetErrorCode(p)));
            exit(-1);
        }
    }
    cout<<"success"<<endl;
    cout<<"closing connection"<<endl;

    mysql_close(connection);
    return 0;
}


bool canQualify(Item * item,string fieldname)
{
    if(item->member_fields.count(fieldname)>0)
        return true;

    if(!item->qualified)
        return false;

    BOOST_FOREACH(Analyser::Key* key, item->table->keys){
        BOOST_FOREACH(Analyser::Field* field, key->fields){
            if(field->name==fieldname)
                return true;
        }
    }
    return false;
}



void qualify(Item * item)
{
    if(item->qualified)
        return;

    if(!item->parent)
        return;

    NDEBUG("qualification for "<<item->table->name);

    BOOST_FOREACH(Analyser::Key* key, item->table->keys){
        if(key->type==Analyser::PrimaryKey){
            NDEBUG("\tprimary");
        }
        else if(key->type==Analyser::IndexKey){
            continue;
        }
        else if(key->type==Analyser::UniqueKey){
            NDEBUG("\tunique");
        }

        bool qualifiedkey=true;
        BOOST_FOREACH(Analyser::Field* field, key->fields){
	        NDEBUG("\t\t> "<<field->name)
            if(item->member_fields.count(field->name)>0){
                NDEBUG("\t\t  by member")
            }
            else if(canQualify(item->parent,field->name)){
                NDEBUG("\t\t  by parent")
            }
            else if(item->sub_result.count(field->name)>0){
                NDEBUG("\t\t  by sub")
            }
            else{
                NDEBUG("\t\t  X no")
                qualifiedkey=false;
            }
        }
        if(qualifiedkey){
            item->qualificator=key;
            item->qualified=true;
            break;
        }
    }
}


bool hack_contains(std::vector<string> keys,string s){
        for(vector<string>::iterator i=keys.begin();i!=keys.end();++i){
            if (s==*i)
                return true;
        }
        return false;
}


/**
this is stage2. It is usually called after stage1 has run unless it is called reverse for a parent relation.
this is why we call qualify() at the beginning.

*/
map<string,string>  finalyEval(Item * item){

    //ignore the root
    if(!item->parent)
        return  map<string,string> ();

    if(item->evald)
        return item->evalresult;


    assert(item->qualified);

    NDEBUG("=====eval====");


    vector<string> keys;
    vector<string> values;

    /** walk through the qualificator key and find all values for the key*/
    BOOST_FOREACH(Analyser::Field* field, item->qualificator->fields){

        keys.push_back(field->name);
        NDEBUG(field->name)


        /** 
            easiest case:  it's just an attribute
        */
        if(item->member_fields.count(field->name)>0){
            values.push_back(item->member_fields[field->name]);
            NDEBUG("\t  by member")
        }
        /** 
            a subnode has generated the key to qualify this field. 
            this is usually an 1 to N relation where the parent can have multiple rows like this.
        */
        else if(item->sub_result.count(field->name)>0){
            values.push_back(item->sub_result[field->name]);
            NDEBUG("\t  by sub")
        }
        /** 
            a parent node has the field i need to insert this row.  
            this is an N:1  relation where this row can be linked to many different parents.
        */
        else if(canQualify(item->parent,field->name)){
            NDEBUG("\t  by parent");
            IFDEBUG(deepnessprefix.append("\t");)

            map<string,string> e= finalyEval(item->parent);
            values.push_back(e[field->name]);
            IFDEBUG(deepnessprefix.resize(deepnessprefix.length()-1);)
        }
        /**
            well this isn't supposed to happen
        */
        else{
            throw runtime_error(" fatal inconsistency");
        }
    }



    /** built my sql strings from the keys */
    string sqlk;
    string sqlv;
    string sqlu;
    string sqls;

    for(int i=0;i<keys.size();i++)
    {
        sqlk+=" `"+keys.at(i)+"` ,";
        sqlv+=" '"+values.at(i)+"' ,";
        sqlu+=" `"+keys.at(i)+"` = '"+values.at(i)+"' ,";
        sqls+=" `"+keys.at(i)+"` = '"+values.at(i)+"' and";
    }


    /** also include all member fields */

	typedef pair<string,string> strpair;
    BOOST_FOREACH (strpair k,item->member_fields){
        if(hack_contains(keys,k.first))
            continue;
        sqlk+=" `"+k.first+"` ,";
        sqlv+=" '"+k.second+"' ,";
        sqlu+=" `"+k.first+"` = '"+k.second+"' ,";
        sqls+=" `"+k.first+"` = '"+k.second+"' and";
    }


    /** get all fields from the subnode that might be relevant */

    BOOST_FOREACH(strpair k,item->sub_result){
        if(hack_contains(keys,k.first))
            continue;

        BOOST_FOREACH(Analyser::Field * field,item->table->fields){
            if(field->name==k.first){
                sqlk+=" `"+k.first+"` ,";
                sqlv+=" '"+k.second+"' ,";
                sqlu+=" `"+k.first+"` = '"+k.second+"' ,";
                sqls+=" `"+k.first+"` = '"+k.second+"' and";
            }
        }
    }


    sqlk.resize(sqlk.length()-1);
    sqlv.resize(sqlv.length()-1);
    sqlu.resize(sqlu.length()-1);
    sqls.resize(sqls.length()-3);





    bool exists=false;
    {
        mysql::query eq("select COUNT(*) from "+item->table->name+" where "+sqls) ;
            exists=(eq.fetchAll()[0][0]!="0");
    }

    
    if(!exists)
    {
        cout<<"\timport \""<< Analyser::table_singular(item->table->name)<<"\""<<endl;
        mysql::query queryi(" replace into `"+item->table->name+"` ( "+sqlk+" )  values ( "+sqlv+" )");
    }

    /** and get the entire row back, so we can feed parents with our generated or found values*/

    
    map<string,string> r;

    mysql::query querys("select * from "+item->table->name+" where "+sqls);
    std::vector<std::map<std::string,std::string> > ir = querys.fetchAll2();
    assert(ir.size()==1);
    

    BOOST_FOREACH(Analyser::Field* field,item->table->fields)
    {
        r[field->name]=ir[0][field->name];
    }

    item->evald=true;
    item->evalresult=r;
    return  r;
}







void push_item(const char * el){
    IFDEBUG(cout<<deepnessprefix<<"#"<<el<<endl;);
    IFDEBUG(deepnessprefix.append("\t"));
    std::string pp = Analyser::table_plural(el);
    BOOST_FOREACH (Analyser::Table * table, scheme){
        if (table->name==pp || table->name==el ){
            Item *o=new Item;
            o->table=table;
            o->parent=items.size()?items.top():0;
	        items.push(o);
            return;
        }
    }
    throw runtime_error("unable to find table"+string(el));
}



void xml_start(void *, const char *el, const char **attr) {

    if(items.size())
        qualify(items.top());

    push_item(el);

    for(int i=0;attr[i];i+=2){
        IFDEBUG(cout<<deepnessprefix<<"verify route for "<<attr[i]<<endl;);

        bool routed=false;
        BOOST_FOREACH(Analyser::Field* field, items.top()->table->fields){
            if (field->name==attr[i]){
                IFDEBUG(cout<<deepnessprefix<<"\t\tis member\n";);
                routed=true;
                break;
            }
        }

        BOOST_FOREACH(Analyser::Key* key, items.top()->table->keys){
            BOOST_FOREACH(Analyser::Field* field, key->fields){
                if (field->name==attr[i]){
                    IFDEBUG(cout<<deepnessprefix<<"\t\tis partial key\n");
                    break;
                }
            }
        }

        if(routed){
            items.top()->member_fields[attr[i]]=attr[i+1];
        }
        else{
                cerr<<"route verification failed"<<endl;
                abort();
        }
    }


    qualify(items.top());
    if(items.top()->qualified)
        finalyEval(items.top());

}



void xml_end(void *, const char *el) {

    qualify(items.top());

    map<string,string> r=finalyEval(items.top());
    delete items.top();
    items.pop();
    if(!items.empty())
       items.top()->sub_result=r; 


    IFDEBUG(deepnessprefix.resize(deepnessprefix.length()-1);)
}


