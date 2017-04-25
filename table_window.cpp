/**************
 * основное окно приложения
 */


#include "table_window.h"
#include "ui_table_window.h"


Table_window::Table_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Table_window)
{
    ui->setupUi(this);
    ui->connect_button_2->click();//автонажатие кнопки connect для соединения с бд;

    this -> setTrayIconActions();//трей
    this -> showTrayIcon();

}

Table_window::~Table_window()
{
    delete ui;
}

/*** функция вызывается при нажатии кнопки load data */

void Table_window::on_load_data_button_clicked()
{
    this->model = new QSqlTableModel(this);
    model->setTable(ui->comboBox->currentText());
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

/*** функция вызывается при нажатии кнопки add column;
     для разных типов бд */

void Table_window::on_add_column_button_clicked()
{
    if(this->main_conn->get_type_db()=="QMYSQL")
    {
        QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
        QString str = ui->add_column_data->date().toString("dd_MM_yyyy");
        qry->prepare("ALTER TABLE "+ui->comboBox->currentText()+" ADD "+str+" VARCHAR(5)");
        qry->exec();
        QMessageBox::information(this,"add column","added column "+str+"\n"+"reload data!");
    }

    if(this->main_conn->get_type_db()=="QSQLITE")
    {
        QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
        QString str = ui->add_column_data->date().toString("dd_MM_yyyy");
        qry->prepare("ALTER TABLE "+ui->comboBox->currentText()+" ADD '"+str+"' VARCHAR(5)");
        qry->exec();
        QMessageBox::information(this,"add column","added column "+str+"\n"+"reload data!");
    }

}

/*** функция вызывается при нажатии кнопки add row;
     добавляет запись в таблицу */
void Table_window::on_add_row_button_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();
    int row = 1+index.row();
    this->model->insertRow(row);
}

/*** функция вызывается при нажатии кнопки delete row;
     удаляет запись из таблицы */
void Table_window::on_delete_row_button_clicked()
{ 
        QModelIndex index = ui->tableView->currentIndex();
        this->model->removeRow(index.row());
}

/*** функция вызывается при нажатии кнопки delete column;
     удаляет столбец из таблицы */
void Table_window::on_delete_column_button_clicked()
{
    if(this->main_conn->get_type_db()=="QMYSQL")
    {
        QModelIndex index = ui->tableView->currentIndex();
        QString str = this->model->record().fieldName(index.column());
        QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
        qry->prepare("ALTER TABLE "+ui->comboBox->currentText()+" DROP "+str);
        qry->exec();
        if(str==""){QMessageBox::warning(this,"warning drop column","choose column");}
        else{QMessageBox::information(this,"drop column","deleted column "+str+"\n"+"reload data!");}
    }
    if(this->main_conn->get_type_db()=="QSQLITE")
    {
        QMessageBox::warning(this,"Внимание!","Недоступно для SQLITE базы!");
    }


}

/*** функция вызывается при нажатии кнопки as csv;
     сохраняет данные из выбраной таблицы в файл в формате .csv */
void Table_window::on_save_as_file_button_clicked()
{
    QString text_data;
    int rows = this->model->rowCount();
    int columns = this->model->columnCount();
    for(int k=0; k< columns; k++)
    {
        text_data += this->model->headerData(k,Qt::Horizontal,Qt::DisplayRole).toString();
        text_data += ";";
    }
    text_data += "\n";

    for(int i=0; i< rows; i++)
    {
        for(int j=0; j<columns; j++){
            text_data += this->model->data(this->model->index(i,j)).toString();
            text_data += ";";
        }
    text_data += "\n";
    }
    QFile csv_file(ui->add_filename_line->text());

    if(csv_file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream out(&csv_file);
        out << text_data;

        csv_file.close();

        QMessageBox::information(this,"Save","File saved as "+ui->add_filename_line->text());
    }
    else
    {
        QMessageBox::warning(this,"Save","Enter correct filename!");
    }
}

