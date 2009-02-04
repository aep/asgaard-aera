#include "db.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStringList>

bool db_open(QUrl dburl)
{
    QSqlDatabase db;
    db.removeDatabase("vengeance");



    if(dburl.scheme().isEmpty())
       db=QSqlDatabase::addDatabase("QMYSQL","vengeance");
    else
       db=QSqlDatabase::addDatabase(dburl.scheme(),"vengeance");


    if(dburl.host().isEmpty())
        db.setHostName("localhost");
    else
        db.setHostName(dburl.host());

    db.setDatabaseName(dburl.path().replace("/",""));

    db.setUserName(dburl.userName());
    db.setPassword(dburl.password());



    bool w=db.open();

    if(!w)
    {
        qDebug()<<db.lastError ();
    }

    return w;
}

