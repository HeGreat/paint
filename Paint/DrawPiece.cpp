// DrawPiece.cpp : ʵ���ļ�
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


// CDrawPiece ��Ա����


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
