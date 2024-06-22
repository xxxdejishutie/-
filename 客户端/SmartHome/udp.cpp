#include "udp.h"
using namespace std;
#define _DEF_UDP_PROT 4322
#define _DEF_UDP_SERVER_IP "192.168.236.53"
udp::udp():m_bStop(false)
{
}
udp::~udp()
{
    uninitNet();
}

bool udp::initNet()
{
    qDebug()<<__func__;
    //加载库
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;


    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

        return false;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        return false;
    }

    udpsock = socket(AF_INET,SOCK_DGRAM,0);

    sockline.sin_family = AF_INET;
    sockline.sin_port = htons(_DEF_UDP_PROT);//与服务器端口号相同

    //sockline.sin_addr.S_un.S_addr = inet_addr("192.168.3.238");//服务器的IP地址
    sockline.sin_addr.S_un.S_addr = inet_addr(_DEF_UDP_SERVER_IP);


    //创建接收数据的线程
    m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
    return true;
}
unsigned __stdcall udp::RecvThread(void* lpVoid) {
    udp* pThis = (udp*)lpVoid;
    pThis->recvData();
    return 1;
}


void udp::uninitNet(){
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
    if (udpsock && INVALID_SOCKET != udpsock) {
        closesocket(udpsock);
    }
    //3.卸载库
    WSACleanup();

}
bool udp::sendData(char* buf, int nLen, long lSend){
    qDebug()<<__func__;
    int num = sendto(udpsock,buf,strlen(buf),0,(sockaddr*)&sockline,sizeof(sockline));
    if(num < 0)
    {
        qDebug() << "send udp faild " << num << endl;
        return false;
    }
    cout<<buf<<endl;
    return true;
}
void udp::recvData(){
    qDebug()<<__func__;
    char buf[30096] = "";
    int nlen = sizeof(sockline);
    QByteArray image_data;
    while(!m_bStop){
        int recvnum = recvfrom(udpsock,buf,sizeof(buf),0,(sockaddr*)&sockline,&nlen);
        if(recvnum > 0)
        {
            //            QByteArray image_data = buf;
            //            int cnt = 0;
            //            while(recvnum == 1024)
            //            {
            //                qDebug() << cnt << endl;
            //                cnt += 1024;
            //                char buf[30096] = "";
            //                recvnum = recvfrom(udpsock,buf,sizeof(buf),0,(sockaddr*)&sockline,&nlen);
            //                image_data.append(buf);
            //            }
            if(sizeof(buf)<1024){
                qDebug()<<buf;
            }else{
                // 保存收到的图片数据为文件
                qDebug() << recvnum <<"  buf len " << sizeof(buf)<< endl;
                QFile file("D:/QT/SmartHome/received_image.jpg");
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(buf,recvnum);
                    file.flush();
                    file.close();
                    qDebug() << "Image received and saved.";
                    Q_EMIT SIG_showpic();
                }
                else {
                    qDebug() << "Failed to open file for writing.";

                }
            }
        }
        if(recvnum<0){
            cout << "RecvData recv error" << WSAGetLastError() << endl;
        }
        //cout  << "recv complete" << endl;
    }
}
