#include "timer.h"
#include "ui_timer.h"
#include<QDebug>
extern bool light;
extern bool chuang;
Timer::Timer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timer)
{
    ui->setupUi(this);
    //创建接收数据的线程
    //m_handletime = (HANDLE)_beginthreadex(NULL, 0, &TimeThread, this, 0, NULL);
    t1=new QTimer;
    t1->setInterval(500);
    t1->start();
    connect(t1, &QTimer::timeout, this, &Timer::CheckTime);
}
//unsigned __stdcall Timer::TimeThread(void* lpVoid) {
//    Timer* pThis = (Timer*)lpVoid;
//    pThis->CheckTime();
//    return 1;
//}

void Timer::CheckTime(){
    qDebug()<<__func__;
    //当前时间与现在时间比较 一样就发送数据
    //1获取系统时间

    QDateTime currentTime = QDateTime::currentDateTime();

    QString timeText = currentTime.toString("hh:mm:ss");
    //把时间放到LCD中
    ui->lcdNumber->setDigitCount(8);//设置为显示8位
    ui->lcdNumber->display(timeText);
    //sleep(1);
    QString timeClock = currentTime.toString("hh:mm");
    clockTriger(timeClock);
}

void Timer::clockTriger(QString timeText)
{
    while(!clockQueue.empty() && timeText == clockQueue.top())
    {
        qDebug() << "current clock run  " << timeText << endl;
        //发送闹钟信号
        //白天  闹钟响，拉开窗帘
        //晚上  闹钟响 打开灯
        QString time=timeText.left(2);
        if(time>"18"||time<"06"){
             pNet->sendData("8",2,0);
             if(!light)
              pNet->sendData("1",2,0);
        }else{
            pNet->sendData("8",2,0);
            if(!chuang)
            pNet->sendData("3",2,0);
        }
        clockClose();
        clockQueue.pop();
    }
    showClock();
}

void Timer::clockClose()
{
    msgBox.setText("您的闹钟响了！");
    msgBox.setStandardButtons(QMessageBox::Ok);
    int ret=msgBox.exec();
    if(ret==QMessageBox::Ok){
        pNet->sendData("9",2,0);
        msgBox.close();
    }
}

Timer::~Timer()
{
    delete ui;
}

void Timer::on_pushButton_clicked()
{
    auto clockTime = ui->timeEdit->text();
    if(clockTime[1] == ':')
    {
        QString str = "0";
        clockTime = str + clockTime;
    }
    qDebug() << clockTime << endl;
    this->clockQueue.push(clockTime);

    qDebug() << clockQueue.top() << " ";

    showClock();
    //cout << endl;


}


void Timer::showClock()
{
    ui->label_5->setText("未设置");
    ui->label_9->setText("未设置");
    ui->label_10->setText("未设置");
    ui->label_11->setText("未设置");
    qDebug() << "show clock" << endl;
    if(clockQueue.empty())
        return;
    QString showTime[4];
    showTime[0] = clockQueue.top();
    ui->label_5->setText(showTime[0]);
    clockQueue.pop();
    if(clockQueue.empty())
    {
        clockQueue.push(showTime[0]);
        return;
    }

    showTime[1] = clockQueue.top();
    ui->label_9->setText(showTime[1]);
    clockQueue.pop();
    if(clockQueue.empty())
    {
        clockQueue.push(showTime[0]);
        clockQueue.push(showTime[1]);
        return;
    }

    showTime[2] = clockQueue.top();
    ui->label_10->setText(showTime[2]);
    clockQueue.pop();
    if(clockQueue.empty())
    {
        clockQueue.push(showTime[0]);
        clockQueue.push(showTime[1]);
        clockQueue.push(showTime[2]);
        return;
    }


    showTime[3] = clockQueue.top();
    ui->label_11->setText(showTime[3]);
    clockQueue.pop();
        clockQueue.push(showTime[0]);
        clockQueue.push(showTime[1]);
        clockQueue.push(showTime[2]);
        clockQueue.push(showTime[3]);
        return;

}

void Timer::on_pushButton_2_clicked()
{
    if(!clockQueue.empty())
    {
        qDebug() << "current clock run  " << clockQueue.top() << endl;
        //发送闹钟信号
        pNet->sendData("8",2,0);
        clockClose();
        clockQueue.pop();
    }
    showClock();
}
