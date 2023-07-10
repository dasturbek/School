#include "user_ui.h"
#include "ui_user_ui.h"
#include <QSqlError>
#include "QMessageBox"
#include "QSqlQuery"
#include "user_ui.h"
#include "QFileDialog"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include <QtWebKitWidgets>

User_UI::User_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User_UI)
{
    ui->setupUi(this);

    sql.open();
    if(!useropen())
    {
        QMessageBox::critical(this,tr("xatolik"),sql.lastError().text());

    }

    ui->stackedWidget->setCurrentIndex(0);
        QString filename = "C:/Users/user/Documents/maktabweb/Education/Education - General.html";
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QTextStream out(&file);
        QString output = out.readAll();

        this->setBaseUrl(QUrl::fromLocalFile(filename));

        ui->webView->setHtml(output, baseUrl);

}

User_UI::~User_UI()
{
    delete ui;
}

void User_UI::setBaseUrl(const QUrl &url)
{
    baseUrl = url;
}


void User_UI::on_malumot_oquv_clicked()
{
//    O'quvchilar haqida malumotlar
    ui->stackedWidget->setCurrentIndex(1);
    QSqlTableModel *model;
    model = new QSqlTableModel(this);
    model->setTable("uquvchilarning_malumotlari_9A_sinf");
    model->select();
    ui->tableView->setModel(model);
}

void User_UI::on_home_clicked()
{
    //userga oyid xabarlar yangiliklar
    QString filename = "C:/Users/user/Documents/maktabweb/Education/Education - General.html";
    QFile file(filename);


    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString output = out.readAll();

    this->setBaseUrl(QUrl::fromLocalFile(filename));

    ui->webView->setHtml(output, baseUrl);
    ui->stackedWidget->setCurrentIndex(0);
}

void User_UI::on_about_clicked()
{
    //dasturni ishlab chiquvchilar haqida va loyiha haqida qisqacha
    QString filename = "C:/Users/user/Documents/maktabweb/Organization/Organization - General.html";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString output = out.readAll();

    this->setBaseUrl(QUrl::fromLocalFile(filename));

    ui->webView->setHtml(output, baseUrl);
    ui->stackedWidget->setCurrentIndex(0);
}

void User_UI::on_royiqnoma_clicked()
{
    // foydalanish boyicha qo'llanma
}

void User_UI::on_fikr_va_mulohazalar_clicked()
{
    //fikir va mulohazalar
}

void User_UI::on_pushButton_2_clicked()
{
    //bildirishnomalar
}

void User_UI::on_pushButton_3_clicked()
{
//    bazadan o'quvchining maluotini o'chirish

}

void User_UI::on_pushButton_clicked()
{
//    bazaga yangi o'quvchi malumotlarini qo'shish
    QSqlQuery query;
           query.prepare("INSERT INTO uquvchilarning_malumotlari_9A_sinf(Ism, Familyasi, Tug'ilgan sanasi, Passport id va seriyasi, Manzili, Ota-onasi haqida ma'lumot)"
                  "VALUES (:ism,:familya, :Sanasi, :passport, :manzili, :ota_onasi_m)");
           query.bindValue(":ism",ui->ism->text());
           query.bindValue(":familya",ui->fam->text());
           query.bindValue(":Sanasi",ui->sana->text());
           query.bindValue(":passport",ui->passport->text());
           query.bindValue(":manzili",ui->adress->text());
           query.bindValue(":ota_onasi_m",ui->ota_ona->text());
           query.exec();
           QSqlQueryModel *m=new QSqlQueryModel();
               m=new QSqlQueryModel();
               m->setQuery("SELECT * FROM uquvchilarning_malumotlari_9A_sinf");
                               ui->tableView->setModel(m);

}

void User_UI::on_pushButton_4_clicked()
{
//    bazadagi o'quvchi malumotlarini tahrirlash
    QSqlQueryModel *m=new QSqlQueryModel();
        m=new QSqlQueryModel();

     int row = ui->tableView->currentIndex().row();
            m->setQuery("UPDATE uquvchilarning_malumotlari_9A_sinf SET Passport id va seriyasi='"+ ui->Tpassport->text()+ "' WHERE id="+ui->tableView->model()->index(row, 0).data().toString());
            m->setQuery("UPDATE uquvchilarning_malumotlari_9A_sinf SET Manzili='"+ ui->Tadress->text()+ "' WHERE id="+ui->tableView->model()->index(row, 0).data().toString());
            m->setQuery("UPDATE uquvchilarning_malumotlari_9A_sinf SET Ota-onasi haqida ma'lumot="+ ui->Tota_ona->text()+ " WHERE id="+ui->tableView->model()->index(row, 0).data().toString());
            m->setQuery("SELECT * FROM uquvchilarning_malumotlari_9A_sinf");
            ui->tableView->setModel(m);

}

void User_UI::on_pushButton_5_clicked()
{
//    tanlanga yachikadagi qator malumotlarini chiqarish

    int row = ui->tableView->currentIndex().row();
    int col=ui->tableView->currentIndex().column();
    ui->tableView->currentIndex();
    ui->Tpassport->setText(ui->tableView->model()->index(row, 4).data().toString());
    ui->Tadress->setText(ui->tableView->model()->index(row, 5).data().toString());
    ui->Tota_ona->setText(ui->tableView->model()->index(row, 6).data().toString());
}

void User_UI::on_dars_jadvali_clicked()
{
//    dars jadvali
    ui->stackedWidget->setCurrentIndex(3);
}

void User_UI::on_baholar_clicked()
{
    //baholar va reyting
    ui->stackedWidget->setCurrentIndex(2);
}

void User_UI::on_comboBox_activated(const QString &arg1)
{
//    Dars jadvallari

}

