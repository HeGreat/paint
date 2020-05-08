#pragma once

// CDrawPiece 命令目标

class CDrawPiece : public CObject
{
	DECLARE_SERIAL(CDrawPiece)
public:
	CDrawPiece();
	virtual ~CDrawPiece();
	
	CPoint m_ptStart;
	CPoint m_ptEnd;
	int m_nToolID;
	virtual void Serialize(CArchive& ar);
	int m_nPenWidth;  // 画笔的宽度
	COLORREF m_Color;  // 画笔的颜色
};


