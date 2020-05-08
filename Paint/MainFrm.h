
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "afxext.h"
#include "ColorPanel.h"
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;   //������
	CStatusBar        m_wndStatusBar; //״̬��
	CComboBox         m_cbLineWidth;  //�ߵĿ��
	CColorPanel m_clrPanel;
	CToolBar m_wndColorBar;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	void DispTool(LPCTSTR szToolName);
	int GetPenWidth();
	CColorPanel *GetColorPanel(){ return &m_clrPanel; }
	
	
};


