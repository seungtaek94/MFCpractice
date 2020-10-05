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
	CString strTmp;

	if (check == FALSE)
	{
		delete pChild;
		AfxMessageBox(_T("���� ��� ����!!"));
		return;
	}

	// CListenSocket ��ü�� �ּҸ� CChildSocket ��ü�� �˷��ֱ� ���� �Լ��� ȣ��
	pChild->SetListenSocket(this); // CChildSocket Ŭ������ ����ڰ� ������ �Լ�
	m_ptrChildSocketList.AddTail(pChild); // ����Ʈ�� Ŭ���̾�Ʈ ���� ����

	// Ŭ���̾�Ʈ�� ������ ���� ����Ʈ�� ���
	CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
	strTmp.Format(_T("Client (%d)"), (int)m_ptrChildSocketList.Find(pChild)); // Ŭ���̾�Ʈ ��ȣ(POSITION(�ּ�) ��)

	pMain->m_ListClient.AddString(strTmp); // Ŭ���̾�Ʈ�� �����Ҷ����� ����Ʈ�� Ŭ���̾�Ʈ �̸� �߰�
	pMain->m_ListForChat.AddString(strTmp + _T(" ���� ���� ���."));
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
		CChatServerDlg* pMain = (CChatServerDlg*)AfxGetMainWnd();
		CString strSocketList, strClientList;
		UINT indx = 0, posNum;
		
		pMain->m_ListClient.SetCurSel(0);

		// ���� ����Ǵ� Ŭ���̾�Ʈ ã��
		while (indx < pMain->m_ListClient.GetCount())
		{
			posNum = (int)m_ptrChildSocketList.Find(pChild);
			pMain->m_ListClient.GetText(indx, strClientList);
			strSocketList.Format(_T("%d"), posNum);

			// ���ϸ���Ʈ, Ŭ���̾�Ʈ����Ʈ�� ���ؼ� ���� Ŭ���̾�Ʈ ��ȣ(POSITION ��) ������ ����Ʈ���� ����
			if (strClientList.Find(strSocketList) != -1)
			{
				pMain->m_ListForChat.AddString(strClientList + _T(" ���� ����."));
				pMain->m_ListForChat.SetCurSel(pMain->m_ListForChat.GetCount() - 1);
				pMain->m_ListClient.DeleteString(indx);
				break;
			}
			indx++;
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
