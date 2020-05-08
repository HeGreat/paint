
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Paint.h"
#include "resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//创建工具栏1:图形按钮
	//........................
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	//创建工具栏2：颜色选项
	//........................
	if (!m_wndColorBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndColorBar.LoadToolBar(IDR_TOOLBAR_COLOR))
	{
		AfxMessageBox(_T("创建颜色工具条失败"));
		return -1;
	}


	//创建组合对话框
	//........................
	CRect rect;
	int nIndex = m_wndToolBar.GetToolBarCtrl().CommandToIndex(IDB_LINEWIDTH);
	m_wndToolBar.SetButtonInfo(nIndex, IDB_LINEWIDTH, TBBS_SEPARATOR, 205);
	m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
	rect.top += 1;
	rect.bottom = rect.top + 80;
	m_cbLineWidth.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP
		| WS_VSCROLL, rect, this, IDB_LINEWIDTH);
	//...................对组合对话框加入内容........................//
	TCHAR szLine[20];
	for (int i = 1; i <= 10; i++)
	{
		swprintf_s(szLine, _T("线宽：%d"), i);
		m_cbLineWidth.AddString(szLine);
	}
	m_cbLineWidth.SetCurSel(1);

	//创建状态条
	//........................
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//.............设置状态条..............//
	//m_wndStatusBar.SetPaneInfo(1, 0, SBPS_POPOUT, 120);   //定义右下角
	//m_wndStatusBar.SetPaneInfo(2, 0, SBPS_POPOUT, 60);    //定义右小角第2个

	//添加颜色面板
	nIndex = m_wndColorBar.GetToolBarCtrl().CommandToIndex(ID_COLORPANEL);
	m_wndColorBar.SetButtonInfo(nIndex, ID_COLORPANEL, TBBS_SEPARATOR, 300);
	m_wndColorBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
	this->m_clrPanel.Create(NULL, _T("颜色"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, rect, &m_wndColorBar, ID_COLORPANEL);

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndColorBar.EnableDocking(CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndColorBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::DispTool(LPCTSTR szToolName)
{
	this->m_wndStatusBar.SetPaneText(1, szToolName);
}


int CMainFrame::GetPenWidth()
{
	return m_cbLineWidth.GetCurSel()+1;
}
