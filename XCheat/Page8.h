#pragma once


// CPage8 dialog

class CPage8 : public CDialogEx
{
	DECLARE_DYNAMIC(CPage8)

public:
	CPage8(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPage8();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
