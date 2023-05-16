#ifndef STU_H
#define STU_H

#include <QWidget>

namespace Ui {
class Stu;
}

class Stu : public QWidget
{
    Q_OBJECT

public:
    explicit Stu(QWidget *parent = nullptr);
    ~Stu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Stu *ui;
};

#endif // STU_H
