// XCheat.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "XCheat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CXCheatApp

BEGIN_MESSAGE_MAP(CXCheatApp, CWinApp)
END_MESSAGE_MAP()


// CXCheatApp construction

CXCheatApp::CXCheatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CXCheatApp object

CXCheatApp theApp;


// CXCheatApp initialization
HANDLE g_hUIThread;
HANDLE g_hFreeThread;

void UIThread(void* pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HINSTANCE hOldIns = AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);


	CMainDlg* pMainDlg = new CMainDlg();

	pMainDlg->DoModal();

	delete pMainDlg;
	pMainDlg = nullptr;

	g_hFreeThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, theApp.m_hInstance, 0, 0);
	CloseHandle(g_hFreeThread);

	AfxSetResourceHandle(hOldIns);
}

BOOL CXCheatApp::InitInstance()
{
	CWinApp::InitInstance();

	g_hUIThread = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UIThread, 0, 0, 0);
	CloseHandle(g_hUIThread);

	return TRUE;
}