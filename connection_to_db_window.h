#ifndef CONNECTION_TO_DB_WINDOW_H
#define CONNECTION_TO_DB_WINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "connection_to_db.h"


namespace Ui {
 class Connection_to_db_window;
}

class Connection_to_db_window : public QDialog
{
    Q_OBJECT

public:
    explicit Connection_to_db_window(QWidget *parent = 0);
    ~Connection_to_db_window();
    QSqlDatabase *db;
    QString get_type_bd();
    QString get_name_bd();
    QString get_host_bd();
    QString get_user_bd();
    QString get_password_bd();
        int get_port_bd();
    Connection_to_db *con;
private slots:
    void on_connect_db_button_clicked();

    void on_test_button_clicked();

private:
    Ui::Connection_to_db_window *ui;


};

#endif // CONNECTION_TO_DB_WINDOW_H
