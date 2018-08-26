#pragma once


// CPage6 dialog

class CPage6 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage6)

public:
	CPage6(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage6();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
