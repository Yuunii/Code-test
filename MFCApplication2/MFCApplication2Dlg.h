
// MFCApplication2Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication2Dlg 대화 상자
class CMFCApplication2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CEdit m_EditX1;
	CEdit m_EditY1;
	CEdit m_EditX2;
	CEdit m_EditY2;
	CButton m_DrawButton;
	CButton m_ActionButton;
	CButton m_OpenButton;
	CImage m_Image;  // 이미지를 저장할 객체

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawButtonClicked();
	afx_msg void OnActionButtonClicked();
	afx_msg void OnOpenButtonClicked();
	DECLARE_MESSAGE_MAP()

	void SaveBitmap(CDC* pDC, int width, int height, CString fileName);
};
