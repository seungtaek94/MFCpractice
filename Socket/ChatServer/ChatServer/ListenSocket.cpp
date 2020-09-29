#include "pch.h"


// 클라이언트가 접속 요청을 해 오면 호출되는 함수
void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	/* 
		클라이언트와 연결할 자소켓 객체를 생성하여
		클라이언트의 접속을 허용하고 자소켓과 연결한다.
	*/
	CChildSocket* pChild = new CChildSocket;
	BOOL check = Accept(*pChild);

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("접속 허용 실패!!"));
		return;
	}

	// CListenSocket 개체의 주소를 CChildSocket 객체에 알려주기 위한 함수를 호출
	pChild->SetListenSocket(this); // CChildSocket 클래스에 사용자가 정의한 함수
	m_ptrChildSocketList.AddTail(pChild);

	// 클라이언트가 접속한 것을 리스트에 출력
	CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();

	pMain->m_ListForChat.AddString(_T("서버 접속 허용."));
	pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount()-1);

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL)
	{
		if (pChild != NULL)
		{
			// 클라이언트와 연결된 자식 소켓을 닫는다.
			pChild->ShutDown();
			pChild->Close();
		}
		// 리스트에서 제거한 후 메모리에서 해제한다.
		m_ptrChildSocketList.RemoveAt(pos);
		delete pChild;
	}
}


void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	// TODO: 여기에 구현 코드 추가.
	POSITION pos;
	pos = m_ptrChildSocketList.GetHeadPosition();
	CChildSocket* pChild = nullptr;

	while (pos != NULL)
	{
		pChild = (CChildSocket*)m_ptrChildSocketList.GetNext(pos);
		if (pChild != nullptr)
		{
			pChild->Send(pszBuffer, len * 2);
		}
	}
}
