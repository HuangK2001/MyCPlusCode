#ifndef SHOWGRADE_H
#define SHOWGRADE_H

#include <QWidget>

namespace Ui {
class Showgrade;
}

class Showgrade : public QWidget
{
    Q_OBJECT

public:
    explicit Showgrade(QWidget *parent = nullptr);
    ~Showgrade();

private slots:


    void on_pushButton_Find_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_return_2_clicked();

private:
    Ui::Showgrade *ui;
};

#endif // SHOWGRADE_H
