
// PaintView.h : CPaintView 类的接口
//

#pragma once
#include "atltypes.h"
#include "atlimage.h"


class CPaintView : public CView
{
protected: // 仅从序列化创建
	CPaintView();
	DECLARE_DYNCREATE(CPaintView)

// 特性
public:
	CPaintDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	// 鼠标按下的起始位置
	CPoint m_ptStart;
	// 鼠标谈起的结束位置
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

#ifndef _DEBUG  // PaintView.cpp 中的调试版本
inline CPaintDoc* CPaintView::GetDocument() const
   { return reinterpret_cast<CPaintDoc*>(m_pDocument); }
#endif

