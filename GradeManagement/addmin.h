#ifndef ADDMIN_H
#define ADDMIN_H

#include <QWidget>

namespace Ui {
class Addmin;
}

class Addmin : public QWidget
{
    Q_OBJECT

public:
    explicit Addmin(QWidget *parent = nullptr);
    ~Addmin();

private slots:
    void on_grade_manager_clicked();

    void on_Add_ddmin_clicked();

    void on_Add_stu_clicked();

    void on_quit_clicked();

private:
    Ui::Addmin *ui;
};

#endif // ADDMIN_H
