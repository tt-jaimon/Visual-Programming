
// Friend SpaceView.cpp : implementation of the CFriendSpaceView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Friend Space.h"
#endif

#include "Friend SpaceSet.h"
#include "Friend SpaceDoc.h"
#include "Friend SpaceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFriendSpaceView

IMPLEMENT_DYNCREATE(CFriendSpaceView, CRecordView)

BEGIN_MESSAGE_MAP(CFriendSpaceView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRecordView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON7, &CFriendSpaceView::OnGoToStartButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON6, &CFriendSpaceView::OnNewButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON5, &CFriendSpaceView::OnAddButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CFriendSpaceView::OnSaveButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CFriendSpaceView::OnDeleteButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CFriendSpaceView::OnPreviousButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON1, &CFriendSpaceView::OnNextButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON8, &CFriendSpaceView::OnSignInButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON10, &CFriendSpaceView::OnSignOutButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON9, &CFriendSpaceView::OnSignUpButtonClicked)
	ON_EN_CHANGE(IDC_EDIT8, &CFriendSpaceView::OnDescriptionEdit)
	ON_EN_CHANGE(IDC_EDIT7, &CFriendSpaceView::OnAddressEdit)
	ON_EN_CHANGE(IDC_EDIT6, &CFriendSpaceView::OnEmailEdit)
	ON_EN_CHANGE(IDC_EDIT3, &CFriendSpaceView::OnMobileEdit)
	ON_EN_CHANGE(IDC_EDIT5, &CFriendSpaceView::OnDateofBirthEdit)
	ON_EN_CHANGE(IDC_EDIT4, &CFriendSpaceView::OnCategoryEdit)
	ON_EN_CHANGE(IDC_EDIT2, &CFriendSpaceView::OnNickNameEdit)
	ON_EN_CHANGE(IDC_EDIT1, &CFriendSpaceView::OnNameEdit)
	ON_LBN_SELCHANGE(IDC_LIST1, &CFriendSpaceView::OnFriendsList)
	ON_LBN_DBLCLK(IDC_LIST1, &CFriendSpaceView::OnFriendListEventHandler)
	ON_BN_CLICKED(IDC_BUTTON11, &CFriendSpaceView::OnFindFriendsListButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON13, &CFriendSpaceView::OnNextFriendButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON12, &CFriendSpaceView::OnPreviousFriendButtonClicked)
END_MESSAGE_MAP()

// CFriendSpaceView construction/destruction

CFriendSpaceView::CFriendSpaceView()
	: CRecordView(CFriendSpaceView::IDD)
	, m_Name(_T(""))
	, m_Nick_name(_T(""))
	, m_Mobile(_T(""))
	, m_Category(_T(""))
	, m_Date_Of_Birth(_T(""))
	, m_Email(_T(""))
	, m_Address(_T(""))
	, m_Description(_T(""))
	, m_FriendID(0)
	, m_UserName(_T(""))
	, m_Password(_T(""))
	, m_FriendSelected(_T(""))
{
	m_LoginCheck = false;
	m_pSet = NULL;
	// TODO: add construction code here

}

CFriendSpaceView::~CFriendSpaceView()
{
}

void CFriendSpaceView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// See MSDN and ODBC samples for more information
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_Nick_name);
	DDX_Text(pDX, IDC_EDIT3, m_Mobile);
	DDX_Text(pDX, IDC_EDIT4, m_Category);
	DDX_Text(pDX, IDC_EDIT5, m_Date_Of_Birth);
	DDX_Text(pDX, IDC_EDIT6, m_Email);
	DDX_Text(pDX, IDC_EDIT7, m_Address);
	DDX_Text(pDX, IDC_EDIT8, m_Description);
	DDX_Text(pDX, IDC_EDIT9, m_FriendID);
	DDX_Control(pDX, IDC_BUTTON7, m_BN_GoToStart);
	DDX_Control(pDX, IDC_BUTTON6, m_BN_New);
	DDX_Control(pDX, IDC_BUTTON5, m_BN_Add);
	DDX_Control(pDX, IDC_BUTTON4, m_BN_Save);
	DDX_Control(pDX, IDC_BUTTON3, m_BN_Delete);
	DDX_Control(pDX, IDC_BUTTON2, m_BN_Previous);
	DDX_Control(pDX, IDC_BUTTON1, m_BN_Next);
	DDX_Text(pDX, IDC_EDIT10, m_UserName);
	DDX_Text(pDX, IDC_EDIT11, m_Password);
	DDX_Control(pDX, IDC_BUTTON8, m_BN_SignIN);
	DDX_Control(pDX, IDC_BUTTON9, m_BN_SignUP);
	DDX_Control(pDX, IDC_BUTTON10, m_BN_SignOut);
	DDX_Control(pDX, IDC_LIST1, m_FriendsList);
	DDX_LBString(pDX, IDC_LIST1, m_FriendSelected);
	DDX_Control(pDX, IDC_BUTTON11, m_FindFriendsList);
	DDX_Control(pDX, IDC_BUTTON13, m_BN_NextFriend);
	DDX_Control(pDX, IDC_BUTTON12, m_BN_PreviousFriend);
}

