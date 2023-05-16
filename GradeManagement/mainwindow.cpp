#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<usersql.h>
#include<QDebug>
#include<addmin.h>
#include<stu.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   Usersql usersql;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
  QMessageBox::information(this,"温馨提示！","登陆账号为学号,密码为手机号",QMessageBox::Ok);
}

void MainWindow::on_pushButton_login_clicked()
{
    QString username=ui->username->text();
    QString password=ui->password->text();
    if( ui->radioButton_addmin->isChecked())
    {
       QSqlQuery query;
        query.exec("select username,password from admin");
        bool temp=false;
        while(query.next())
        {
            QString Username=query.value(0).toString();
            QString Password=query.value(1).toString();
           if(username.compare(Username)==0&&password.compare(Password)==0)
           {
                temp=true;
                //loginer=username;
                this->hide();
                Addmin *a=new Addmin();
                a->show();
           }
       }
        if(temp==false)
        {
            QMessageBox::information(this,"提示！","输入账户或密码有错！",QMessageBox::Ok);
        }
    }
    if(ui->radioButton_stu->isChecked())
    {
        QSqlQuery query;
       query.exec("select username,password from stu");
        bool temp=false;
        while(query.next())
        {
            QString Username=query.value(0).toString();
            QString Password=query.value(1).toString();
            if(username.compare(Username)==0&&password.compare(Password)==0)
            {
                temp=true;
                this->hide();
                Stu *s=new Stu;
                s->show();
            }
        }
        if(temp==false)
        {
            QMessageBox::information(this,"提示！","输入账户或密码有错！",QMessageBox::Ok);
        }
    }

}
