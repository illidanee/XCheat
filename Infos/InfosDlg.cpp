
// InfosDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Infos.h"
#include "InfosDlg.h"
#include "afxdialogex.h"

#include <TlHelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInfosDlg dialog



CInfosDlg::CInfosDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INFOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInfosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInfosDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ, &CInfosDlg::OnBnClickedRead)
END_MESSAGE_MAP()


// CInfosDlg message handlers

BOOL CInfosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInfosDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInfosDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInfosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD GetModuleBaseAddress(const TCHAR* lpszModuleName, DWORD dwPID)
{
	MODULEENTRY32 ModuleEntry;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (!hSnapShot)
	{
		return 0;
	}

	ModuleEntry.dwSize = sizeof(ModuleEntry);

	BOOL RunModule = Module32First(hSnapShot, &ModuleEntry);

	while (RunModule)
	{
		if (!_tcscmp(lpszModuleName, ModuleEntry.szModule))
		{
			CloseHandle(hSnapShot);
			return (DWORD)(ModuleEntry.modBaseAddr);
		}
		RunModule = Module32Next(hSnapShot, &ModuleEntry);
	}

	CloseHandle(hSnapShot);
	return 0;
}

void CInfosDlg::OnBnClickedRead()
{
	// TODO: Add your control notification handler code here

	CString strBuffer, strTmp;
	HWND hWnd = ::FindWindow(NULL, _T("Counter-Strike Source"));
	if (hWnd == NULL)
	{
		MessageBox(_T("请打开游戏后重试"));
		return;
	}

	DWORD dwPID;
	HANDLE hProcess;
	GetWindowThreadProcessId(hWnd, &dwPID);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	DWORD dwServer;
	dwServer = GetModuleBaseAddress(_T("server_css.dll"), dwPID);

	strBuffer += strTmp;

	DWORD dwRoleObject;
	DWORD dwRoleHp;

	ReadProcessMemory(hProcess, (LPBYTE)(dwServer + 0x3B5D18), &dwRoleObject, 4, 0);
	ReadProcessMemory(hProcess, (LPBYTE)(dwRoleObject + 0x9C), &dwRoleHp, 4, 0);

	strTmp.Format(_T("Server模块地址:0x%X   人物基地址:0x%X   人物血量:%d \r\n"),
		dwServer,
		dwRoleObject,
		dwRoleHp);

	strBuffer += strTmp;

	float Pos[3];
	ReadProcessMemory(hProcess, (LPBYTE)(dwRoleObject + 0x348), &Pos, sizeof(Pos), 0);
	strTmp.Format(_T("人物坐标:x:%f    y:%f    z:%f \r\n"), Pos[0], Pos[1], Pos[2]);

	strBuffer += strTmp;

	SetDlgItemText(IDC_INFOS, strBuffer);
}
