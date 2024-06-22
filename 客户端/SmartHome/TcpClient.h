#pragma once
#include<WinSock2.h>
#include<iostream>
#include<QObject>

class TcpClientNet:public QObject{
    Q_OBJECT
public:
    TcpClientNet();
	~TcpClientNet();
	bool InitNet();
	void UnInitNet();
	bool SendData(char* buf, int nLen, long lSend);
    void DealData(char* buf, int nLen, long lFrom);
signals:
    void SIG_readyData(char* buf,int nLen,long lSend);

protected:
	static unsigned __stdcall RecvThread(void* lpVoid);
	void RecvData();
	SOCKET m_sock;
	HANDLE m_handle;
	bool m_bStop;
};
