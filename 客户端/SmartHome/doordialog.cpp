#include "doordialog.h"
#include "ui_doordialog.h"

#include<QString>
#include<QDebug>
#include<QMessageBox>
extern udp* pNet;
using namespace std;
doorDialog::doorDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doorDialog)
{
    ui->setupUi(this);
}

doorDialog::~doorDialog()
{
    delete ui;
}

void doorDialog::on_pb_yes_clicked()
{
    QString pass=ui->ed_password->text();
    if(pass=="12345"){
        QMessageBox::about(NULL, "提示", "密码正确，已开门");
        pNet->udp::sendData("5",2,0);
        sleep(0.25);
         pNet->udp::sendData("5",2,0);
        ui->ed_password->clear();
        this->hide();
    }else{
         QMessageBox::about(NULL, "提示", "密码错误");
    }
}
