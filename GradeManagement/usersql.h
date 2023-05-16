#ifndef USERSQL_H
#define USERSQL_H
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class Usersql
{
public:
    Usersql();
    void connectsql();
private:
        QSqlQuery *query;
};

#endif // USERSQL_H
