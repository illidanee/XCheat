#pragma once


// CPage2 dialog

class CPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
