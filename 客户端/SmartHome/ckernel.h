#ifndef CKERNEL_H
#define CKERNEL_H
#include "udp.h"
#include <QObject>
#include <QWidget>
#include"TcpClient.h"
class ckernel:public QObject
{Q_OBJECT

public:
    explicit ckernel(QObject* parent=0);
    ~ckernel();

public slots:
    //接收处理所有函数
    void slot_readyData(char* buf,int nLen,long lFrom);
public:
    udp* m_pUdp;
};

#endif // KERNEL_H
