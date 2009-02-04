#include <QCoreApplication>
#include <QStringList>
#include <QDebug>
#include <QTextStream>
#include <QUrl>
#include "db.h"
#include "analyser.h"
#include "import.h"
#include <QXmlQuery>
#include <QFile>
#include <QXmlFormatter>
#include <QXmlNamePool>
#include <QxtStdio>
#include <QXmlStreamWriter>

static void help()
{
QTextStream(stdout)<<
    "vengeance xml2sql\r\n"
    "(c) 2009 Asgaard Technologies\r\n\r\n"
    "usage: vengeance [DRIVER://user:password@hostname/database] [OPTIONS]\r\n"
    "\r\ndatabase options:\r\n"
    "-s, --scheme scheme.xml .. use xml/sqldescriptor to describe the sql database\r\n"
    "                           the default ist to try auto detection\r\n"
    "-a, --analyze  ........... print database scheme as xml\r\n"

    "\r\n";
};
    


int main(int argc, char ** argv)
{
    QCoreApplication app(argc,argv);

    if(app.arguments().count()<2)
    {
        help();
        return 1;
    }


    if(!db_open(app.arguments().at(1)))
    {
        qDebug("cannot connect to the database");
        return 62;
    }



    if(app.arguments().count()>2  && (( app.arguments().at(2)=="-a" ) || ( app.arguments().at(2)=="--analyze" )  ) )
    {
        QList<Analyser::Table *>  tables= Analyser().analyse();


        QxtStdio stdio;
        QXmlStreamWriter writer(&stdio);
        writer.setAutoFormatting(true);

        writer.writeStartDocument();
        writer.writeStartElement("sqldescriptor");

        foreach(Analyser::Table* table, tables)
        {
            writer.writeStartElement("table");
            writer.writeAttribute("name",table->name);

            foreach(Analyser::Field *field,table->fields)
            {
                writer.writeStartElement("field");
                writer.writeAttribute("name",field->name);
                writer.writeEndElement();
            }


            foreach(Analyser::Key* key,table->keys)
            {
                writer.writeStartElement("key");
                if(key->type==Analyser::IndexKey)
                {
                    writer.writeAttribute("type","key");
                }
                else if(key->type==Analyser::PrimaryKey)
                {
                    writer.writeAttribute("type","primary");
                }
                else if(key->type==Analyser::UniqueKey)
                {
                    writer.writeAttribute("type","unique");
                }
    
    
                foreach(Analyser::Field* field,key->fields)
                {
                    writer.writeStartElement("field");
                    writer.writeAttribute("name",field->name);
                    writer.writeEndElement();
                }
                writer.writeEndElement();
            }
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeEndDocument();

    }
    else
    {

        QxtStdio io;
        io.waitForEOF();
        Import import(Analyser().analyse());
        import.import(io.readAll());
    }


    return 0;
}

