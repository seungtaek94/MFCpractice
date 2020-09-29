#pragma once
#include <afxsock.h>

class CChildSocket :
    public CSocket
{
public:
    // 클라이언트 접속을 위해 대기하는 서버 소켓
    CAsyncSocket* m_pListenSocket;
    void SetListenSocket(CAsyncSocket* pSocket);
    virtual void OnClose(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
};

