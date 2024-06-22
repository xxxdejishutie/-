#ifndef DOORDIALOG_H
#define DOORDIALOG_H
#include <QWidget>
#include"udp.h"
extern udp* pNet;
namespace Ui {
class doorDialog;
}

class doorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit doorDialog(QWidget *parent = 0);
    ~doorDialog();
private slots:
    void on_pb_yes_clicked();

private:
    Ui::doorDialog *ui;
};

#endif // DOORDIALOG_H
