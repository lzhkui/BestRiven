
// SP_Expert_PIV.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSP_Expert_PIVApp:
// �йش����ʵ�֣������ SP_Expert_PIV.cpp
//

class CSP_Expert_PIVApp : public CWinApp
{
public:
	CSP_Expert_PIVApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSP_Expert_PIVApp theApp;