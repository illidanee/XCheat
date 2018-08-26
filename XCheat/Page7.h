#pragma once


// CPage7 dialog

class CPage7 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage7)

public:
	CPage7(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage7();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
