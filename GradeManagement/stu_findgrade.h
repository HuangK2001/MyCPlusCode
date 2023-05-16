#ifndef STU_FINDGRADE_H
#define STU_FINDGRADE_H

#include <QWidget>

namespace Ui {
class Stu_findgrade;
}

class Stu_findgrade : public QWidget
{
    Q_OBJECT

public:
    explicit Stu_findgrade(QWidget *parent = nullptr);
    ~Stu_findgrade();

private slots:
    void on_find_grade_clicked();

    void on_quit_clicked();

private:
    Ui::Stu_findgrade *ui;
};

#endif // STU_FINDGRADE_H
