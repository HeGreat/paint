#include "stdafx.h"
#include "DrawWord.h"


CDrawWord::CDrawWord() : m_szString(_T(""))
, m_point(0)
{
}


CDrawWord::~CDrawWord()
{

}


void CDrawWord::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_szString;
		ar << m_point;
	}
	else
	{	// loading code
		ar >> m_szString;
		ar >> m_point;
	}
}