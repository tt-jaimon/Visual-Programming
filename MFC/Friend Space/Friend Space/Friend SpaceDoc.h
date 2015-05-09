
// Friend SpaceDoc.h : interface of the CFriendSpaceDoc class
//


#pragma once
#include "Friend SpaceSet.h"


class CFriendSpaceDoc : public CDocument
{
protected: // create from serialization only
	CFriendSpaceDoc();
	DECLARE_DYNCREATE(CFriendSpaceDoc)

// Attributes
public:
	CFriendSpaceSet m_FriendSpaceSet;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFriendSpaceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
