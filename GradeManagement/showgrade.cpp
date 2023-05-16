#include "showgrade.h"
#include "ui_showgrade.h"
#include<addmin.h>
#include<QMessageBox>
#include<usersql.h>
Showgrade::Showgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Showgrade)
{
    ui->setupUi(this);
}

Showgrade::~Showgrade()
{
    delete ui;
}


void Showgrade::on_pushButton_Find_clicked()
{
    QString findId=ui->Id->text();
    QSqlQuery query;
    if(!findId.isEmpty())
    {
        QString sqlById1=QString("select Id,name,class,gaoshu,Eg,Com,Cplus from grade where Id='%1'").arg(findId);
        query.exec(sqlById1);
        bool Notfond=true;
        while (query.next())
        {
            QString Id1=query.value(0).toString();
            QString name1=query.value(1).toString();
            QString Class1=query.value(2).toString();
            QString gaoshu1=query.value(3).toString();
            QString Eg1=query.value(4).toString();
            QString Com1=query.value(5).toString();
            QString Cplus1=query.value(6).toString();

            ui->Id_2->setText(Id1);
            ui->name_2->setText(name1);
            ui->class_2->setText(Class1);
            ui->gaoshu->setText(gaoshu1);
            ui->Eg->setText(Eg1);
            ui->Com->setText(Com1);
            ui->Cplus->setText(Cplus1);

            Notfond=false;
        }
        if(Notfond){
            QMessageBox::information(this, "警告", "未找到相关信息");
            this->close();
            Addmin *a=new Addmin;
            a->show();
        }
    }
    else {
        QString findname=ui->name->text();
        QString sqlByName1=QString("select Id,name,class,gaoshu,Eg,Com,Cplus from grade where name='%2'").arg(findname);
        query.exec(sqlByName1);
        bool Notfond=true;
        while (query.next())
        {
            QString Id1=query.value(0).toString();
            QString name1=query.value(1).toString();
            QString Class1=query.value(2).toString();
            QString gaoshu1=query.value(3).toString();
            QString Eg1=query.value(4).toString();
            QString Com1=query.value(5).toString();
            QString Cplus1=query.value(6).toString();
            ui->Id_2->setText(Id1);
            ui->name_2->setText(name1);
            ui->class_2->setText(Class1);
            ui->gaoshu->setText(gaoshu1);
            ui->Eg->setText(Eg1);
            ui->Com->setText(Com1);
            ui->Cplus->setText(Cplus1);

            Notfond=false;

            Notfond=false;
        }
        if(Notfond)
        {
            QMessageBox::information(this, "警告", "未找到相关信息");
            this->close();
            Addmin *a=new Addmin;
            a->show();
        }
    }
}

void Showgrade::on_pushButton_return_clicked()
{
    QString updateId=ui->Id->text();
    QString updatename=ui->name->text();
    QString updateclass=ui->class_2->text();
    QString updateGs=ui->gaoshu->text();
    QString updateEg=ui->Eg->text();
    QString updateCom=ui->Com->text();
    QString updateC=ui->Cplus->text();

    QSqlQuery query;
    QString sql=QString("update grade set Id='%1',name='%2',class='%3',gaoshu='%4',Eg='%5',Com='%6',Cplus='%7'").arg(updateId).arg( updatename).arg( updateclass).arg( updateGs).arg( updateEg).arg( updateCom).arg( updateC);
            query.exec(sql);
            QMessageBox::information(this, "温馨提示", "恭喜！信息修改成功！");
            this->close();
            Addmin *a=new Addmin;
            a->show();

}

void Showgrade::on_pushButton_return_2_clicked()
{
    this->close();
    Addmin *a=new Addmin;
    a->show();
}
