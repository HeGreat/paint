// DrawPiece.cpp : 实现文件
//

#include "stdafx.h"
#include "Paint.h"
#include "DrawPiece.h"


// CDrawPiece
IMPLEMENT_SERIAL(CDrawPiece, CObject, 1);


CDrawPiece::CDrawPiece(): m_nPenWidth(0)
{
}

CDrawPiece::~CDrawPiece()
{
}


// CDrawPiece 成员函数


void CDrawPiece::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		ar << m_ptStart;
		ar << m_ptEnd;
		ar << m_nToolID;
	}
	else
	{	
		ar >> m_ptStart;
		ar >> m_ptEnd;
		ar >> m_nToolID;
	}
}
