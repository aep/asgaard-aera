#include "analyser.h"
#include "db.h"
#include <iostream>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace boost;
using namespace std;

typedef split_iterator<string::iterator> string_split_iterator;


Analyser::Analyser()
{
    
}

std::vector<Analyser::Table *>  Analyser::analyse()
{
    std::vector<std::map<int,std::string> > r=mysql::query("show tables;").fetchAll();
    for(std::vector< std::map<int,std::string> >::iterator i=r.begin();i!=r.end();++i) {
        std::map<int,std::string> row=*i;
        mysql::query stc ("show create table " + row[0]);
        MYSQL_ROW row2;
        while ((row2 = mysql_fetch_row(stc)) != NULL){
                parseShowCreate(std::string(row2[1]));
        }
    }
    return tables;
}

void Split( std::string const & str , char token , std::vector<std::string> & res ){
  std::string::size_type pos  = std::string::npos , last = 0; 

  while( (pos = str.find_first_of( token , last = pos + 1 )) != std::string::npos )
     res.push_back(str.substr(last,pos - last));

  res.push_back(str.substr(last));
}



void Analyser::parseShowCreate (std::string  sc){

    Table * table= new Table;
    bool expectmorefields=false;

    for(string_split_iterator It= make_split_iterator(sc, first_finder("\n", is_iequal()));It!=string_split_iterator();++It){
        std::string line=copy_range<std::string>(*It);
        trim(line);
        to_lower(line);
        if(starts_with(line,"create")){
            for(string_split_iterator It2= make_split_iterator(line, first_finder(" ", is_iequal()));It2!=string_split_iterator();++It2){
                std::string linesub=copy_range<std::string>(*It2);
                trim(linesub);
                if(linesub=="create")
                    continue;
                if(linesub=="table")
                    continue;
	            erase_all(linesub, "`"); 
                table->name=linesub;
                break;
            }
            expectmorefields=true;
            continue;
        }
        else if(starts_with(line,")")){
            expectmorefields=false;
            break;
        }
        else if(starts_with(line,"unique") ||  starts_with(line,"primary") || starts_with(line,"key"))
        {
            Key *key=new Key;
            key->type=UnknownKeyType;

            vector<string> rt1;
            split( rt1, line , is_any_of("(") );
            
            for(string_split_iterator It2= make_split_iterator(rt1[0], first_finder(" ", is_iequal()));It2!=string_split_iterator();++It2){
                std::string linesub=copy_range<std::string>(*It2);
                trim(linesub);

                if(linesub=="primary"){
                    if(key->type==UnknownKeyType)
                        key->type=PrimaryKey;
                    continue;
                }
                if(linesub=="unique"){
                    if(key->type==UnknownKeyType)
                        key->type=UniqueKey;
                    continue;
                }
                if(linesub=="key"){
                    if(key->type==UnknownKeyType)
                        key->type=IndexKey;
                    continue;
                }

                break;
            }

            vector<string> rt2;
            split( rt2, line , is_any_of(")") );
            split( rt2, rt2[0] , is_any_of("(") );



            for(string_split_iterator It2= make_split_iterator(rt2[1], first_finder(",", is_iequal()));It2!=string_split_iterator();++It2){
                std::string keyfield=copy_range<std::string>(*It2);
                trim(keyfield);
	            erase_all(keyfield, "`"); 
                for(vector<Field*>::iterator i=table->fields.begin();i!=table->fields.end();++i)
                {
                    Field* f=*i;
                    if(f->name==keyfield)
                    {
                        key->fields.push_back(f);
                        break;
                    }
                }
            }

            table->keys.push_back(key);

            expectmorefields=false;
            continue;
        }
        else if(expectmorefields)
        {
            Field * field= new Field;

            vector<string> rt;
            split( rt, line , is_any_of(" "));

            field->name=rt[0];
            trim(field->name);
            erase_all(field->name, "`"); 
            field->datatype=rt[1];
            trim(field->datatype);
            table->fields.push_back(field);
        }
    }
    tables.push_back(table);

}



bool endsWith (std::string str, std::string substr) {
    size_t i = str.rfind(substr);
    return (i != std::string::npos) && (i == (str.length() - substr.length()));
}


std::string Analyser::table_plural(std::string s)
{
    if(endsWith(s,"us"))
    {
        s=s.substr(0,s.length()-2);
        s.append("i");
    }
    else if(endsWith(s,"y"))
    {
        s=s.substr(0,s.length()-1);
        s.append("ies");
    }
    else if(endsWith(s,"ss"))
    {
        s.append("es");
    }
    else if(!endsWith(s,"s"))
    {
        s.append("s");
    }
    return s;
}

std::string Analyser::table_singular(std::string s)
{
    if(endsWith(s,"i"))
    {
        s=s.substr(0,s.length()-2);
        s.append("us");
    }
    else if(endsWith(s,"ies"))
    {
        s=s.substr(0,s.length()-3);
        s.append("y");
    }
    else if(endsWith(s,"sses"))
    {
        s=s.substr(0,s.length()-2);
    }
    else if(endsWith(s,"s") && !endsWith(s,"ss"))
    {
        s=s.substr(0,s.length()-1);
    }
    return s;
}






