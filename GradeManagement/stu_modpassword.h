#ifndef STU_MODPASSWORD_H
#define STU_MODPASSWORD_H

#include <QWidget>

namespace Ui {
class Stu_modpassword;
}

class Stu_modpassword : public QWidget
{
    Q_OBJECT

public:
    explicit Stu_modpassword(QWidget *parent = nullptr);
    ~Stu_modpassword();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Stu_modpassword *ui;
};

#endif // STU_MODPASSWORD_H
