
// Saper.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSaperApp:
// See Saper.cpp for the implementation of this class
//

class CSaperApp : public CWinApp
{
public:
	CSaperApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};




class Grass  {
	int x, y, size;
public:
	void Draw(CPaintDC& dc);
};

class Bomb {
	int x, y, size;
public:
	Bomb(int x, int y, int size);
	void Draw(CPaintDC& dc);
};

class VoidBlock {
	int x, y, size;
public:
	VoidBlock(int x, int y, int size);
	void Draw(CPaintDC& dc);
};

//class NumberBlock {
//	//int color[3];
//	POINT numbers[9][6] = {
//		{{-1,-1},{0,-2},{0, 2},		{0},{0},{0}},
//		{{-1,-1},{0,-2},{1,-1},{-1,2},{2,1},	 {-1,2}},
//		{{0,-2},{1,-1},{0,0},{1,1},{0,2},{-1,1}},
//		{{1,0},{-1,0},{1,-2},{1,2},		{1,2},{1,2}},
//		{{1,-2},{-1,-2},{-1,0},{1,0},{1,2},{-1,2}},
//		{{1,-2},{-1,-2},{1,-2},{1,0},{-1,0}},
//		{{-1,-2},{1,-2},{-1,2},{0,0},{-1,0},{1,0}},
//		{{0,-2},{1,-1},{-1,-2},{1,2},{-1,-1},{0,-2}},
//		{{},{},{},{},{},{}}
//	};
//	//NumberBlock(int count, int color[3]);
//	void DrawNumber(CPaintDC& dc, int count, int color[3]);
//};

class Saper {
	int bombs = 0,
		score = 0;
	/*void SecondDestroy(int r, int c);*/
	POINT numbers[9][6] = {
		{{-1,-1},{0,-2},{0, 2},		{3,0},{3,0},{3,0}}, //1
		{{-1,-1},{0,-2},{1,-1},{-1,2},{1,2},	{3,0}}, //2
		{{-1,-2},{1,-2},{0,-1},{1,1},{0,2},{-1,1}},     //3
		{{1,0},{-1,0},{1,-2},{1,2},		{3,2},{3,2}},	//4
		{{1,-2},{-1,-2},{-1,0},{1,0},{1,2},{-1,2}},		//5
		{{1,-2},{-1,-2},{-1,2},{1,2},{1,0},{-1,0}},		//6
		{{-1,-2},{1,-2},{-1,2},{0,0},{-1,0},{1,0}},		//7
		{{-1,-2},{1,-2},{-1,2},{1,2},{-1,-2},	{3,0}},	//8
		{{-1,2},{1,2},{1,-2},{-1,-2},{-1,0},{1,0}}		//9
	};
	void DrawNumber(CPaintDC& dc, int count, int color[]);
public:
	void MsgBox(int winLose);
	int seconds = 0,
		destroyedBlocks = 0,
		cntAllBombs = 0,
		levelDifficulty=3, 
		currentFlagsCount=0;
	bool isStart = false,
		isFlag=false;
	bool grass[9][9],
		flagsPole[9][9];
	int pole[9][9];
	void Start();
	void GenericStartArtea(int r, int c);
	void Draw(CRect &rect, CPaintDC& dc);
	void MultyDestroy(int r, int c);
	int GetScore() {
		return score;
	}
	void SetScore(int sc) {
		score += sc;;
	}
};

extern Saper game;
extern CSaperApp theApp;
