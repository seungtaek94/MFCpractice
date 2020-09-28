
// DobuleBufferingDlg.h: 헤더 파일
//

#pragma once


// CDobuleBufferingDlg 대화 상자
class CDobuleBufferingDlg : public CDialogEx
{
// 생성입니다.
public:
	CDobuleBufferingDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOBULEBUFFERING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CImage m_img;
	CString strPath;
	CPoint m_rectStart;
	CPoint m_rectEnd;

	void OpenImage();	// 이미지 객체 열기
	void OnDrawImage();	// Double Buffering 한 것을 실제로 그리는 작업.
	void DrawRect(CDC* pDC);	// 임시객체 내에 사각형을 그리는 작업.
	void DrawImage(CDC* pDC);	// 임시객체 내에 이미지를 그리는 작업.

	afx_msg void OnBnClickedBtnLoadImg();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
