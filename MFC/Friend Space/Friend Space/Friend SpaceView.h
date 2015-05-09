
// Friend SpaceView.h : interface of the CFriendSpaceView class
//

#pragma once
#include "afxwin.h"


class CFriendSpaceSet;

class CFriendSpaceView : public CRecordView
{
protected: // create from serialization only
	CFriendSpaceView();
	DECLARE_DYNCREATE(CFriendSpaceView)

public:
	enum{ IDD = IDD_FRIENDSPACE_FORM };
	CFriendSpaceSet* m_pSet;

// Attributes
public:
	CFriendSpaceDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFriendSpaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Nick_name;
	CString m_Mobile;
	CString m_Category;
	CString m_Date_Of_Birth;
	CString m_Email;
	CString m_Address;
	CString m_Description;
	long m_FriendID;
	bool m_LoginCheck;
	bool m_FirstTimer;
	CButton m_BN_GoToStart;
	CButton m_BN_New;
	CButton m_BN_Add;
	CButton m_BN_Save;
	CButton m_BN_Delete;
	CButton m_BN_Previous;
	CButton m_BN_Next;
	afx_msg void OnGoToStartButtonClicked();
	afx_msg void OnNewButtonClicked();
	afx_msg void OnAddButtonClicked();
	afx_msg void OnSaveButtonClicked();
	afx_msg void OnDeleteButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnNextButtonClicked();
	void UpdateDatabase();
	void UpdateFriendSpace();
	void GotoNext();
	void GotoPrevious();
	void ResetLogin();
	CString m_UserName;
	CString m_Password;
	CButton m_BN_SignIN;
	CButton m_BN_SignUP;
	CButton m_BN_SignOut;
	afx_msg void OnSignInButtonClicked();
	afx_msg void OnSignOutButtonClicked();
	afx_msg void OnSignUpButtonClicked();
	afx_msg void OnDescriptionEdit();
	afx_msg void OnAddressEdit();
	afx_msg void OnEmailEdit();
	afx_msg void OnMobileEdit();
	afx_msg void OnDateofBirthEdit();
	afx_msg void OnCategoryEdit();
	afx_msg void OnNickNameEdit();
	afx_msg void OnNameEdit();
	CListBox m_FriendsList;
	CString m_FriendSelected;
	afx_msg void OnFriendsList();
	afx_msg void OnFriendListEventHandler();
	CButton m_FindFriendsList;
	afx_msg void OnFindFriendsListButtonClicked();
	CButton m_BN_NextFriend;
	CButton m_BN_PreviousFriend;
	afx_msg void OnNextFriendButtonClicked();
	afx_msg void OnPreviousFriendButtonClicked();
};

#ifndef _DEBUG  // debug version in Friend SpaceView.cpp
inline CFriendSpaceDoc* CFriendSpaceView::GetDocument() const
   { return reinterpret_cast<CFriendSpaceDoc*>(m_pDocument); }
#endif

