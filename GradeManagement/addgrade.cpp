#include "addgrade.h"
#include "ui_addgrade.h"
#include<usersql.h>
#include<QMessageBox>
#include<QDebug>
#include<addmin.h>
Addgrade::Addgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addgrade)
{
    ui->setupUi(this);
}

Addgrade::~Addgrade()
{
    delete ui;
}

void Addgrade::on_pushButton_gengxincj_clicked()
{
    QString addId=ui->Id->text();
    QString addname=ui->name->text();
    QString addclass=ui->class_2->text();
    QString addGs=ui->gaoshu->text();
    QString addEg=ui->yingyu->text();
    QString addCom=ui->computer->text();
    QString addC=ui->C->text();
    QSqlQuery query;
    query.exec("select Id from grade");
    bool isExist=false;
    if(addId.isEmpty()||addname.isEmpty()||addclass.isEmpty()||addEg.isEmpty()||addGs.isEmpty()||addCom.isEmpty()||addC.isEmpty())
    {
        QMessageBox::information(this,"温馨提示","信息未修改！",QMessageBox::Ok);
    }
    while(query.next())
    {
        QString id=query.value(0).toString();
        if(id.compare(addId)!=0){
            QMessageBox::information(this, "警告", "该账号不存在！");
            isExist=false;
            break;
        }
        isExist=true;
    }

    if(!query.next()){
        isExist=true;
    }
    if(isExist){
        QString sql=QString("insert into grade(Id,name,class,gaoshu,Eg,Com,Cplus)values('%1','%2','%3','%4','%5','%6','%7')").arg(addId).arg(addname).arg(addclass).arg(addGs).arg(addEg).arg(addCom).arg(addC);
        query.exec(sql);
        QMessageBox::information(this, "温馨提示", "恭喜，学号："+addId+"成绩更新成功");
        qDebug()<<addId+"成绩更新成功";
        this->close();
    }

}


void Addgrade::on_pushButton_cannal_clicked()
{
    this->close();
    Addmin *a=new Addmin;
    a->show();
}
