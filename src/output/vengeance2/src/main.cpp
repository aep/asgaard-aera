#include <cstdio>
#include "db.h"
#include "analyser.h"
#include <boost/foreach.hpp>
#include <iostream>
using namespace std;
using namespace boost;

int main(int argc, char ** argv)
{

    if(argc<4)
    {
        printf(
        "vengeance2 xml2mysql\r\n"
        "(c) 2009 Asgaard Technologies\r\n\r\n"
        "usage: vengeance2 user password scheme\r\n"
        "reads vengeance xml stream from stdin\r\n"
        "\r\n");

        return 1;
    }

    connection = mysql_init(NULL);
    mysql_options(connection,MYSQL_READ_DEFAULT_GROUP,"vengeance2");
    if (!mysql_real_connect(connection,"localhost",argv[1],argv[2],argv[3],0,NULL,0))
    {
        throw new mysql::error();
    }


    std::vector<Analyser::Table *>  tl=Analyser().analyse();
    BOOST_FOREACH(Analyser::Table * t,tl)
    {
        cout<<t->name<<endl;
        BOOST_FOREACH(Analyser::Field * f,t->fields)
        {
	        cout<<'\t'<<f->name<<endl;
        }

    }

    mysql_close(connection);

    return 0;
}



