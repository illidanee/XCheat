#pragma once


// CPage3 dialog

class CPage3 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage3();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
