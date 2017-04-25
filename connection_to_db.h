#ifndef CONNECTION_TO_DB_H
#define CONNECTION_TO_DB_H
#include <QtSql>

class Connection_to_db
{
public:
    Connection_to_db();
    bool connect();
    void close();
    void set_db_name(QString);
    void set_host(QString);
    void set_user(QString);
    void set_password(QString);
    void set_port(int);
    void set_type_name(QString);
    QString get_name_db();
    QSqlDatabase get_database();
    QString get_type_db();

private:

    QSqlDatabase mydb;
    QString db_name ;
    QString host_name ;
    QString user_name ;
    QString password ;
    QString type_name ;
    int port ;
};

#endif // CONNECTION_TO_DB_H
