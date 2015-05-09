
// Friend Space.h : main header file for the Friend Space application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFriendSpaceApp:
// See Friend Space.cpp for the implementation of this class
//

class CFriendSpaceApp : public CWinApp
{
public:
	CFriendSpaceApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFriendSpaceApp theApp;
