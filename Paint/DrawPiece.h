#pragma once

// CDrawPiece ����Ŀ��

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
	int m_nPenWidth;  // ���ʵĿ��
	COLORREF m_Color;  // ���ʵ���ɫ
};


