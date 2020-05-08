
// PaintView.h : CPaintView ��Ľӿ�
//

#pragma once
#include "atltypes.h"
#include "atlimage.h"


class CPaintView : public CView
{
protected: // �������л�����
	CPaintView();
	DECLARE_DYNCREATE(CPaintView)

// ����
public:
	CPaintDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	// ��갴�µ���ʼλ��
	CPoint m_ptStart;
	// ���̸��Ľ���λ��
	CPoint m_ptEnd;
public:
	afx_msg void OnTools(UINT id);
protected:
	int m_nCurTools;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawPiece(CDC* pDC, CDrawPiece* dp);
	virtual void OnUpdateTools(CCmdUI * pCmdUI);
	afx_msg void OnOpenPicture();
protected:
	CImage image;
public:
	afx_msg void OnText();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CPoint m_ptOldEnd;
	BOOL m_bInputText;
	CPoint m_ptOrigin;
	CString m_strLine;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawWord(CDrawWord* tp);
	void OnCare();
//	afx_msg void OnPaint();
};

#ifndef _DEBUG  // PaintView.cpp �еĵ��԰汾
inline CPaintDoc* CPaintView::GetDocument() const
   { return reinterpret_cast<CPaintDoc*>(m_pDocument); }
#endif

