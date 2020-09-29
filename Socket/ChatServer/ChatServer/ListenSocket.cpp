#include "pch.h"


// Ŭ���̾�Ʈ�� ���� ��û�� �� ���� ȣ��Ǵ� �Լ�
void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	/* 
		Ŭ���̾�Ʈ�� ������ �ڼ��� ��ü�� �����Ͽ�
		Ŭ���̾�Ʈ�� ������ ����ϰ� �ڼ��ϰ� �����Ѵ�.
	*/
	CChildSocket* pChild = new CChildSocket;
	BOOL check = Accept(*pChild);

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("���� ��� ����!!"));
		return;
	}

	// CListenSocket ��ü�� �ּҸ� CChildSocket ��ü�� �˷��ֱ� ���� �Լ��� ȣ��
	pChild->SetListenSocket(this); // CChildSocket Ŭ������ ����ڰ� ������ �Լ�
	m_ptrChildSocketList.AddTail(pChild);

	// Ŭ���̾�Ʈ�� ������ ���� ����Ʈ�� ���
	CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();

	pMain->m_ListForChat.AddString(_T("���� ���� ���."));
	pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount()-1);

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::CloseClientSocket(CSocket* pChild)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
	POSITION pos;
	pos = m_ptrChildSocketList.Find(pChild);
	if (pos != NULL)
	{
		if (pChild != NULL)
		{
			// Ŭ���̾�Ʈ�� ����� �ڽ� ������ �ݴ´�.
			pChild->ShutDown();
			pChild->Close();
		}
		// ����Ʈ���� ������ �� �޸𸮿��� �����Ѵ�.
		m_ptrChildSocketList.RemoveAt(pos);
		delete pChild;
	}
}


void CListenSocket::BroadCast(char* pszBuffer, int len)
{
	// TODO: ���⿡ ���� �ڵ� �߰�.
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
