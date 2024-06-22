#include "mainwindow.h"
#include <QApplication>
#include <qdebug.h>
#include "ckernel.h"
#include"sys/stat.h"
#include <ws2tcpip.h>
#include"winsock2.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include"doordialog.h"
#include<time.h>
using namespace  std;
udp* pNet = new udp;
bool light=false;
bool chuang=false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if(!pNet->initNet())
    {
        cout<<"init error"<<endl;
    }
    char* buf = new char[1024];
    buf="7";
    if(!pNet->sendData(buf,sizeof(buf),0)){
        cout<<"send error"<<endl;
    }



//    //展示代码
//        // 创建一个QLabel
//           QLabel label;

//           // 加载图像并将其转换为QPixmap
//           QPixmap pixmap("D:/QT/SmartHome/received_image.jpg");

//           // 将QPixmap设置为QLabel的背景
//           label.setPixmap(pixmap);

//           // 调整QLabel大小以适应图像
//           label.setScaledContents(true);

//           // 显示QLabel
//           label.show();



    return a.exec();
}
