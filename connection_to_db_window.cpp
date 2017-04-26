/******************
 * окно для соединения с базой данных
 *
*/

#include "connection_to_db_window.h"
#include "ui_connection_to_db_window.h"


Connection_to_db_window::Connection_to_db_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connection_to_db_window)
{
    ui->setupUi(this);
    ui->comboBox->addItem("set db type");
    ui->comboBox->addItem("mysql");
    ui->comboBox->addItem("sqlite");
}

Connection_to_db_window::~Connection_to_db_window()
{
    delete ui;
}

/* функция вызфывется при нажатии кнопки connect
    проверяет валидность бд */
void Connection_to_db_window::on_test_button_clicked()
{
    if(ui->comboBox->currentText()=="mysql")
    {
//        ui->lineEdit_db_name->setText("test");//автозаполнение для теста
//        ui->lineEdit_host->setText("127.0.0.1");//автозаполнение для теста
//        ui->lineEdit_port->setText("3306");//автозаполнение для теста
//        ui->lineEdit_username->setText("root");//автозаполнение для теста
//        ui->lineEdit_password->setText("root");//автозаполнение для теста

        con = new Connection_to_db();
        con->set_type_name("QMYSQL");
        con->set_db_name(ui->lineEdit_db_name->text());
        con->set_host(ui->lineEdit_host->text());
        con->set_port(ui->lineEdit_port->text().toInt());
        con->set_user(ui->lineEdit_username->text());
        con->set_password(ui->lineEdit_password->text());
        bool ok = con->connect();
        if(!ok)
        {
            QMessageBox::warning(this,"Error mysql connection","Проверьте введенные данные!");

        }
        else QMessageBox::information(this,"mysql connection","TEST OK!");
        con->close();


    }
    else if(ui->comboBox->currentText()=="sqlite")
    {

        //ui->lineEdit_db_name->setText("C:/Users/HOME/Documents/build-basa_1_test-Desktop_Qt_5_8_0_MinGW_32bit-Debug/mydatabase.sqlite");//автозаполнение для теста

        con = new Connection_to_db();
        con->set_type_name("QSQLITE");
        con->set_db_name(ui->lineEdit_db_name->text());
        bool ok = con->connect();
        if(!ok)
        {
            QMessageBox::warning(this,"Error sqlite connection","Проверьте введенные данные!");
        }
        else QMessageBox::information(this,"sqlite connection","TEST OK!");
        con->close();

    }

    else
    {
       QMessageBox::warning(this,"ERROR","invalid database!");
    }
}

/*функция на нажатие кнопки ok*/
void Connection_to_db_window::on_connect_db_button_clicked()
{
    this->close();
}

/* получаем данные из формы
   */
QString Connection_to_db_window::get_type_bd()
{
    if(ui->comboBox->currentText()=="mysql") return "QMYSQL";
    if(ui->comboBox->currentText()=="sqlite") return "QSQLITE";
    else return "";
}

QString Connection_to_db_window::get_name_bd()
{
    return ui->lineEdit_db_name->text();
}

QString Connection_to_db_window::get_host_bd()
{
    return ui->lineEdit_host->text();
}

QString Connection_to_db_window::get_user_bd()
{
    return ui->lineEdit_username->text();
}

QString Connection_to_db_window::get_password_bd()
{
    return ui->lineEdit_password->text();
}

int Connection_to_db_window::get_port_bd()
{
    return ui->lineEdit_port->text().toInt();
}
