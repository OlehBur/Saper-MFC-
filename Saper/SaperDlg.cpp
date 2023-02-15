
// SaperDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Saper.h"
#include "SaperDlg.h"
#include "afxdialogex.h"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Saper game;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CSaperDlg dialog



CSaperDlg::CSaperDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAPER_DIALOG, pParent)
	, checker(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, ListBox);
	DDX_Control(pDX, IDC_CHECK1, checkFlag);
	DDX_Check(pDX, IDC_CHECK1, checker);
}

BEGIN_MESSAGE_MAP(CSaperDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSaperDlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSaperDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK1, &CSaperDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CSaperDlg message handlers

BOOL CSaperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ListBox.AddString(_T("Легкий"));
	ListBox.AddString(_T("Помірний"));
	ListBox.AddString(_T("Важкий"));
	ListBox.SetCurSel(0);

//	checkFlag.
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSaperDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSaperDlg::OnPaint()
{
	UpdateData(TRUE);
	game.levelDifficulty = 3 - ListBox.GetCurSel();

	SetTimer(1, 1000, 0);
	CPaintDC dc(this); 
	CRect rect;
	GetClientRect(&rect);
	if (IsIconic())
	{
		// device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		/*int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);*/
		
		/*GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;*/
		//rect.left = 50;
		//rect.right = 50;
		//rect.top = 200;
		//rect.bottom = 50;
		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		game.Draw(rect, dc);
	/*	CPen pen(PS_SOLID, 2, RGB(0, 107, 0));
		CPen pen1(PS_SOLID, 3, RGB(0, 0, 0));
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				dc.SelectObject(&pen);
				dc.Rectangle(50 + i * 80, 150 + j * 80, 50 + i * 80 + 80, 150 + j * 80 + 80);
				if (rand() % 6 == 3) {
					dc.SelectObject(&pen1);
					dc.Rectangle(50 + 60 + i * 80, 150 + 60 + j * 80, 50 + i * 80+20, 150 + j * 80+20);
				}
			}*/
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSaperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSaperDlg::OnBnClickedButton1()
{
	game.isStart = false;
	game.Start();
	Invalidate();
}

afx_msg void CSaperDlg::OnTimer(UINT ID) {
	//string time;
	//static int seconds = 0;
	static TCHAR time[7] = { 0 };
	/*if (seconds < 60)*/
		game.seconds++;
	/*else if (seconds == 60) {
		minutes++;
		seconds = 0;	
	}*/
	_itot_s(game.seconds, time, _countof(time), 7);
	SetDlgItemText(IDC_STATIC1, time);
	//Invalidate();
}

//afx_msg void OnLButtonDown(UINT nFlags, CPoint point) {
//	if(MK_LBUTTON)
//		for (int i = 0; i < 9; i++)
//			for (int j = 0; j < 9; j++) {
//				if (point.x > (50 + i * 80) && point.y > (150 + j * 80) && point.x < (50 + i * 80 + 80) && point.y < (150 + j * 80 + 80))
//					game.grass[i][j] = true;
//			}
//}


void CSaperDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	static TCHAR score[10];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (point.x > (50 + i * 80) && point.y > (150 + j * 80) && point.x < (50 + i * 80 + 80) && point.y < (150 + j * 80 + 80)) {
				if (!game.grass[i][j]) 
					if (!game.isFlag){
					if (game.pole[i][j] != 10) {
						game.SetScore(game.pole[i][j]);
						if (game.destroyedBlocks == (81 - game.cntAllBombs)) {
							Invalidate();
							game.MsgBox(1);
						}
					}
					else {
						game.grass[i][j] = true;
						Invalidate();
						game.MsgBox(0);
					}
					game.grass[i][j] = true;
					}
					else {
						if (game.flagsPole[i][j] != 1) {//setflg
							game.currentFlagsCount--;
							game.flagsPole[i][j] = 1;
						}
						else {//dell flg
							game.currentFlagsCount++;
							game.flagsPole[i][j] = 0;
						}
					}
				_itot_s(game.GetScore(), score, _countof(score), 10);
				if (!game.isStart){
					game.Start();
					game.GenericStartArtea(i, j);
				game.isStart = true;
			}
				if (game.pole[i][j] == 0)
					game.MultyDestroy(i, j);
				SetDlgItemText(IDC_STATIC, score);
				Invalidate();
			}
		}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CSaperDlg::OnCbnSelchangeCombo1()
{
	game.isStart = false;
	game.Start();
	Invalidate();
}


void CSaperDlg::OnBnClickedCheck1()
{
	game.isFlag=checkFlag.GetCheck();
}
