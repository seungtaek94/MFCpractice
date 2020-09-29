#pragma once
#include <afxsock.h>


class CListenSocket :
    public CAsyncSocket
{
public:
    // ����� Ŭ���̾�Ʈ ���� ��ü�� �����ϴ� ����Ʈ ��ü ����
    CPtrList m_ptrChildSocketList;
    virtual void OnAccept(int nErrorCode);
    void CloseClientSocket(CSocket* pChild);
    void BroadCast(char* pszBuffer, int len);
};

