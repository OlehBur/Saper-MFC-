
// Saper.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "Saper.h"
#include "SaperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSaperApp

BEGIN_MESSAGE_MAP(CSaperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSaperApp construction

CSaperApp::CSaperApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSaperApp object

CSaperApp theApp;


// CSaperApp initialization

BOOL CSaperApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Activate "Windows Native" visual manager for enabling themes in MFC controls
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CSaperDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}



void Grass::Draw(CPaintDC& dc) {
	dc.Rectangle(x - size / 2, y - size / 2, x - size / 2, y - size / 2);
};


Bomb::Bomb(int x, int y, int size) {
	this->x = x;
	this->y = y;
	this->size = size;
};
void Bomb::Draw(CPaintDC& dc) {
	static CPen numbPen(PS_SOLID, 3, RGB(0, 0, 0));
	dc.SelectObject(&numbPen);
	dc.Rectangle(x - size / 2+10, y - size / 2+10, x - size / 2-10, y - size / 2-10);
};


VoidBlock::VoidBlock(int x, int y, int size) {
	this->x = x;
	this->y = y;
	this->size = size;
};
void VoidBlock::Draw(CPaintDC& dc) {
	static CPen numbPen(PS_SOLID, 2, RGB(62, 153, 186));
	dc.SelectObject(&numbPen);
	dc.Rectangle(x - size / 2, y - size / 2, x - size / 2, y - size / 2);
};

void Saper::GenericStartArtea(int r, int c) {
	for (int i = r - 1; i < r + 2; i++)
		for (int j = c - 1; j < c + 2; j++)
			pole[i][j] = 0;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			bombs = 0;
			if (pole[i][j] == 0) {
				for (int floor = -1; floor < 2; floor++)
					for (int col = -1; col < 2; col++)
						if((i+ floor )<9&&(j+col)<9 && -1 < (i + floor) && -1 < (j + col))
						if (pole[i + floor][j + col] == 10/* && (-1<(i+floor)<9) && (-1 < (j + col) < 9)*/)
							bombs++;
				pole[i][j] = bombs;
			}
		}
};

void Saper::Start() {
	currentFlagsCount = levelDifficulty * 4;
	cntAllBombs = 0;
	destroyedBlocks = 0;
	if (!isStart)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				grass[i][j] = false;
				flagsPole[i][j] = false;
			}
	score = 0;
	seconds = 0;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) {
				//if(!isStart)
					//if (x > (50 + i * 80) && y > (150 + j * 80) && x < (50 + i * 80 + 80) && y < (150 + j * 80 + 80)) {
					//	//isStart = true;
					//	pole[i][j] = 0;
					//}
				if(rand() % (1+levelDifficulty) == levelDifficulty){
					pole[i][j] = 10; 
					cntAllBombs++;
				}else
					pole[i][j] = 0;
			}
};

//void Saper::SecondDestroy(int r, int c) {
//	if(0<=r<9 && 0<=c<9)
//	for (int row = r - 1; row < r + 2; row++)
//		for (int col = c - 1; col < c + 2; col++)
//			if (row > -1 && col > -1 && row < 9 && col < 9) {
//				if (/*pole[row][col] != 0 && */!grass[row][col]) {
//					score += pole[row][col];
//					grass[row][col] = true;
//				}
//				/*else if (pole[row][col] == 0 && !grass[row][col])
//					SecondDestroy(row, col);*/
//			}
//};

void Saper::MultyDestroy(int r, int c) {
	if(0 <= r < 9 && 0 <= c < 9)
	for (int row = r - 1; row < r + 2; row++)
			for (int col = c - 1; col < c + 2; col++) 
				if (row > -1 && col > -1 && row < 9 && col < 9) {
					if (/*pole[row][col] != 0 && */!grass[row][col]) {
						score += pole[row][col];
						grass[row][col] = true;
						if (pole[row][col] == 0)
							MultyDestroy(row, col);
							//SecondDestroy(row, col);
					}
				}
};

void Saper::DrawNumber(CPaintDC& dc, int count, int color[]) {
	//CPen NumbPen(PS_SOLID, 2, RGB(color[0], color[1], color[2]));
	//dc.SelectObject(&NumbPen);
	//
	//dc.LineTo(numbers[6][0].x, numbers[6][0].y);
	//for (int point = 1; point < 6; point++)
	//	dc.MoveTo(numbers[6][point].x, numbers[6][point].y);
};

