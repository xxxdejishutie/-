#include "temprature.h"
#include "ui_temprature.h"
extern udp* pNet;
temprature::temprature(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::temprature)
{
    ui->setupUi(this);
}

temprature::~temprature()
{
    delete ui;
}

void temprature::on_pushButton_clicked()
{
    QString temp="0";
    temp += ui->spinBox->text();
    //pNet->sendData("0",2,0);
    pNet->sendData(const_cast<char*> (temp.toStdString().c_str()),2,0);
    this->close();
}