BOOL CFriendSpaceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CFriendSpaceView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_FriendSpaceSet;
	CRecordView::OnInitialUpdate();

}


// CFriendSpaceView printing

BOOL CFriendSpaceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFriendSpaceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFriendSpaceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CFriendSpaceView diagnostics

#ifdef _DEBUG
void CFriendSpaceView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CFriendSpaceView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CFriendSpaceDoc* CFriendSpaceView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFriendSpaceDoc)));
	return (CFriendSpaceDoc*)m_pDocument;
}
#endif //_DEBUG


// CFriendSpaceView database support
CRecordset* CFriendSpaceView::OnGetRecordset()
{
	return m_pSet;
}

void CFriendSpaceView::GotoNext()
{
	m_pSet->MoveNext();
	while (!m_pSet->IsEOF())
	{
		if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
			break;
		m_pSet->MoveNext();
	}
	if (m_pSet->IsEOF())
	{
		MessageBox(_T("You have Reached the End"), _T("Friend Space"), MB_OK);
		while (!m_pSet->IsBOF())
		{
			if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
				break;
			m_pSet->MovePrev();
		}
		if (m_pSet->IsBOF())
		{
			MessageBox(_T("Sorry Currently you have zero friends in FriendSpace So you have been Signed Off"), _T("Friend Space"), MB_OK);
			this->ResetLogin();
		}
	}
}

void CFriendSpaceView::GotoPrevious()
{
	m_pSet->MovePrev();
	while (!m_pSet->IsBOF())
	{
		if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
			break;
		m_pSet->MovePrev();
	}
	if (m_pSet->IsBOF())
	{
		MessageBox(_T("You have Reached the Begining"), _T("Friend Space"), MB_OK);
		while (!m_pSet->IsEOF())
		{
			if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
				break;
			m_pSet->MoveNext();
		}
		if (m_pSet->IsEOF())
		{
			MessageBox(_T("Sorry Currently you have zero friends in FriendSpace So you have been Signed Off"), _T("Friend Space"), MB_OK);
			this->ResetLogin();
		}
	}
}

void CFriendSpaceView::ResetLogin()
{
	this->OnNewButtonClicked();
	while (m_FriendsList.GetCount())
		m_FriendsList.DeleteString(0);
	m_LoginCheck = false;
	m_FirstTimer = true;
	m_UserName = "";
	m_Password = "";
	UpdateData(false);
}

void CFriendSpaceView::UpdateDatabase()
{
	m_pSet->m_friend_name = m_Name;
	m_pSet->m_friend_nick_name = m_Nick_name;
	m_pSet->m_date_of_birth = m_Date_Of_Birth;
	m_pSet->m_mobile_no = m_Mobile;
	m_pSet->m_email = m_Email;
	m_pSet->m_address = m_Address;
	m_pSet->m_description = m_Description;
	m_pSet->m_friend_category = m_Category;
	m_pSet->m_user_name = m_UserName;
	m_pSet->m_password = m_Password;
}
void CFriendSpaceView::UpdateFriendSpace()
{
	m_Name = m_pSet->m_friend_name;
	m_Nick_name = m_pSet->m_friend_nick_name;
	m_Date_Of_Birth = m_pSet->m_date_of_birth;
	m_Mobile = m_pSet->m_mobile_no;
	m_Email = m_pSet->m_email;
	m_Address = m_pSet->m_address;
	m_Description = m_pSet->m_description;
	m_FriendID = m_pSet->m_friend_id;
	m_Category = m_pSet->m_friend_category;
	m_UserName = m_pSet->m_user_name;
	m_Password = m_pSet->m_password;
}

void CFriendSpaceView::OnNewButtonClicked()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	m_Name = "";
	m_Nick_name = "";
	m_Date_Of_Birth = "";
	m_Mobile = "";
	m_Email = "";
	m_Address = "";
	m_Description = "";
	m_FriendID = 0;
	m_Category = "";
	UpdateData(false);
}

void CFriendSpaceView::OnSaveButtonClicked()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	UpdateData(true);
	m_pSet->Edit();
	this->UpdateDatabase();
	m_pSet->Update();
	MessageBox(_T("Entry is been succesfully saved"), _T("Friend Space"), MB_OK);
	this->UpdateFriendSpace();
	UpdateData(false);
}


