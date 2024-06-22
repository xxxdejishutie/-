#ifndef CWARNING_H
#define CWARNING_H

#include <QWidget>

namespace Ui {
class CWarning;
}

class CWarning : public QWidget
{
    Q_OBJECT

public:
    explicit CWarning(QWidget *parent = 0);
    ~CWarning();

    Ui::CWarning *ui;
    void set_pic();
private slots:
    void on_pushButton_clicked();
};

#endif // CWARNING_H
