#pragma once
#include <afxsock.h>

class CChildSocket :
    public CSocket
{
public:
    // Ŭ���̾�Ʈ ������ ���� ����ϴ� ���� ����
    CAsyncSocket* m_pListenSocket;
    void SetListenSocket(CAsyncSocket* pSocket);
    virtual void OnClose(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
};

