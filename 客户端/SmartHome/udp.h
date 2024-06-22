#ifndef UDP_H
#define UDP_H
#include <qdebug.h>
#include"sys/stat.h"
#include <ws2tcpip.h>
#include"winsock2.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include<QPixmap>
#include<QLabel>
#include<QFile>

class udp:public QObject
{Q_OBJECT
public:
    udp();
    ~udp();
    bool initNet();
    bool sendData(char *buf, int nLen, long lSend);
protected:
    void uninitNet();
    void recvData();
    static unsigned __stdcall RecvThread(void *lpVoid);
    SOCKET udpsock;
    HANDLE m_handle;
    bool m_bStop;
    sockaddr_in sockline;
signals:
    void SIG_showpic();

};

#endif // UDP_H