void CFriendSpaceView::OnAddButtonClicked()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	UpdateData(true);
	m_pSet->MoveLast();
	m_pSet->AddNew();
	this->UpdateDatabase();
	m_pSet->Update();
	MessageBox(_T("New Entry is been succesfully added"), _T("Friend Space"), MB_OK);
	m_FirstTimer = false;
	this->GotoNext();
	this->UpdateFriendSpace();
	UpdateData(false);
}


void CFriendSpaceView::OnGoToStartButtonClicked()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	m_pSet->MoveFirst();
	m_pSet->MovePrev();
	this->GotoNext();
	this->UpdateFriendSpace();
	UpdateData(false);
}


void CFriendSpaceView::OnPreviousButtonClicked()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	this->GotoPrevious();
	this->UpdateFriendSpace();
	UpdateData(false);
}

void CFriendSpaceView::OnNextButtonClicked()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	this->GotoNext();
	this->UpdateFriendSpace();
	UpdateData(false);
}

void CFriendSpaceView::OnDeleteButtonClicked()
{
	if (m_FirstTimer||!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	m_pSet->Delete();
	MessageBox(_T("Entry is been succesfully deleted"), _T("Friend Space"), MB_OK);
	this->GotoPrevious();
	if (m_LoginCheck)
		this->UpdateFriendSpace();
	UpdateData(false);
}

void CFriendSpaceView::OnSignInButtonClicked()
{
	UpdateData(true);
	m_pSet->MoveFirst();
	while (!m_pSet->IsEOF())
	{
		if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
			break;
		m_pSet->MoveNext();
	}
	if (m_pSet->IsEOF())
	{
		MessageBox(_T("Invalid Username/Password"), _T("Friend Space"), MB_OK);
		this->ResetLogin();
	}
	else
	{
		MessageBox(_T("Login Successfull"), _T("Friend Space"), MB_OK);
		m_LoginCheck = true;
		m_FirstTimer = false;
		this->OnGoToStartButtonClicked();
	}
}


void CFriendSpaceView::OnSignOutButtonClicked()
{
	MessageBox(_T("Succesfully Signed Off"), _T("Friend Space"), MB_OK);
	this->ResetLogin();
}

void CFriendSpaceView::OnSignUpButtonClicked()
{
	UpdateData(true);
	if (m_UserName == "" || m_Password == "")
	{
		MessageBox(_T("Please Enter Valid Username and password"), _T("Friend Space"), MB_OK);
		return;
	}
	m_LoginCheck = true;
	m_FirstTimer = true;
	MessageBox(_T("Sucessfully Signed Up"), _T("Friend Space"), MB_OK);
}


void CFriendSpaceView::OnDescriptionEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Description = "";
		UpdateData(false);
		return;
	}	
}


void CFriendSpaceView::OnAddressEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Address = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnEmailEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Email = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnMobileEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Mobile = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnDateofBirthEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Date_Of_Birth = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnCategoryEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Category = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnNickNameEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Nick_name = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnNameEdit()
{
	if (!m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		m_Name = "";
		UpdateData(false);
		return;
	}
}


void CFriendSpaceView::OnFriendsList()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	
}


void CFriendSpaceView::OnFriendListEventHandler()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}

	m_pSet->MoveFirst();
	UpdateData(true);
	while (!m_pSet->IsEOF())
	{
		if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password&&m_pSet->m_friend_name == m_FriendSelected)
		{
			this->UpdateFriendSpace();
			UpdateData(false);
			break;
		}
		m_pSet->MoveNext();
	}
}


void CFriendSpaceView::OnFindFriendsListButtonClicked()
{
	if (m_FirstTimer || !m_LoginCheck)
	{
		MessageBox(_T("Access Denied"), _T("Friend Space"), MB_OK);
		return;
	}
	while (m_FriendsList.GetCount())
		m_FriendsList.DeleteString(0);
	m_pSet->MoveFirst();
	while (!m_pSet->IsEOF())
	{
		if (m_pSet->m_user_name == m_UserName&&m_pSet->m_password == m_Password)
		{
			if (m_FriendsList.FindString(0, m_pSet->m_friend_name) == -1)
				m_FriendsList.AddString(m_pSet->m_friend_name);
		}
		m_pSet->MoveNext();
	}
}


void CFriendSpaceView::OnNextFriendButtonClicked()
{
	this->GotoNext();
	if (m_pSet->m_friend_name == m_FriendSelected)
	{
		this->UpdateFriendSpace();
		UpdateData(false);
	}
}


void CFriendSpaceView::OnPreviousFriendButtonClicked()
{
	this->GotoPrevious();
	if (m_pSet->m_friend_name == m_FriendSelected)
	{
		this->UpdateFriendSpace();
		UpdateData(false);
	}
}
