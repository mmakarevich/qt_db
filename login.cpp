/**************
 * окно аутентификации
 */


#include "login.h"
#include "ui_login.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_username->setText("admin");//автозаполнение для теста
    ui->lineEdit_password->setText("password");//автозаполнение для теста
    QString line_user = ui->lineEdit_username->text();
    QString line_pass = ui->lineEdit_password->text();

    if(line_user == "admin" && line_pass == "password")
    {

        this->close();
        table_window = new Table_window();
        table_window->show();
    }
    else
    {
        ui->statusBar->showMessage("Username and password is incorrect! try again");
    }



}
