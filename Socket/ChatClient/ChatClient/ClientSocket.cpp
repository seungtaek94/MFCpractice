// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "ChatClient.h"
#include "ClientSocket.h"
#include "ChatClientDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	this->ShutDown();
	this->Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("Error: Disconnected from Server!"));
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	if (Receive(szBuffer, 1024) > 0)
	{
		CChatClientDlg* pMain = (CChatClientDlg*)AfxGetMainWnd();
		pMain->m_ListForChat.AddString(LPCTSTR(szBuffer));
		pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
