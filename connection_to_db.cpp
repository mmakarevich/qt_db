/****************
 * класс для соединения с базой данных
 *
*/



#include "connection_to_db.h"

Connection_to_db::Connection_to_db()
{

}
bool Connection_to_db::connect()
{
    this->mydb=QSqlDatabase::addDatabase(this->type_name);
    mydb.setDatabaseName(this->db_name);
    mydb.setHostName(this->host_name);
    mydb.setPort(this->port);
    mydb.setUserName(this->user_name);
    mydb.setPassword(this->password);
    if(mydb.open())
        {
            qDebug()<<"connected to "+this->db_name+" "+this->type_name;
            return true;
        }
        else
        {
            qDebug()<<"connection error !";
            return false;
        }

}
void Connection_to_db::close()
{
    this->mydb.removeDatabase(mydb.connectionName());
    qDebug()<<"connection close !";
}
void Connection_to_db::set_db_name(QString name)
{
    this->db_name=name;
}
void Connection_to_db::set_host(QString name)
{
    this->host_name=name;
}
void Connection_to_db::set_password(QString name)
{
    this->password=name;
}
void Connection_to_db::set_user(QString name)
{
    this->user_name=name;
}
void Connection_to_db::set_port(int name)
{
    this->port=name;
}
void Connection_to_db::set_type_name(QString name)
{
    this->type_name = name;
}

QString Connection_to_db::get_name_db()
{
    return this->db_name;
}
QSqlDatabase Connection_to_db::get_database()
{
    return this->mydb;
}

QString Connection_to_db::get_type_db()
{
    return this->type_name;
}
