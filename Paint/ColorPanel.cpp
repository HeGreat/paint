// ColorPanel.cpp : 实现文件
//

#include "stdafx.h"
#include "Paint.h"
#include "ColorPanel.h"


// CColorPanel

IMPLEMENT_DYNAMIC(CColorPanel, CWnd)

CColorPanel::CColorPanel()
{

}

CColorPanel::~CColorPanel()
{
}


BEGIN_MESSAGE_MAP(CColorPanel, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CColorPanel 消息处理程序


#define GAP 3
#define CP_MAX_COLS 16

COLORREF GetRGB(int row, int col)
{
	return RGB(row * 100 + col * 200, col * 10, col * 10);
}

void CColorPanel::OnPaint()
{
	// 不为绘图消息调用 CWnd::OnPaint()
	CPaintDC dc(this); // device context for painting
	CRect rect, rcCell, rcField;
	int wCell, wClient;
	COLORREF color;

	this->GetClientRect(&rect);
	wClient = rect.Width();
	m_wIndicator = rect.Height() - 2 * GAP;

	dc.DrawFrameControl(CRect(GAP, GAP, GAP + m_wIndicator, GAP + m_wIndicator), DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);

	int xThird = (m_wIndicator - 2 * GAP) / 3;
	dc.FillRect(CRect(GAP + GAP + xThird, GAP + xThird, m_wIndicator - GAP, m_wIndicator - GAP * 2), &m_brBack);
	dc.FillRect(CRect(GAP + GAP, GAP + 3, GAP + GAP + xThird * 2, GAP + xThird * 2), &m_brFront);

	wCell = (m_wIndicator - GAP) / 2;
	CBrush brush;
	for (int r = 0; r < 2; r++)
	{
		rcCell.left = GAP + m_wIndicator + GAP;
		rcCell.top = GAP + (wCell + GAP)*r;
		rcCell.right = rcCell.left + wCell;
		rcCell.bottom = rcCell.top + wCell;
		for (int i = 0; i < CP_MAX_COLS; i++)
		{
			dc.DrawFrameControl(rcCell, DFC_BUTTON, DFCS_BUTTONPUSH | DFCS_PUSHED);
			rcField = rcCell;

			rcCell.left += wCell + GAP;
			rcCell.right = rcCell.left + wCell;

			rcField.DeflateRect(3, 3);
			color = GetRGB(r, i);  
			brush.CreateSolidBrush(color);

			dc.FillRect(&rcField, &brush);
			brush.DeleteObject();
		}
	}

}


void CColorPanel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int row = (point.y > m_wIndicator / 2) ? 1 : 0;
	int col = (point.x - m_wIndicator) / (m_wIndicator / 2);
	this->m_clrFront = GetRGB(row, col);

	m_brBack.DeleteObject();
	m_brBack.CreateSolidBrush(m_clrBack);

	this->Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CColorPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int row = (point.y > m_wIndicator / 2) ? 1 : 0;
	int col = (point.x - m_wIndicator) / (m_wIndicator / 2);

	this->m_clrFront = GetRGB(row, col);

	m_brFront.DeleteObject();
	m_brFront.CreateSolidBrush(m_clrFront);
	this->Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}
