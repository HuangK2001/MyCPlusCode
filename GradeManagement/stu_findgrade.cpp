#include "stu_findgrade.h"
#include "ui_stu_findgrade.h"
#include<usersql.h>
#include<QMessageBox>
#include<stu_findgrade.h>
#include<stu.h>
Stu_findgrade::Stu_findgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stu_findgrade)
{
    ui->setupUi(this);
}

Stu_findgrade::~Stu_findgrade()
{
    delete ui;
}

void Stu_findgrade::on_find_grade_clicked()
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
            QString Id2=query.value(0).toString();
            QString name2=query.value(1).toString();
            QString Class2=query.value(2).toString();
            QString gaoshu2=query.value(3).toString();
            QString Eg2=query.value(4).toString();
            QString Com2=query.value(5).toString();
            QString Cplus2=query.value(6).toString();
            ui->Id_3->setText(Id2);
            ui->name_3->setText(name2);
            ui->class_3->setText(Class2);
            ui->gaoshu->setText(gaoshu2);
            ui->Eg->setText(Eg2);
            ui->Com->setText(Com2);
            ui->Cplus->setText(Cplus2);
            Notfond=false;
        }
        if(Notfond){
            QMessageBox::information(this, "警告", "未找到相关信息");
            this->close();
            Stu_findgrade *s=new Stu_findgrade;
            s->show();
        }
    }
}


void Stu_findgrade::on_quit_clicked()
{
   this->close();
    Stu *S=new Stu;
    S->show();

}
