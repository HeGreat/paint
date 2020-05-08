#pragma once


// CColorPanel

class CColorPanel : public CWnd
{
	DECLARE_DYNAMIC(CColorPanel)

public:
	CColorPanel();
	virtual ~CColorPanel();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	int m_wIndicator;
	COLORREF m_clrFront;
	COLORREF m_clrBack;
	CBrush	m_brBack;
	CBrush  m_brFront;
};


