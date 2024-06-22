#include "cwarning.h"
#include "ui_cwarning.h"
#include"udp.h"
extern udp* pNet;
CWarning::CWarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWarning)
{
    ui->setupUi(this);

}

CWarning::~CWarning()
{
    delete ui;
}

void CWarning::on_pushButton_clicked()
{
    this->hide();
    pNet->sendData("7",2,0);
    sleep(0.25);
    pNet->sendData("7",2,0);
    pNet->sendData("7",2,0);
    pNet->sendData("7",2,0);
    sleep(0.25);
    pNet->sendData("7",2,0);
    //pNet->sendData("7",2,0);

}
void CWarning::set_pic(){
    qDebug()<<__func__;
    QPixmap pixmap("D:/QT/SmartHome/received_image.jpg");
     ui->label->setPixmap(pixmap);
     ui->label->setScaledContents(true);
     ui->label->show();
}


