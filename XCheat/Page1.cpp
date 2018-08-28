// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "XCheat.h"
#include "Page1.h"
#include "afxdialogex.h"

#include "CheatGame.h"

// CPage1 dialog

IMPLEMENT_DYNAMIC(CPage1, CDialogEx)

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE9, pParent)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CDialogEx)
	ON_BN_CLICKED(IDC_START, &CPage1::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CPage1::OnBnClickedStop)
END_MESSAGE_MAP()


// CPage1 message handlers

CCheatGame g_CheatGame;
void CPage1::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here

	g_CheatGame.Init();
}

void CPage1::OnBnClickedStop()
{
	// TODO: Add your control notification handler code here

	g_CheatGame.Done();
}
