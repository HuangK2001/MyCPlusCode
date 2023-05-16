#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString strRes = "";
    float fRes = ui->lineEdit->text().toFloat() +
                 ui->lineEdit_2->text().toFloat();
    strRes = QString( "%1" ).arg(fRes);
    ui->lineEdit_3->setText(strRes);

}

void Dialog::on_pushButton_2_clicked()
{
    QString strRes = "";
    float fRes = ui->lineEdit->text().toFloat() -
                 ui->lineEdit_2->text().toFloat();
    strRes = QString( "%1" ).arg(fRes);
    ui->lineEdit_3->setText(strRes);
}

void Dialog::on_pushButton_3_clicked()
{
    QString strRes = "";
    float fRes = ui->lineEdit->text().toFloat() *
                 ui->lineEdit_2->text().toFloat();
    strRes = QString( "%1" ).arg(fRes);
    ui->lineEdit_3->setText(strRes);
}

void Dialog::on_pushButton_4_clicked()
{
    QString strRes = "";
    float fRes = ui->lineEdit->text().toFloat() /
                 ui->lineEdit_2->text().toFloat();
    strRes = QString( "%1" ).arg(fRes);
    ui->lineEdit_3->setText(strRes);
}

void Dialog::on_pushButton_5_clicked()
{
    QString str=ui->lineEdit->text();
    bool ok;
    int val=str.toInt(&ok,10);
    str=QString::number(val,2);
    ui->lineEdit_3->setText(str);
}

void Dialog::on_pushButton_6_clicked()
{
    QString str=ui->lineEdit->text();
    bool ok;
    int val=str.toInt(&ok,10);
    str=QString::number(val,8);
    ui->lineEdit_3->setText(str);
}

void Dialog::on_pushButton_7_clicked()
{
    QString str=ui->lineEdit->text();
    bool ok;
    int val=str.toInt(&ok,10);
    str=QString::number(val,16);
    str = str.toUpper();
    ui->lineEdit_3->setText(str);
}
