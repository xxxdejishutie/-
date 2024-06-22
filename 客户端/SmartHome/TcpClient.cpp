#include "TcpClient.h"
#include<iostream>
#include<WinSock2.h>
#include <sys/types.h>
#include<QDebug>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define _DEF_TCP_PROT (1237)
#define _DEF_TCP_SERVER_IP ("192.168.124.53")
TcpClientNet::TcpClientNet():m_sock(INVALID_SOCKET), m_handle(NULL),m_bStop(false){

}
TcpClientNet::~TcpClientNet() {
    UnInitNet();
}

bool TcpClientNet::InitNet() {
    //1、加载库
    WORD wVersion = MAKEWORD(2, 2);//制造一个word类型的数据
    WSAData data;

    int error = WSAStartup(wVersion, &data);
    if (error != 0) {
        cout << "WSAStartup error" << endl;
        return false;
    }
    //判断加载的库版本是否是2.2版本
    if (LOBYTE(data.wVersion) != 2 || HIBYTE(data.wVersion) != 2) {
        //已经加载库 但是版本错误 完成结束之前要先卸载库
        cout << "version error" << endl;
        return false;
    }
    else {
        cout << "WSAStartup succese" << endl;

    }

    //2.创建套接字
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == m_sock) {
        cout << "socket error" << WSAGetLastError() << endl;
        //已经加载库 完成结束之前要先卸载库
        return false;
    }
    else {
        cout << "socket  succese" << endl;


    }

    //连接
    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(_DEF_TCP_PROT);
    addrServer.sin_addr.S_un.S_addr = inet_addr(_DEF_TCP_SERVER_IP);
    int serverSize = sizeof(addrServer);
    int err = ::connect(m_sock, (sockaddr*)&addrServer, serverSize);
    if (err == SOCKET_ERROR) {
        cout << "connect fail" << WSAGetLastError() << endl;
        return 1;
    }
    else {
        cout << "connect success" << endl;
    }
    //创建接收数据的线程
    m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
    return true;
}

unsigned __stdcall TcpClientNet::RecvThread(void* lpVoid) {
    TcpClientNet* pThis = (TcpClientNet*)lpVoid;
    pThis->RecvData();
    return 1;
}
void TcpClientNet::UnInitNet() {
    //1.回收内核空间（结束线程和关闭句柄）
    m_bStop = true;
    if (m_handle) {
        if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 100)) {
            TerminateThread(m_handle,-1);
        }
        CloseHandle(m_handle);
        m_handle = NULL;
    }
    //2.关闭套接字
    if (m_sock && INVALID_SOCKET != m_sock) {
        closesocket(m_sock);
    }
    //3.卸载库
    WSACleanup();
}
bool TcpClientNet::SendData(char* buf, int nLen, long lSend) {
    //1.判断参数是否合法
    if (!buf || nLen <= 0) {
        cout << "TcpClientNet::SendData 参数错误" << WSAGetLastError() <<endl;
        return false;
    }
//    //2.先发包大小
//    if (send(m_sock, (char*)&nLen, sizeof(int),0) <= 0) {
//        cout<<"TcpClientNet::SendData send error:" << WSAGetLastError() << endl;
//        return false;
//    }
    //3.再发包内容
    if (send(m_sock, buf, nLen, 0) <= 0) {
        cout << "TcpClientNet::SendData send error:" << WSAGetLastError() << endl;
        return false;

    }
    return true;
}

void TcpClientNet::RecvData() {
    qDebug()<<__func__;
    int nPackSize = 0;
    int nRecvNum = 0;
    //记录当前累计接收到多少数据
    int nOffset = 0;
    char* buf=new char[1024];
    qDebug()<<"m_bStop"<<m_bStop;
    nRecvNum = recv(m_sock, buf, nPackSize, 0);

     qDebug()<<QString::fromUtf8(buf);
     if(nRecvNum<0)
         cout << "TcpClientNet::RecvData recv error" << WSAGetLastError() << endl;
//    while (!m_bStop) {
//        //1.接受包大小
//        nRecvNum = recv(m_sock, (char*)&nPackSize, sizeof(int), 0);
//        if (nRecvNum > 0) {
//            qDebug()<<"size";
//            //2、按照包大小new接收数据的空间
//            char* buf = new char[nPackSize];

//            //3、接受包内容
//            nOffset = 0;
//            while (nPackSize > 0) {
//                qDebug()<<"content";
//                nRecvNum = recv(m_sock, buf + nOffset, nPackSize, 0);
//                if (nRecvNum > 0) {
//                    nOffset += nRecvNum;
//                    nPackSize -= nRecvNum;
//                }
//                else {
//                    cout<<"TcpClientNet::RecvData recv error"<< WSAGetLastError() << endl;
//                    return;
//                }
//            }
//            //4.接收数据成功
//            DealData(buf, nOffset, m_sock);
//        }
//        else {
//            cout << "TcpClientNet::RecvData recv error" << WSAGetLastError() << endl;
//            break;
//        }
//    }
}
void TcpClientNet::DealData(char* buf, int nLen, long lFrom) {
    qDebug()<<__func__;

    Q_EMIT SIG_readyData(buf,nLen,lFrom);
}
