// XCheat.h : main header file for the XCheat DLL
//

#include "MainDlg.h"

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXCheatApp
// See XCheat.cpp for the implementation of this class
//

class CXCheatApp : public CWinApp
{
public:
	CXCheatApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
