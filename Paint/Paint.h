
// Paint.h : Paint Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPaintApp:
// �йش����ʵ�֣������ Paint.cpp
//

class CPaintApp : public CWinApp
{
public:
	CPaintApp();
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
	afx_msg void OnAboutDialog();
};

extern CPaintApp theApp;
