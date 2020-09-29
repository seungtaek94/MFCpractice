#include "pch.h"



void CChildSocket::SetListenSocket(CAsyncSocket* pSocket)
{
	// TODO: 여기에 구현 코드 추가.
	m_pListenSocket = pSocket;
}

// 클라이언트 소켓이 닫히면 호출
void CChildSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);

	CAsyncSocket::OnClose(nErrorCode);
}

// 클라이언트가 데이터를 보내면 호출되는 함수
void CChildSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString tmp = _T(""), strIPAddress = _T("");
	UINT uuPortNumber = 0;

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	// 연결된 클라이언트의 IP주소와 포트 번호를 얻음
	GetPeerName(strIPAddress, uuPortNumber);
	// 실제 데이터를 수신
	int len;
	if ((len = Receive(szBuffer, 1024)) > 0)
	{
		// 데이터를 수신하였다면 받은 메시지를 리스트에 출력
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		tmp.Format(_T("[%s] : %s"), strIPAddress, szBuffer);
		pMain->m_ListForChat.AddString(tmp);
		pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount() - 1);

		// 연결된 모든 클라이언트에 해당 메시지를 전송
		CListenSocket* pServerSocket = (CListenSocket*)m_pListenSocket;
		pServerSocket->BroadCast(szBuffer, len);
	}
	CSocket::OnReceive(nErrorCode);
}
