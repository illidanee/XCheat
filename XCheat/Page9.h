#pragma once


// CPage9 dialog

class CPage9 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage9)

public:
	CPage9(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage9();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
