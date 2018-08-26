#pragma once
#include "afxcmn.h"

#include "TabSheet.h"
#include "Page1.h"
#include "Page2.h"
#include "Page3.h"
#include "Page4.h"
#include "Page5.h"
#include "Page6.h"
#include "Page7.h"
#include "Page8.h"
#include "Page9.h"

// CMainDlg dialog

class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CTabSheet _MainTab;

	CPage1 _Page1;
	CPage2 _Page2;
	CPage3 _Page3;
	CPage4 _Page4;
	CPage5 _Page5;
	CPage6 _Page6;
	CPage7 _Page7;
	CPage8 _Page8;
	CPage9 _Page9;
	virtual BOOL OnInitDialog();
};
