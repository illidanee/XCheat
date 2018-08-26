// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XCheat.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg dialog

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAINDLG, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAINTAB, _MainTab);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg message handlers


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	_MainTab.AddPage(L"IDD_PAGE1", &_Page1, IDD_PAGE1);
	_MainTab.AddPage(L"IDD_PAGE2", &_Page2, IDD_PAGE2);
	_MainTab.AddPage(L"IDD_PAGE3", &_Page3, IDD_PAGE3);
	_MainTab.AddPage(L"IDD_PAGE4", &_Page4, IDD_PAGE4);
	_MainTab.AddPage(L"IDD_PAGE5", &_Page5, IDD_PAGE5);
	_MainTab.AddPage(L"IDD_PAGE6", &_Page6, IDD_PAGE6);
	_MainTab.AddPage(L"IDD_PAGE7", &_Page7, IDD_PAGE7);
	_MainTab.AddPage(L"IDD_PAGE8", &_Page8, IDD_PAGE8);
	_MainTab.AddPage(L"IDD_PAGE9", &_Page9, IDD_PAGE9);
	_MainTab.Show();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
