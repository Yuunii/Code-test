
// MFCApplication2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
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


// CMFCApplication2Dlg 대화 상자



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X1, m_EditX1);
	DDX_Control(pDX, IDC_EDIT_Y1, m_EditY1);
	DDX_Control(pDX, IDC_EDIT_X2, m_EditX2);
	DDX_Control(pDX, IDC_BUTTON_DRAW, m_DrawButton);
	DDX_Control(pDX, IDC_BUTTON_ACTION, m_ActionButton);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_OpenButton);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DRAW, &CMFCApplication2Dlg::OnDrawButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ACTION, &CMFCApplication2Dlg::OnActionButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication2Dlg::OnOpenButtonClicked)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기

BOOL CMFCApplication2Dlg::OnInitDialog()
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

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		if (!m_Image.IsNull()) // 이미지가 로드되었을 경우
		{
			// 이미지 크기
			int imgWidth = m_Image.GetWidth();
			int imgHeight = m_Image.GetHeight();

			// 다이얼로그에 이미지 출력
			m_Image.Draw(dc.GetSafeHdc(), 50, 50, imgWidth, imgHeight);

			// 중심 좌표 구하기 (이미지의 중앙)
			int centerX = 50 + imgWidth / 2;
			int centerY = 50 + imgHeight / 2;

			// X 모양 그리기
			CPen pen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간색 X 표시
			dc.SelectObject(&pen);
			dc.MoveTo(centerX - 10, centerY - 10);
			dc.LineTo(centerX + 10, centerY + 10);
			dc.MoveTo(centerX + 10, centerY - 10);
			dc.LineTo(centerX - 10, centerY + 10);

			// 좌표 텍스트 출력
			CString strCoords;
			strCoords.Format(_T("(%d, %d)"), centerX, centerY);
			dc.TextOutW(centerX + 15, centerY - 5, strCoords);
		}
		else
		{
			CDialogEx::OnPaint();
		}
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
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Draw 버튼 클릭 시 원을 그리는 기능
void CMFCApplication2Dlg::OnDrawButtonClicked()
{
	CString strX1, strY1;
	m_EditX1.GetWindowText(strX1);
	m_EditY1.GetWindowText(strY1);

	int x1 = _ttoi(strX1);
	int y1 = _ttoi(strY1);

	// 랜덤한 반지름 생성
	int radius = rand() % 50 + 10;

	CClientDC dc(this); // 그리기 위한 디바이스 컨텍스트
	CBrush brush(RGB(0, 0, 255)); // 파란색 원
	dc.SelectObject(&brush);
	dc.Ellipse(x1 - radius, y1 - radius, x1 + radius, y1 + radius);
}

// Action 버튼 클릭 시 원을 이동시키면서 저장하는 기능
void CMFCApplication2Dlg::OnActionButtonClicked()
{
	CString strX1, strY1, strX2, strY2;
	m_EditX1.GetWindowText(strX1);
	m_EditY1.GetWindowText(strY1);
	m_EditX2.GetWindowText(strX2);
	m_EditY2.GetWindowText(strY2);

	int x1 = _ttoi(strX1);
	int y1 = _ttoi(strY1);
	int x2 = _ttoi(strX2);
	int y2 = _ttoi(strY2);

	int steps = 10;  // 10번에 걸쳐 이동
	int dx = (x2 - x1) / steps;
	int dy = (y2 - y1) / steps;

	// 랜덤 반지름
	int radius = rand() % 50 + 10;

	CClientDC dc(this); // 그리기 위한 디바이스 컨텍스트
	CBrush brush(RGB(0, 255, 0)); // 녹색 원
	dc.SelectObject(&brush);

	// 이미지 저장 경로 설정
	CString folderPath = _T("image\\");
	CreateDirectory(folderPath, NULL);

	// 이동시키면서 저장
	for (int i = 0; i <= steps; ++i)
	{
		// 이전 원 지우기
		Invalidate();
		UpdateWindow();

		int newX = x1 + i * dx;
		int newY = y1 + i * dy;

		dc.Ellipse(newX - radius, newY - radius, newX + radius, newY + radius);

		// 파일 이름 지정 (예: image_0.bmp)
		CString fileName;
		fileName.Format(_T("%simage_%d.bmp"), folderPath, i);
		SaveBitmap(&dc, 300, 300, fileName);

		Sleep(200); // 약간의 딜레이 추가
	}
}

void CMFCApplication2Dlg::SaveBitmap(CDC* pDC, int width, int height, CString fileName)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, width, height);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	memDC.BitBlt(0, 0, width, height, pDC, 0, 0, SRCCOPY);

	CImage image;
	image.Attach((HBITMAP)bitmap.Detach());
	image.Save(fileName);

	memDC.SelectObject(pOldBitmap);
}

void CMFCApplication2Dlg::OnOpenButtonClicked()
{
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_FILEMUSTEXIST, _T("Image Files (*.bmp; *.jpg; *.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();

		if (m_Image.IsNull() == FALSE)
		{
			m_Image.Destroy();  // 이전 이미지를 메모리에서 해제
		}

		HRESULT hResult = m_Image.Load(filePath);
		if (SUCCEEDED(hResult))
		{
			Invalidate(); // 다시 그리기 위해 무효화
		}
		else
		{
			AfxMessageBox(_T("이미지 로드 실패!"));
		}
	}
}
