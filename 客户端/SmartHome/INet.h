#pragma once
#include<iostream>
#include<WinSock2.h>

//#pragma comment(lib,"Ws2_32.lib")
using namespace std;
class INet {
public:
    INet() {}
    virtual ~INet() {}
	virtual bool InitNet() = 0;
	virtual void UnInitNet() = 0;
	virtual bool SendData(char* buf,int nLen,long lSend) = 0;
protected:
	virtual void RecvData() = 0;
};
