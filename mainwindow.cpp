#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include "QMessageBox"
#include "QSqlQuery"
#include "user_ui.h"
#include "QFileDialog"
#include "QSqlQueryModel"
#include "QDate"
#include "QTime"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame_3->hide();
    ui->frame_5->hide();

    ui->kod->hide();
    ui->newparol1->hide();
    ui->newparol2->hide();
    ui->checkBox_3->hide();
    ui->kirishForgot->hide();

    this->setGeometry(300,50,650,900);

    sql.open();
    if(!useropen())
    {
        QMessageBox::critical(this,tr("xatolik"),sql.lastError().text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        ui->password->setEchoMode(QLineEdit::Normal);
        ui->checkBox->setText("Parolni yashirish");
    }else{
        ui->password->setEchoMode(QLineEdit::Password);
        ui->checkBox->setText("Parolni ko'rsatish");
    }
}

void MainWindow::on_kirish_clicked()
{

    //kirishga urinish vaqtni olamiz
    QTime time=QTime::currentTime();
    QDate date=QDate::currentDate();
    QString sdate=date.toString("dd.MM.yyyy");
    QString stime=time.toString("H:m:s");

    // fayllarni yozish uchun e'lon qilamiz
    QFile file1("session1.txt");
    QFile file2("session2.txt");
    if (!file1.open( QIODevice::Text | QIODevice::ReadWrite)){
             return;}
    if (!file2.open(QIODevice::ReadWrite | QIODevice::Text)){
             return;}


    if(ui->password->text() == "" || ui->email->text() == "")
    {
        ui->label->show();
        ui->label->setText("Iltimos email va parol maydonlarini\nto'ldiring");
    }
    else{
        QString email = ui->email->text(),
                password = ui->password->text();
        useropen();
        QSqlQuery query;
        query.prepare("select * from user where email='"+email+"' and password='"+password+"'");

        int count = 0;
        if(query.exec()){
            while (query.next()) {
                count++;
            }
            // keyingi kodlar qatorini regestratsiya qiloyatga email yoki passvordni qayta kiritmaslikda ishlatsa bo'ladi
            if(count == 1){

                //
                useropen();
                QSqlQueryModel *m=new QSqlQueryModel();
                        m=new QSqlQueryModel();
                m->setQuery("delete from user_shahsiy where kirish=1");
                QSqlQuery query2;
                query2.prepare("INSERT INTO user_shahsiy(ismi, famil, email, kirish) "
                        "VALUES(:ism, :familya, :email, :kirish)");
               query2.bindValue(":ism","salom");
               query2.bindValue(":familya","hello2");
               query2.bindValue(":email",email);
               query2.bindValue(":kirish",1);
               query2.exec();

               QTextStream fout1(&file1);
               QString t1=fout1.readAll()+"\n";
               fout1<<sdate<<" kunda soat "<<stime<<" da kirildi.\n";
               file1.close();

                this->hide();
                //ui->label->setText("Kirish amalga oshmoqda..\nIltimos biroz kuting!");
                User_UI userdialog;
                userdialog.setModal(true);
                userdialog.exec();
                
            }
            /*
            if(count > 1){
                ui->label->setText("!!!!!!!");
            }
    */
            if(count < 1){
                ui->label->setText("Email yoki parol xato!!!\n Qayta urunib ko'ring?");
                QTextStream fout2(&file2);
                QString t2=fout2.readAll()+"\n";
                fout2<<sdate<<" kuni soat "<<stime<<" da kirishga urinildi\n";
                file2.close();
            }
        }
    }
}

void MainWindow::on_create_acount_clicked()
{
    ui->frame_2->hide();
    ui->frame_3->show();
    this->setWindowTitle("Create Account");
}

void MainWindow::on_forgot_clicked()
{
    ui->frame_2->hide();
    ui->frame_3->hide();
    this->setWindowTitle("Forgot Password");
    ui->frame_5->show();
}


void MainWindow::on_orqaga_clicked()
{
    ui->frame_5->hide();
    ui->frame_3->hide();
    this->setWindowTitle("Sign in");
    ui->frame_2->show();
}
// email forgotdagi nextforgotga
QString emailforgot;

