#include "stu_modpassword.h"
#include "ui_stu_modpassword.h"
#include<usersql.h>
#include<QMessageBox>
#include<stu.h>
Stu_modpassword::Stu_modpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stu_modpassword)
{
    ui->setupUi(this);
}

Stu_modpassword::~Stu_modpassword()
{
    delete ui;
}

void Stu_modpassword::on_pushButton_clicked()
{
   QString newpassword=ui->new_password->text();
   QString lastpassword=ui->second_password->text();
    QSqlQuery query;
    QString sqlById1=QString("update stu set password='%2'").arg(newpassword);
    query.exec(sqlById1);
    QMessageBox::information(this,"温馨提示","密码修改成功！",QMessageBox::Ok);
    this->close();
    Stu *S=new Stu;
    S->show();
}


void Stu_modpassword::on_pushButton_3_clicked()
{
    QString findId=ui->Id->text();
    QSqlQuery query;
    bool Notfond=true;
    if(!findId.isEmpty())
    {
        QString sqlById1=QString("select username,password from stu where username='%1'").arg(findId);
        query.exec(sqlById1);

        while (query.next())
        {
            QString Id=query.value(0).toString();
            QString pssword=query.value(1).toString();
            ui->show_Id->setText(Id);
            ui->show_password->setText(pssword);
            Notfond=false;
        }

    }
    else if(Notfond)
    {
        QMessageBox::information(this, "警告", "未找到相关信息");
        this->close();
    }
}

void Stu_modpassword::on_pushButton_2_clicked()
{
    this->close();
    Stu *S=new Stu;
    S->show();
}
