#ifndef TEMPRATURE_H
#define TEMPRATURE_H
#include"udp.h"
#include <QWidget>

namespace Ui {
class temprature;
}


class temprature : public QWidget
{
    Q_OBJECT

public:
    explicit temprature(QWidget *parent = 0);
    ~temprature();

private slots:
    void on_pushButton_clicked();

private:
    Ui::temprature *ui;
};

#endif // TEMPRATURE_H
