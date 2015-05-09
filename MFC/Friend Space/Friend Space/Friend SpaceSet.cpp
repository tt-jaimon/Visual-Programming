
// Friend SpaceSet.cpp : implementation of the CFriendSpaceSet class
//

#include "stdafx.h"
#include "Friend Space.h"
#include "Friend SpaceSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFriendSpaceSet implementation

// code generated on Thursday, May 7, 2015, 10:29 PM

IMPLEMENT_DYNAMIC(CFriendSpaceSet, CRecordset)

CFriendSpaceSet::CFriendSpaceSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_user_name = L"";
	m_password = L"";
	m_friend_id = 0;
	m_friend_name = L"";
	m_friend_category = L"";
	m_friend_nick_name = L"";
	m_date_of_birth = L"";
	m_address = L"";
	m_mobile_no = L"";
	m_email = L"";
	m_description = L"";
	m_nFields = 11;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CFriendSpaceSet::GetDefaultConnect()
{
	return _T("DSN=Friend Space;DBQ=C:\\Users\\Jaimon\\Documents\\Friend Space.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CFriendSpaceSet::GetDefaultSQL()
{
	return _T("[FriendSpace]");
}

void CFriendSpaceSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[user_name]"), m_user_name);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Long(pFX, _T("[friend_id]"), m_friend_id);
	RFX_Text(pFX, _T("[friend_name]"), m_friend_name);
	RFX_Text(pFX, _T("[friend_category]"), m_friend_category);
	RFX_Text(pFX, _T("[friend_nick_name]"), m_friend_nick_name);
	RFX_Text(pFX, _T("[date_of_birth]"), m_date_of_birth);
	RFX_Text(pFX, _T("[address]"), m_address);
	RFX_Text(pFX, _T("[mobile_no]"), m_mobile_no);
	RFX_Text(pFX, _T("[email]"), m_email);
	RFX_Text(pFX, _T("[description]"), m_description);

}
/////////////////////////////////////////////////////////////////////////////
// CFriendSpaceSet diagnostics

#ifdef _DEBUG
void CFriendSpaceSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFriendSpaceSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

