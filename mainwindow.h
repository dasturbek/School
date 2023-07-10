#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlDatabase>
#include <QDebug>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    QSqlDatabase sql;

    void userclose(){
        sql.close();
        sql.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool useropen(){
        sql = QSqlDatabase::addDatabase("QSQLITE");
        sql.setDatabaseName("C:/Users/user/Documents/Maktab/baza/maktab.db");
        sql.open();
        if(!sql.open())
        {
            qDebug()<<"no open database";
            return false;
        }else{
            qDebug()<<"open database";
            return true;
        }
    }

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_clicked();

    void on_kirish_clicked();

    void on_create_acount_clicked();

    void on_forgot_clicked();


    void on_orqaga_clicked();

    void on_forgotNext_clicked();

    void on_orqaga_2_clicked();

    void on_checkBox_3_clicked();

    void on_kirishForgot_clicked();

    void on_signUp_clicked();

    void on_checkBox_2_clicked();

    void on_acount_icon_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