void Saper::Draw(CRect &rect, CPaintDC& dc) {
	int cntMines = 0;
	destroyedBlocks = 0;
	CPen bombPen(PS_SOLID, 5, RGB(70, 70, 70));
	CPen pen(PS_SOLID, 2, RGB(0, 107, 0));
	CPen dirtPen(PS_SOLID, 2, RGB(181, 114, 10));
	CBrush grassBrush, grassBrush1, cleanBrush, dirtBrush, dirtBrush1, greenBackg, bombBrush;
	grassBrush.CreateSolidBrush(RGB(0, 206, 7));
	grassBrush1.CreateSolidBrush(RGB(0, 178, 6));
	cleanBrush.CreateSolidBrush(RGB(240, 240, 240));// 169, 22));
	dirtBrush.CreateSolidBrush(RGB(255, 169, 22));
	dirtBrush1.CreateSolidBrush(RGB(216, 146, 27));
	greenBackg.CreateSolidBrush(RGB(56, 213, 67));
	bombBrush.CreateSolidBrush(RGB(124, 130, 179));

	dc.FillRect(rect, &greenBackg);

	/*dc.SelectObject(&bombPen);*/

	/*dc.SelectObject(&dirtBrush);
	dc.Rectangle(46, 146, 53 + 8*80 + 80, 153 + 8*80 + 80);*/

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (grass[i][j]) {
				dc.SelectObject(&dirtPen);
				((i + j) % 2 == 0) ? dc.SelectObject(&dirtBrush) : dc.SelectObject(&dirtBrush1);
				dc.Rectangle(50 + i * 80, 150 + j * 80, 50 + i * 80 + 80, 150 + j * 80 + 80);
			}


			if (pole[i][j] == 10) {
				dc.SelectObject(&bombBrush);
				dc.SelectObject(&bombPen);
				dc.Ellipse(70 + i * 80, 170 + j * 80, 30 + i * 80 + 80, 130 + j * 80 + 80);
			}
			else if (pole[i][j]) {
				dc.SelectObject(&cleanBrush);
				int color[3] = { pole[i][j] * 50, 0, pole[i][j] * 10 };
				//DrawNumber(dc, 6, color);
				
				CPen blockPen;
				CPen NumbPen;
				if(pole[i][j]<6){
				blockPen.CreatePen(PS_SOLID, 3, RGB(pole[i][j] * 50, 0, pole[i][j] * 10));
				NumbPen.CreatePen(PS_SOLID, 4, RGB(pole[i][j] * 50, 0, pole[i][j] * 10));
				} 
				else {
					NumbPen.CreatePen(PS_SOLID, 4, RGB(255- pole[i][j]*3,  pow(pole[i][j],2)*2, pow(pole[i][j],2.6)));
					blockPen.CreatePen(PS_SOLID, 3, RGB(255 - pole[i][j] * 3, pow(pole[i][j],2)*2, pow(pole[i][j],2.6)));
				}
				dc.SelectObject(&blockPen);
				dc.Rectangle(56 + i * 80, 156 + j * 80, 44 + i * 80 + 80, 144 + j * 80 + 80);
				dc.SelectObject(&NumbPen);

				cntMines = pole[i][j] - 1;
				dc.MoveTo(60 + 30 + i * 80 + numbers[cntMines][0].x * 8, 160 + 30 + j * 80 + numbers[cntMines][0].y * 8);
				for (int point = 1; point < 6; point++)
					if (numbers[cntMines][point].x != 3)
						dc.LineTo(60 + 30 + i * 80 + numbers[cntMines][point].x * 8, 160 + 30 + j * 80 + numbers[cntMines][point].y * 8);
				/*CPen blockPen(PS_SOLID, 3, RGB(pole[i][j] * 50, 0, pole[i][j]*10));
				dc.SelectObject(&blockPen);
				for(int numb=0; numb< pole[i][j]; numb++)
				dc.Rectangle(60 + i * 80+ numb*5, 160 + j * 80+ numb*5, 40 + i * 80 + 80- numb*5 , 140 + j * 80 + 80- numb *5);*/

			}
		}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			if (!grass[i][j]) {
				dc.SelectObject(&pen);
				((i + j) % 2 == 0) ?
					dc.SelectObject(&grassBrush) :
					dc.SelectObject(&grassBrush1);
				dc.Rectangle(50 + i * 80, 150 + j * 80, 50 + i * 80 + 80, 150 + j * 80 + 80);
			}
			else if(pole[i][j]!=10)
				destroyedBlocks++;
		}

	/*for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (grass[i][j])
				destroyedBlocks++;*/

	static int anim = 1;
	anim *=10;

};

void Saper::MsgBox(int winLose)
{
	if (!winLose) {
		game.isStart = false;
		//game.Start();
		switch (MessageBox(NULL, (LPCWSTR)L"    Ви програли! \nБажаєте почати наново?", (LPCWSTR)L"Ой лишенько...", MB_ICONSTOP | MB_RETRYCANCEL)) {
		case IDRETRY:
			game.isStart = false;
			game.Start();
			break;
		case IDCANCEL:
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
			return;
			break;
		}
	}
	else switch (MessageBox(NULL, (LPCWSTR)L"    Ви перемогли! \nБажаєте почати наново?", (LPCWSTR)L"Успіх!!!", MB_ICONASTERISK | MB_RETRYCANCEL)) {
	case IDRETRY:
		game.isStart = false;
		game.Start();
		break;
	case IDCANCEL:
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
		return;
		break;
	}
}