/*** функция вызывается при нажатии кнопки connect;
     загружает данные из выбранной таблицы */
void Table_window::on_connect_button_2_clicked()
{
    this->w = new Connection_to_db_window(this);
    w->setModal(true);
    w->show();
    int rez = w->exec();
    if(QDialog::Accepted==rez)
    {
        this->main_conn = new Connection_to_db();
        main_conn->set_type_name(w->get_type_bd());
        main_conn->set_db_name(w->get_name_bd());
        main_conn->set_user(w->get_user_bd());
        main_conn->set_host(w->get_host_bd());
        main_conn->set_password(w->get_password_bd());
        main_conn->set_port(w->get_port_bd());
        main_conn->connect();

    }
}

/*** функция вызывается при нажатии кнопки load tables;
     загружает названия доступных таблиц из бд в comboBox */
void Table_window::on_load_tables_button_clicked()
{
    if(this->main_conn->get_type_db()=="QMYSQL")
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
        qry->prepare("SHOW TABLES");
        qry->exec();
        model->setQuery(*qry);
        ui->comboBox->setModel(model);
    }
    if(this->main_conn->get_type_db()=="QSQLITE")
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
        qry->prepare("select name from sqlite_master where type='table'");
        qry->exec();
        model->setQuery(*qry);
        ui->comboBox->setModel(model);
    }
}

/*** функция вызывается при нажатии кнопки .jpg;
     сохраняет таблицу в формате jpg */
void Table_window::on_save_as_jpg_file_clicked()
{
    ui->tableView->grab().save(ui->add_filename_line->text());
    QMessageBox::information(this,"Save","File saved as "+ui->add_filename_line->text());
}

/*** функция вызывается при нажатии кнопки add table;
     добавляет таблицу в текущую бд */
void Table_window::on_add_table_button_clicked()
{

    QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
    QString str = ui->line_add_table->text();
    qry->prepare("CREATE TABLE "+str+"( name varchar(30) not null default '-')");
    qry->exec();
    QMessageBox::information(this,"add table","added table "+str+"\n"+"reload tables!");

}

/*** функция вызывается при нажатии кнопки delete table;
     удаляет таблицу из бд */
void Table_window::on_delete_table_button_clicked()
{
    QSqlQuery *qry = new QSqlQuery(this->main_conn->get_database());
    QString str = ui->line_add_table->text();
    qry->prepare("DROP TABLE "+str);
    qry->exec();
    QMessageBox::information(this,"delete table","deleted table "+str+"\n"+"reload tables!");
}

/*** функция перехватывает сворачивание приложения и сворачивает его в трей;
      */
void Table_window::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
        if (event -> type() == QEvent::WindowStateChange)
        {
            if (isMinimized())
            {
                this -> hide();
            }
        }
}

/*** функция вызывается при нажатии на иконку в трее ;
     при нажатии левой кнопкой мыши разворачивает приложение */
void Table_window::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
        {
            case QSystemTrayIcon::Trigger:
            case QSystemTrayIcon::DoubleClick:
                this -> showNormal();
                break;
            default:
                break;
        }
}

/*** функция вызывается при нажатии правой кнопкой мыши на иконку в трее;
      */
void Table_window::setTrayIconActions()
{

       minimizeAction = new QAction("Свернуть", this);
       restoreAction = new QAction("Восстановить", this);
       quitAction = new QAction("Выход", this);

       connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
       connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
       connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

       trayIconMenu = new QMenu(this);
       trayIconMenu -> addAction (minimizeAction);
       trayIconMenu -> addAction (restoreAction);
       trayIconMenu -> addAction (quitAction);
}

/*** функция задает свойства для трея;
      */
void Table_window::showTrayIcon()
{
        trayIcon = new QSystemTrayIcon(this);
        QIcon trayImage(":/images/icon.png");
        trayIcon -> setIcon(trayImage);
        trayIcon -> setContextMenu(trayIconMenu);

        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

        trayIcon -> show();
}
