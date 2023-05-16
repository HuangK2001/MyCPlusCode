#include "mainwindow.h"
#include <QApplication>
#include <qsqldatabase.h>
#include<qdebug.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
       db.setHostName("127.0.0.1");
       db.setUserName("root");//你的数据库管理员账户
       db.setPassword("183655");//数据库密码
       db.setDatabaseName("user");
       if(db.open())
           {
               qDebug()<<"Database connected successfully!";

           }
       else
           {
               qDebug()<<"Database connected failed!";

           }
    return a.exec();
}
