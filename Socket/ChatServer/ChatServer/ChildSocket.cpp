#include "pch.h"



void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	m_pListenSocket = pSocket;
}

// Ŭ���̾�Ʈ ������ ������ ȣ��
void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);

	CAsyncSocket::OnClose(nErrorCode);
}

// Ŭ���̾�Ʈ�� �����͸� ������ ȣ��Ǵ� �Լ�
void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString tmp = _T(""), strIPAddress = _T("");
	UINT uuPortNumber = 0;

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	// ����� Ŭ���̾�Ʈ�� IP�ּҿ� ��Ʈ ��ȣ�� ����
	GetPeerName(strIPAddress, uuPortNumber);
	// ���� �����͸� ����
	int len;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		// �����͸� �����Ͽ��ٸ� ���� �޽����� ����Ʈ�� ���
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
		pMain->m_ListForChat.AddString(tmp);
		pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount() - 1);

		// ����� ��� Ŭ���̾�Ʈ�� �ش� �޽����� ����
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
	}
	CSocket::OnReceive(nErrorCode);
}
