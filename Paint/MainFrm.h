
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "afxext.h"
#include "ColorPanel.h"
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;   //工具条
	CStatusBar        m_wndStatusBar; //状态条
	CComboBox         m_cbLineWidth;  //线的宽度
	CColorPanel m_clrPanel;
	CToolBar m_wndColorBar;
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	void DispTool(LPCTSTR szToolName);
	int GetPenWidth();
	CColorPanel *GetColorPanel(){ return &m_clrPanel; }
	
	
};


