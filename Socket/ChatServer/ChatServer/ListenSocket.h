#pragma once
#include <afxsock.h>


class CListenSocket :
    public CAsyncSocket
{
public:
    // 연결된 클라이언트 소켓 객체를 관리하는 리스트 객체 선언
    CPtrList m_ptrChildSocketList;
    virtual void OnAccept(int nErrorCode);
    void CloseClientSocket(CSocket* pChild);
    void BroadCast(char* pszBuffer, int len);
};

