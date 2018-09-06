// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "XCheat.h"
#include "Page1.h"
#include "afxdialogex.h"

#include "CheatGame.h"
#include "Helpers.h"

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
	ON_BN_CLICKED(IDC_BUTTON1, &CPage1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CPage1::OnBnClickedCheck1)
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


void CPage1::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	::MessageBox(0, L"123456", 0, MB_OK);
}

int
(WINAPI* Real_MessageBox)(
	HWND hWnd,
	LPCTSTR lpText,
	LPCTSTR lpCaption,
	UINT uType
	) = MessageBox;

int WINAPI MyMessage(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCWSTR lpText,
	_In_opt_ LPCWSTR lpCaption,
	_In_ UINT uType)
{
	lpText = L"abcdef";
	return Real_MessageBox(hWnd, lpText, lpCaption, uType);
}

void CPage1::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here

	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		CHelpers::HookFunction(&(PVOID&)Real_MessageBox, MyMessage);
	}
	else
	{
		CHelpers::UnHookFunction(&(PVOID&)Real_MessageBox, MyMessage);
	}
}
