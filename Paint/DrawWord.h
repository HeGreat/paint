#pragma once
#include "afx.h"
#include "atltypes.h"
class CDrawWord :
	public CObject
{
public:
	CDrawWord();
	~CDrawWord();
	CString m_szString;

	virtual void Serialize(CArchive& ar);
	CPoint m_point;
};
