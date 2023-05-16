#include "stu.h"
#include "ui_stu.h"
#include<stu_findgrade.h>
#include<stu_modpassword.h>
Stu::Stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stu)
{
    ui->setupUi(this);
}

Stu::~Stu()
{
    delete ui;
}

void Stu::on_pushButton_clicked()
{
    this->hide();
    Stu_findgrade *s=new Stu_findgrade;
    s->show();
}

void Stu::on_pushButton_2_clicked()
{
    this->hide();
    Stu_modpassword *S=new Stu_modpassword;
    S->show();
}

void Stu::on_pushButton_4_clicked()
{
    this->close();
}
