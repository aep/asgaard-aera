#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <mysql.h>

extern MYSQL * connection;

namespace mysql {
    class error : public std::runtime_error{
    public:
        error():std::runtime_error(mysql_error(connection)) {   
        }
    };

    class query {
    public:
        query(std::string q){
            if (mysql_query(connection,q.c_str())){
                throw mysql::error();
            }
            res=mysql_store_result(connection);
        }
        std::vector<std::map<int,std::string> > fetchAll(){
            std::vector<std::map<int,std::string> > r;

            MYSQL_ROW row;
            

            while ((row = mysql_fetch_row(res)) != NULL){
                std::map<int,std::string>  x;
	            for(int i=0;i<mysql_num_fields(res);++i)
                    if(row[i]==0)
                        x[i]=std::string("");
                    else
                        x[i]=std::string(row[i]);
                r.push_back(x);
            }
            return r;
        }
        std::vector<std::map<std::string,std::string> > fetchAll2(){
            std::vector<std::map<std::string,std::string> > r;

            std::map<int,std::string>  ff;
            MYSQL_FIELD *field;

            int i=0;
            while((field = mysql_fetch_field(res))){       
                ff[i++]= field->name;
            }

            MYSQL_ROW row;
            
            while ((row = mysql_fetch_row(res)) != NULL){
                std::map<std::string,std::string>  x;
	            for(int i=0;i<mysql_num_fields(res);++i)
                    if(row[i]==0)
                        x[ff[i]]=std::string("");
                    else
                        x[ff[i]]=std::string(row[i]);
                r.push_back(x);
            }
            return r;
        }

        ~query(){
            mysql_free_result(res);
        }
        operator MYSQL_RES * (){
            return res;
        }
    private:
        MYSQL_RES * res;
    };


};



