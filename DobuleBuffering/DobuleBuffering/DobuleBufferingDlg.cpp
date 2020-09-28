
// DobuleBufferingDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "DobuleBuffering.h"
#include "DobuleBufferingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDobuleBufferingDlg 대화 상자



CDobuleBufferingDlg::CDobuleBufferingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOBULEBUFFERING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDobuleBufferingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDobuleBufferingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD_IMG, &CDobuleBufferingDlg::OnBnClickedBtnLoadImg)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CDobuleBufferingDlg 메시지 처리기

BOOL CDobuleBufferingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CDobuleBufferingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CDobuleBufferingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CDobuleBufferingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDobuleBufferingDlg::OnBnClickedBtnLoadImg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OpenImage();
}

void CDobuleBufferingDlg::OpenImage()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		strPath = fileDlg.GetPathName();

		m_img.Load(strPath);
	}
}

void CDobuleBufferingDlg::OnDrawImage()
{
	// Picture Control DC 얻기
	CClientDC dc(GetDlgItem(IDC_PC_IMG));

	// Picture Control 크기 얻기
	CRect rect;
	GetDlgItem(IDC_PC_IMG)->GetClientRect(&rect);

	CDC bufDC;
	CBitmap* pOldBitmap, bitmap;

	// Picture Control DC와 호환되는 새로운 CDC 생성 (임시 버퍼 생성)
	bufDC.CreateCompatibleDC(&dc);

	// Picture COntrol과 크기가 동일한 비트맵을 생성
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	// 직전에 생성한 비트맵을 선택함과 동시에 pOldBitmap에 보존.
	pOldBitmap = bufDC.SelectObject(&bitmap);

	// 임시 버퍼에 검은색으로 채움.
	bufDC.PatBlt(0, 0, rect.Width(), rect.Height(), BLACKNESS);

	// 임시 버퍼에 그리는 동작을 수행
	
	DrawImage(&bufDC);
	if (m_rectStart.x != 0 && m_rectStart.y != 0)
	{
		DrawRect(&bufDC);
	}
	

	// 임시 버퍼를 Picture Control에 그림
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bufDC, 0, 0, SRCCOPY);

	// 이전 비트맵으로 재설정
	bufDC.SelectObject(pOldBitmap);

	// 생성한 리소스 해제
	bufDC.DeleteDC();
	bitmap.DeleteObject();
}

void CDobuleBufferingDlg::DrawImage(CDC* pDC)
{
	CRect rect;
	GetDlgItem(IDC_PC_IMG)->GetClientRect(&rect);

	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	m_img.Draw(pDC->GetSafeHdc(), rect);
}

void CDobuleBufferingDlg::DrawRect(CDC* pDC)
{
	CRect rect;
	GetDlgItem(IDC_PC_IMG)->GetClientRect(&rect);

	CPen* pOldPen, pen;
	CBrush* pOldBrush, brush;
	pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	brush.CreateStockObject(NULL_BRUSH);

	pOldPen = pDC->SelectObject(&pen);
	pOldBrush = pDC->SelectObject(&brush);	

	pDC->Rectangle(CRect(m_rectStart.x, m_rectStart.y, m_rectEnd.x, m_rectEnd.y));

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	brush.DeleteObject();
	pen.DeleteObject();
}



void CDobuleBufferingDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// Window 좌표계->Picture Control 좌표계 변환
	GetCursorPos(&point);
	GetDlgItem(IDC_PC_IMG)->ScreenToClient(&point);
	
	if (nFlags & MK_LBUTTON)
	{
		m_rectEnd = point;

		// CString strTmp;
		// strTmp.Format(_T("sX: %d, sY: %d // eX: %d, eY: %d\n"), m_rectStart.x, m_rectStart.y, m_rectEnd.x, m_rectEnd.y);
		// OutputDebugString(strTmp);

		OnDrawImage();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDobuleBufferingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// Window 좌표계 -> Picture Control 좌표계 변환
	GetCursorPos(&point);
	GetDlgItem(IDC_PC_IMG)->ScreenToClient(&point);
	m_rectStart = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDobuleBufferingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
}
