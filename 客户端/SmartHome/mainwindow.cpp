#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"ckernel.h"
#include<iostream>
#include<QDateTime>
#include<QString>
using namespace std;
extern bool light;
extern bool chuang;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //新建开门窗口
    m_pdoor=new doorDialog;
    m_pwarning=new CWarning;
    m_ptem=new temprature;
    // 将CustomWindow对象作为中心部件
          // setCentralWidget(m_pwarning);
    //定时
    m_ptimedlg=new Timer;
    if(!connect(pNet,SIGNAL(SIG_showpic()),
            this,SLOT(slot_showpic()))){
        cout << "connect error" << WSAGetLastError() << endl;
    }
    //connect(pNet,&udp::SIG_showpic,this,&slot_showpic);
}

MainWindow::~MainWindow()
{
    delete ui;
}




//开门
void MainWindow::on_pb_door_clicked()
{
    m_pdoor->show();
}

void MainWindow::on_pb_light_clicked()
{
    if(light==false){
        pNet->sendData("1",2,0);//发送打开灯光
        sleep(0.25);
        pNet->sendData("1",2,0);//发送打开灯光
        light=true;
        ui->pb_light->setText("关闭灯光");
    }else{
        pNet->sendData("2",2,0);//发送关闭灯光
        sleep(0.25);
        pNet->sendData("2",2,0);//发送关闭灯光
        light=false;
        ui->pb_light->setText("打开灯光");
    }
}

void MainWindow::on_pb_chuang_clicked()
{
    if(chuang==false){
        pNet->sendData("3",2,0);//发送打开窗帘
        sleep(0.25);
        pNet->sendData("3",2,0);//发送打开窗帘
        chuang=true;
        ui->pb_chuang->setText("关闭窗帘");
    }else{
        pNet->sendData("4",2,0);//发送关闭窗帘
        sleep(0.25);
        pNet->sendData("4",2,0);//发送关闭窗帘
        chuang=false;
        ui->pb_chuang->setText("打开窗帘");
    }
}

void MainWindow::on_pb_morning_clicked()
{
    m_ptimedlg->show();
    //设置时间
    //时间到了发送
    //pNet->sendData("8",2,0);
}

void MainWindow::slot_showpic()
{
    //qDebug()<<__func__;
    //m_pwarning->ui->lable->setPixmap(pixmap);
    m_pwarning->set_pic();
    m_pwarning->show();
}

void MainWindow::on_pb_night_clicked()
{
    pNet->sendData("2",2,0);//发送关闭灯光
    sleep(0.25);
     pNet->sendData("2",2,0);//发送关闭灯光
}

void MainWindow::on_pb_du_clicked()
{
    m_ptem->show();
}
