
// PaintDoc.h : CPaintDoc ��Ľӿ�
//


#pragma once
#include "DrawPiece.h"
#include "DrawWord.h"
#include <vector>
class CPaintDoc : public CDocument
{
protected: // �������л�����
	CPaintDoc();
	DECLARE_DYNCREATE(CPaintDoc)

// ����
public:
	std::vector<CDrawPiece*>m_Draws;
	std::vector<CDrawWord*>m_words;
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int AddDrawPiece(CPoint * m_ptStart, CPoint* m_ptEnd, int m_nToolID);
	int GetDrawCount();
	CDrawPiece* GetDrawPiece(int n);
	void FreeDraws();
	afx_msg void OnEditUndo();
	int AddDrawWord(CString str, CPoint m_point);
	CDrawWord* GetDrawWord(int n);
	int GetWordsCount();
	void FreeWords();
};