void MainWindow::on_forgotNext_clicked()
{
    ui->label_3->setText("Kod maydoniga emailga yuborilgan\nkodni kiriting");

    //kiritilgan email bazada mavjudli tekshiriladi--------
    QString email = ui->email_2->text();
    emailforgot = email;
    QSqlQuery query3;
    query3.prepare("select * from user where email='"+email+"'");

    int count = 0;
    if(query3.exec()){
        while (query3.next()) {
            count++;
        }
        if(count == 1){
            ui->kod->show();
            ui->newparol1->show();
            ui->newparol2->show();
            ui->checkBox_3->show();
            ui->kirishForgot->show();
            ui->email_2->hide();
            ui->forgotNext->hide();
        }else{
            ui->label_3->setText("Bunday foydalanuvchi yo'q");
        }
    }

}

void MainWindow::on_orqaga_2_clicked()
{
    ui->frame_5->hide();
    ui->frame_3->hide();
    this->setWindowTitle("Sign in");
    ui->frame_2->show();
}

void MainWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked()){
        ui->newparol1->setEchoMode(QLineEdit::Normal);
        ui->checkBox_3->setText("Parolni yashirish");
    }else{
        ui->newparol1->setEchoMode(QLineEdit::Password);
        ui->checkBox_3->setText("Parolni ko'rsatish");
    }
}

void MainWindow::on_kirishForgot_clicked()
{
    //parolni tiklashda yuborilgan kodni to'g'riligi va parollarning mosligi tekshiriladi
    useropen();
    QString parol_1 = ui->newparol1->text(),
            parol_2 = ui->newparol2->text(),
            kod = ui->kod->text(),
            emailf = emailforgot;
    if(kod == "12345"){
        if(parol_1 == parol_2){
            QSqlQueryModel *m=new QSqlQueryModel();
            m=new QSqlQueryModel();
            m->setQuery("UPDATE user SET password='"+ parol_1 +"' WHERE email='"+ emailf +"'");
            //kod yangi qoyildi va sign in ga otildi
            ui->frame_5->hide();
            ui->frame_3->hide();
            this->setWindowTitle("Sign in");
            ui->frame_2->show();

        }else{
            ui->label_3->setText("Parollarning mosligida xato bor?");
        }
    }else{
        ui->label_3->setText("Kod Xato.??");
    }

}

void MainWindow::on_signUp_clicked()
{
    //account yaratish bo'yicha buyruqlar
    useropen();
    QString ismi = ui->ism->text(),
            fami = ui->fam->text(),
            email = ui->email_c->text(),
            parol_1 = ui->password1->text(),
            parol_2 = ui->password2->text();
    if(ismi == "" || fami == ""  || email == "" || parol_1 =="" || parol_2 == "")
    {
        ui->label_2->setText("Maydonlarni to'ldiring");
    }else{
        if(parol_1 == parol_2){
            QSqlQuery query;
            query.prepare("select * from user where email='"+email+"'");

            int count = 0;
            if(query.exec()){
                while (query.next()) {
                    count++;
                }
                if(count < 1){

                    QSqlQuery query2;
                    query2.prepare("INSERT INTO user(ismi, familyasi, email, password) "
                            "VALUES(:ism, :familya, :email, :parol)");
                    query2.bindValue(":ism",ismi);
                    query2.bindValue(":familya",fami);
                    query2.bindValue(":email",email);
                    query2.bindValue(":parol",parol_1);
                    query2.exec();

                    this->hide();
                    User_UI userdialog;
                    userdialog.setModal(true);
                    userdialog.exec();
                }
                if(count ==1){
                    ui->label_2->setText("Bunday foydalanuchi mavjud");
                }
            }
        }else{
            ui->label_2->setText("Parollarda xatolik bor");
        }
    }
   userclose();
}

void MainWindow::on_checkBox_2_clicked()
{
    if(ui->checkBox_2->isChecked()){
        ui->password1->setEchoMode(QLineEdit::Normal);
        ui->checkBox_2->setText("Parolni yashirish");
    }else{
        ui->password1->setEchoMode(QLineEdit::Password);
        ui->checkBox_2->setText("Parolni ko'rsatish");
    }
}

void MainWindow::on_acount_icon_2_clicked()
{
    //rasmni tanlash va uni push buutonga joylash va bazaga saqlash
    QString filename = QFileDialog::getOpenFileName(this, "Rasm tanlang", "D:/media", "*.jpg *.png");
    QIcon icon(filename);
    ui->acount_icon_2->setIcon(icon);
}
