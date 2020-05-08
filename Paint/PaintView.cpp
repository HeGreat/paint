
// PaintView.cpp : CPaintView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Paint.h"
#endif

#include "DrawWord.h"
#include "DrawPiece.h"
#include "PaintDoc.h"
#include "PaintView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CView)

BEGIN_MESSAGE_MAP(CPaintView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND_RANGE(IDM_RECT, IDM_LINE,&CPaintView::OnTools)
	ON_UPDATE_COMMAND_UI_RANGE(IDM_RECT, IDM_LINE, OnUpdateTools)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OPEN_PICTURE, &CPaintView::OnOpenPicture)
	ON_COMMAND(IDM_TEXT, &CPaintView::OnText)
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPaintView ����/����

CPaintView::CPaintView()
	: m_ptStart(0)
	, m_ptEnd(0)
	, m_nCurTools(0)
	, m_ptOldEnd(0)
	, m_bInputText(FALSE)
	, m_ptOrigin(0)
	, m_strLine(_T(""))
{
	// TODO:  �ڴ˴���ӹ������

}

CPaintView::~CPaintView()
{
}

BOOL CPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPaintView ����
void CPaintView::DrawPiece(CDC* pDC, CDrawPiece* dp)
{
	HBRUSH hOldBrush;

	HPEN hOldPen, hNewPen;
	hNewPen = ::CreatePen(PS_SOLID, dp->m_nPenWidth, dp->m_Color);
	if (hNewPen == NULL)
	{
		AfxMessageBox(_T("��������ʧ��\n"));
		return;
	}
	hOldPen = (HPEN)SelectObject(pDC->m_hDC, hNewPen);
	hOldBrush = (HBRUSH)::SelectObject(pDC->m_hDC, GetStockObject(NULL_BRUSH));

	switch (dp->m_nToolID)
	{
	case IDM_RECT:
		pDC->Rectangle(dp->m_ptStart.x, dp->m_ptStart.y, dp->m_ptEnd.x, dp->m_ptEnd.y);
		break;
	case IDM_CIRCLE:
		pDC->Ellipse(dp->m_ptStart.x, dp->m_ptStart.y, dp->m_ptEnd.x, dp->m_ptEnd.y);
		break;
	case IDM_LINE:
		pDC->MoveTo(dp->m_ptStart.x, dp->m_ptStart.y);
		pDC->LineTo(dp->m_ptEnd.x, dp->m_ptEnd.y);
		break;
	}
	SelectObject(pDC->m_hDC, hOldPen);
	::SelectObject(pDC->m_hDC, hOldBrush);
	::DeleteObject(hNewPen);
}


void CPaintView::OnDraw(CDC* pDC)
{
	CPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CDrawPiece *dp;
	for (int i = 0; i < pDoc->GetDrawCount(); i++)
	{
		dp = pDoc->GetDrawPiece(i);
		DrawPiece(pDC, dp);
	}


	//����
	CDrawWord *tp;
	for (int i = 0; i < pDoc->GetWordsCount(); i++)
	{
		tp = pDoc->GetDrawWord(i);
		DrawWord(tp);
	}

	//�����
	CClientDC dc(this);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);
	SetCaretPos(m_ptOrigin);
	if (m_bInputText)
	{
		ShowCaret();
	}
	else
	{
		DestroyCaret();
	}
	//ͼ��
	if (!image.IsNull())
	{
		image.Draw(pDC->GetSafeHdc(), 0, 0);
	}
	dc.MoveTo(20, 20);
	dc.LineTo(60, 60);
}


// CPaintView ��ӡ

BOOL CPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CPaintView ���

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaintDoc* CPaintView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaintDoc)));
	return (CPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaintView ��Ϣ�������
const TCHAR* Tools_Name[] = { _T("����"), _T("Բ"), _T("ֱ��") };

void CPaintView::OnTools(UINT id)
{
	m_nCurTools = id;
	DestroyCaret();   //���ٲ����

	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	int Index = id - IDM_RECT;
	if (Index<0 || Index>(sizeof(Tools_Name) / sizeof(Tools_Name[0])))
		return;
	pFrame->DispTool(Tools_Name[Index]);
}


void CPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptStart = point;     //���Ƽ���ͼ��ʹ��
	m_ptOrigin = point;	   //��������ʹ��
	CView::OnLButtonDown(nFlags, point);
}


void CPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptEnd = point;
	CPaintDoc *pDoc = GetDocument();
	pDoc->AddDrawPiece(&m_ptStart, &m_ptEnd, m_nCurTools);

	m_ptOldEnd.x = -1;
	m_ptOldEnd.y = -1;


	CView::OnLButtonUp(nFlags, point);
	Invalidate();
}




void CPaintView::OnUpdateTools(CCmdUI * pCmdUI)
{
	// TODO:  �ڴ����ר�ô����/����û���
	pCmdUI->SetCheck(this->m_nCurTools == pCmdUI->m_nID);

}


void CPaintView::OnOpenPicture()
{
	// TODO:  �ڴ���������������
	CFileDialog dlg(TRUE, _T(".bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("λͼ�ļ�(*.bmp)|*.bmp|JPEGͼ���ļ�|*.jpg|GIFͼ���ļ�|*.gif|PNGͼ��|*.png|������ʽ(*.*)|* .* |"));
	if (dlg.DoModal() == IDOK)
	{
		if (!image.IsNull())
		{
			image.Destroy();
		}
		image.Load(dlg.GetPathName());
		Invalidate();
	}
}


void CPaintView::OnText()
{
	// TODO:  �ڴ���������������
	m_bInputText = TRUE;
	m_nCurTools = -1;
}


void CPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDrawPiece dp;
	CMainFrame * pFrame = (CMainFrame *)AfxGetMainWnd();
	if (nFlags & MK_LBUTTON)
	{
		CDC *pDC = GetDC();

		int nOldRop = pDC->GetROP2();  //set the erase mode
		dp.m_nPenWidth = pFrame->GetPenWidth();
		dp.m_ptStart = this->m_ptStart;
		dp.m_ptEnd = point;
		dp.m_nToolID = m_nCurTools;
		dp.m_Color = pFrame->GetColorPanel()->m_clrFront;
		if (m_ptOldEnd.x >= 0)   //need erase old drawing
		{
			pDC->SetROP2(R2_NOT);
			dp.m_ptEnd = m_ptOldEnd;
			DrawPiece(pDC, &dp);

		}
		dp.m_ptEnd = point;
		DrawPiece(pDC, &dp);
		this->m_ptOldEnd = point;    //prepare for next erase

	}
	CView::OnMouseMove(nFlags, point);
}


void CPaintView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_bInputText)
	{
		CClientDC dc(this);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);


		if (0x0d == nChar)
		{
			m_strLine.Empty();
			m_ptOrigin.y += tm.tmHeight;
		}
		else if (0x08 == nChar)
		{
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
			m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
			dc.SetTextColor(clr);
		}
		else
		{
			m_strLine += (WCHAR)nChar;
		}

		CSize sz = dc.GetTextExtent(m_strLine);
		CPoint pt;
		pt.x = m_ptOrigin.x + sz.cx;
		pt.y = m_ptOrigin.y;
		SetCaretPos(pt);
		dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);

		CPaintDoc *pDoc = GetDocument();
		pDoc->AddDrawWord(m_strLine, m_ptOrigin);

	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CPaintView::DrawWord(CDrawWord* tp)
{
	OnCare();

	CClientDC dc(this);
	dc.TextOut(tp->m_point.x, tp->m_point.y, tp->m_szString);
}


void CPaintView::OnCare()
{
	m_strLine.Empty();
}

