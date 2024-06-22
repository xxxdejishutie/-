#include "ckernel.h"
#include<QDebug>
#include<iostream>

ckernel::ckernel(QObject *parent):QObject(parent)
{
    qDebug()<<__func__;
    m_pUdp=new udp;

    if(!m_pUdp->initNet()){
        qDebug()<<"打开网络失败";
        exit(0);
    }
    //给登录&注册窗口new对象
    //绑定接收处理所有数据的信号和槽函数
    connect(m_pUdp,SIGNAL(SIG_readyData(char*,int,long)),
            this,SLOT(slot_readyData(char*,int,long)));
    m_pNet->SendData(" hello",sizeof(" hello"),90);
}
ckernel::~ckernel(){
    qDebug()<<__func__;
    if(m_pNet){
        m_pNet->UnInitNet();
        delete m_pNet;
        m_pNet=NULL;
    }
}

void ckernel::slot_readyData(char *buf, int nLen, long lFrom)
{
    qDebug()<<__func__;
    qDebug()<<buf;

    //    //取出协议头
    //    PackType type=*(PackType*)buf;
    //    //取出协议头判断哪个是结构体，走哪个处理函数

    //    if(type>_PROTOCOL_BASE&&type<=_PROTOCOL_BASE+_DEF_PROTOCOL_COUNT){
    //        //计算数组下标
    //        int index=type-_PROTOCOL_BASE-1;
    //        //取出函数指针
    //        PFUN pf=m_mapProtocol[index];
    //        //调用函数
    //        if(pf){
    //            (this->*pf)(buf,nLen,lFrom);
    //        }else{
    //            qDebug()<<"函数指针为空， type"<<type;
    //        }
    //    }else{
    //        qDebug()<<"type"<<type;
    //    }

    //    //回收接收数据的空间
    //    delete[] buf;
}
