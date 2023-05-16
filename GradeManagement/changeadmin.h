#ifndef CHANGEADMIN_H
#define CHANGEADMIN_H

#include <QWidget>

namespace Ui {
class Changeadmin;
}

class Changeadmin : public QWidget
{
    Q_OBJECT

public:
    explicit Changeadmin(QWidget *parent = nullptr);
    ~Changeadmin();

private slots:
    void on_pushButton_add_clicked();

    void on_showadmin_clicked();

    void on_pushButton_del_clicked();

    void on_return_2_clicked();

private:
    Ui::Changeadmin *ui;
};

#endif // CHANGEADMIN_H
