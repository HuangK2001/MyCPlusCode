#include "changeadmin.h"
#include "ui_changeadmin.h"
#include<usersql.h>
#include<QMessageBox>
#include<QDebug>
#include<addmin.h>

Changeadmin::Changeadmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Changeadmin)
{
    ui->setupUi(this);
}

Changeadmin::~Changeadmin()
{
    delete ui;
}

void Changeadmin::on_pushButton_add_clicked()
{
    QString addId=ui->username->text();
    QString addPassword=ui->password->text();
    if(addId.isEmpty()||addPassword.isEmpty())
    {
        QMessageBox::information(this,"提示！","输入不能为空！",QMessageBox::Ok);
    }
    QSqlQuery query;
    QString sql=QString("select username from admin");
    query.exec(sql);
    bool isExist=false;
    while(query.next())
    {
        QString id=query.value(0).toString();
        if(id.compare(addId)==0)
        {
            QMessageBox::information(this, "警告！", "该管理员已存在！");
            isExist=false;
            break;
        }
        isExist=true;
    }
    if(!query.next())
    {
        isExist=true;
    }
    if(isExist)
    {
        QString sql=QString("insert into admin(username,password)values('%1','%2')").arg(addId).arg(addPassword);
        query.exec(sql);
        QMessageBox::information(this, "温馨提示", "恭喜!管理员："+addId+"添加成功");
        this->close();
    }
}


void Changeadmin::on_showadmin_clicked()
{
    QSqlQuery query;
    QString sql=QString("select username,password from admin");
    query.exec(sql);
    while(query.next())
    {
        QString showId=query.value(0).toString();
        QString showname=query.value(1).toString();
        ui->show->append("管理员："+showId+"  "+"密码："+showname);
    }
}

void Changeadmin::on_pushButton_del_clicked()
{
    QString deleteusername=ui->del_username->text();
    if(deleteusername=="")
    {
        QMessageBox::information(this, "警告", "您未输入想要删除的管理员");
        return;
    };
    QSqlQuery query;
    query.exec("select username from admin");
    bool isExist=false;
    while(query.next())
    {
        QString findusername=query.value(0).toString();
        if(findusername.compare(deleteusername)==0){
            QString sql=QString("delete from admin where username='%1'").arg(deleteusername);
            query.exec(sql);
            QMessageBox::information(this, "温馨提示", "恭喜!管理员："+deleteusername+"删除成功");
            isExist=false;
            this->close();
            Addmin *a=new Addmin;
            a->show();
            break;
        }
        isExist=true;
    }
    if(isExist){
        QMessageBox::information(this, "警告", "抱歉！不存该管理员:"+deleteusername);
        ui->del_username->setText("");
    }
}



void Changeadmin::on_return_2_clicked()
{
    this->close();
    Addmin *a=new Addmin;
    a->show();
}
