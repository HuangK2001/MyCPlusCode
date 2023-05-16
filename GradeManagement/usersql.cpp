#include "usersql.h"
#include<QDebug>
Usersql::Usersql()
{
    connectsql();
}

void Usersql::connectsql()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
       db.setHostName("127.0.0.1");
       db.setUserName("root");
       db.setPassword("183655");
       db.setDatabaseName("user");
       if(db.open())
           {
               qDebug()<<"Database connected successfully!";
               return;
           }
       else
           {
               qDebug()<<"Database connected failed!";
               return;
           }

}
