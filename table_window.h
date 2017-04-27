#ifndef TABLE_WINDOW_H
#define TABLE_WINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QUrl>
#include <QFileDialog>
#include <QDesktopServices>
#include "connection_to_db.h"
#include "connection_to_db_window.h"


namespace Ui {
class Table_window;
}

class Table_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Table_window(QWidget *parent = 0);
    ~Table_window();

private slots:
    void on_load_data_button_clicked();

    void on_add_column_button_clicked();

    void on_add_row_button_clicked();

    void on_delete_row_button_clicked();

    void on_delete_column_button_clicked();

    void on_connect_button_2_clicked();

    void on_load_tables_button_clicked();

    void on_add_table_button_clicked();

    void on_delete_table_button_clicked();

//    void changeEvent(QEvent*);

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    void setTrayIconActions();

    void showTrayIcon();

    void on_actionabout_QT_triggered();

    void on_actionclose_2_triggered();

    void on_actionAPI_QT_triggered();

    void on_actionabout_triggered();

    void on_action_save_file_triggered();

private:
    Ui::Table_window *ui;
    Connection_to_db *active_connection_to_db;
    QSqlTableModel *model;
    Connection_to_db_window *w;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;

};

#endif // TABLE_WINDOW_H
