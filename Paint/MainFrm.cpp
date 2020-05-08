
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//����������1:ͼ�ΰ�ť
	//........................
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	//����������2����ɫѡ��
	//........................
	if (!m_wndColorBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndColorBar.LoadToolBar(IDR_TOOLBAR_COLOR))
	{
		AfxMessageBox(_T("������ɫ������ʧ��"));
		return -1;
	}


	//������϶Ի���
	//........................
	CRect rect;
	int nIndex = m_wndToolBar.GetToolBarCtrl().CommandToIndex(IDB_LINEWIDTH);
	m_wndToolBar.SetButtonInfo(nIndex, IDB_LINEWIDTH, TBBS_SEPARATOR, 205);
	m_wndToolBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
	rect.top += 1;
	rect.bottom = rect.top + 80;
	m_cbLineWidth.Create(CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP
		| WS_VSCROLL, rect, this, IDB_LINEWIDTH);
	//...................����϶Ի����������........................//
	TCHAR szLine[20];
	for (int i = 1; i <= 10; i++)
	{
		swprintf_s(szLine, _T("�߿�%d"), i);
		m_cbLineWidth.AddString(szLine);
	}
	m_cbLineWidth.SetCurSel(1);

	//����״̬��
	//........................
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	//.............����״̬��..............//
	//m_wndStatusBar.SetPaneInfo(1, 0, SBPS_POPOUT, 120);   //�������½�
	//m_wndStatusBar.SetPaneInfo(2, 0, SBPS_POPOUT, 60);    //������С�ǵ�2��

	//�����ɫ���
	nIndex = m_wndColorBar.GetToolBarCtrl().CommandToIndex(ID_COLORPANEL);
	m_wndColorBar.SetButtonInfo(nIndex, ID_COLORPANEL, TBBS_SEPARATOR, 300);
	m_wndColorBar.GetToolBarCtrl().GetItemRect(nIndex, &rect);
	this->m_clrPanel.Create(NULL, _T("��ɫ"), WS_VISIBLE | WS_CHILD | WS_TABSTOP, rect, &m_wndColorBar, ID_COLORPANEL);

	// TODO:  �������Ҫ��ͣ������������ɾ��������
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
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



void CMainFrame::DispTool(LPCTSTR szToolName)
{
	this->m_wndStatusBar.SetPaneText(1, szToolName);
}


int CMainFrame::GetPenWidth()
{
	return m_cbLineWidth.GetCurSel()+1;
}
