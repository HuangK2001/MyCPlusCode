#ifndef ADDGRADE_H
#define ADDGRADE_H

#include <QWidget>

namespace Ui {
class Addgrade;
}

class Addgrade : public QWidget
{
    Q_OBJECT

public:
    explicit Addgrade(QWidget *parent = nullptr);
    ~Addgrade();

private slots:
    void on_pushButton_gengxincj_clicked();

    void on_pushButton_cannal_clicked();

private:
    Ui::Addgrade *ui;
};

#endif // ADDGRADE_H
