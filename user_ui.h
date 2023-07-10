#ifndef USER_UI_H
#define USER_UI_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QUrl>

namespace Ui {
class User_UI;
}

class User_UI : public QDialog
{
    Q_OBJECT

    QSqlDatabase sql;
public: void userclose(){
        sql.close();
        sql.removeDatabase(QSqlDatabase::defaultConnection);
    }

public: bool useropen(){
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
    explicit User_UI(QWidget *parent = 0);
    ~User_UI();

    void setBaseUrl(const QUrl &url);

private slots:
    void on_malumot_oquv_clicked();

    void on_home_clicked();

    void on_about_clicked();

    void on_royiqnoma_clicked();

    void on_fikr_va_mulohazalar_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_dars_jadvali_clicked();

    void on_baholar_clicked();

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::User_UI *ui;
    QUrl baseUrl;
};

#endif // USER_UI_H
