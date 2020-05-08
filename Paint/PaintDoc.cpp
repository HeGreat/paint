
// PaintDoc.cpp : CPaintDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "PaintDoc.h"
#include "MainFrm.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPaintDoc

IMPLEMENT_DYNCREATE(CPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintDoc, CDocument)
	ON_COMMAND(ID_EDIT_UNDO, &CPaintDoc::OnEditUndo)
END_MESSAGE_MAP()


// CPaintDoc 构造/析构

CPaintDoc::CPaintDoc()
{
	// TODO:  在此添加一次性构造代码

}

CPaintDoc::~CPaintDoc()
{
	FreeDraws();
	FreeWords();
}

BOOL CPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}




// CPaintDoc 序列化

void CPaintDoc::Serialize(CArchive& ar)
{
	int n;
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
		ar << m_Draws.size();
		for (int i = 0; i < m_Draws.size(); i++)
		{
			ar.WriteObject(m_Draws[i]);
		}
	}
	else
	{
		// TODO:  在此添加加载代码
		ar >> n;
		for (int i = 0; i < n; i++)
		{
			m_Draws.push_back((CDrawPiece*)ar.ReadObject(RUNTIME_CLASS(CDrawPiece)));
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CPaintDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CPaintDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CPaintDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintDoc 诊断

#ifdef _DEBUG
void CPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintDoc 命令


int CPaintDoc::AddDrawPiece(CPoint * m_ptStart, CPoint* m_ptEnd, int m_nToolID)
{
	CDrawPiece *dp = new CDrawPiece();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	dp->m_ptStart = *m_ptStart;
	dp->m_ptEnd = *m_ptEnd;
	dp->m_nToolID = m_nToolID;
	dp->m_nPenWidth = pFrame->GetPenWidth();
	dp->m_Color = pFrame->GetColorPanel()->m_clrFront;
	m_Draws.push_back(dp);
	
	return 0;
}


int CPaintDoc::GetDrawCount()
{
	return m_Draws.size();
}


CDrawPiece* CPaintDoc::GetDrawPiece(int n)
{
	return ((n>=m_Draws.size())?NULL:m_Draws[n]);
}


void CPaintDoc::FreeDraws()
{
	for (int i = 0; i < m_Draws.size(); i++)
	{
		delete m_Draws[i];
	}
	m_Draws.clear();
}


void CPaintDoc::OnEditUndo()
{
	CDrawPiece* dp;
	if (m_Draws.size()>0)
	{
		dp = m_Draws[m_Draws.size() - 1];
		this->m_Draws.pop_back();
		delete dp;
		this->UpdateAllViews(false);
	}
}


int CPaintDoc::AddDrawWord(CString str, CPoint m_point)
{
	CDrawWord *dp = new CDrawWord();
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	dp->m_point = m_point;
	dp->m_szString = str;
	m_words.push_back(dp);
	return 0;
}


CDrawWord* CPaintDoc::GetDrawWord(int n)
{
	return ((n >= m_words.size()) ? NULL : m_words[n]);
}


int CPaintDoc::GetWordsCount()
{
	return m_words.size();
}


void CPaintDoc::FreeWords()
{
	for (int i = 0; i < m_words.size(); i++)
	{
		delete m_words[i];
	}
	m_words.clear();
}
