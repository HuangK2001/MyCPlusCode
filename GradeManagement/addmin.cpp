#include "addmin.h"
#include "ui_addmin.h"
#include<addgrade.h>
#include<changeadmin.h>
#include<showgrade.h>
Addmin::Addmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Addmin)
{
    ui->setupUi(this);
}

Addmin::~Addmin()
{
    delete ui;
}

void Addmin::on_grade_manager_clicked()
{
    this->hide();
    Addgrade *A=new Addgrade;
    A->show();
}

void Addmin::on_Add_ddmin_clicked()
{
    this->hide();
   Changeadmin *c=new Changeadmin;
   c->show();
}

void Addmin::on_Add_stu_clicked()
{
    this->hide();
    Showgrade *s=new Showgrade;
    s->show();
}

void Addmin::on_quit_clicked()
{
    this->close();
}
