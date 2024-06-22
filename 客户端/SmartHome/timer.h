#ifndef TIMER_H
#define TIMER_H
#include"sys/stat.h"
#include <ws2tcpip.h>
#include"winsock2.h"
#include <unistd.h>
#include <QWidget>
#include<QTimer>
#include<queue>
#include"udp.h"
#include<QMessageBox>
namespace Ui {
class Timer;
}

extern udp* pNet;
class Timer : public QWidget
{
    Q_OBJECT

public:
    explicit Timer(QWidget *parent = 0);
    ~Timer();
    void CheckTime();
    void showClock();
    void clockTriger(QString);
    QTimer* t1;
    void clockClose();
protected:
    static unsigned __stdcall TimeThread(void *lpVoid);
    HANDLE m_handletime;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Timer *ui;
    std::priority_queue<QString,std::vector<QString>,std::greater<QString>> clockQueue;
    QMessageBox msgBox;
};

#endif // TIMER_H
