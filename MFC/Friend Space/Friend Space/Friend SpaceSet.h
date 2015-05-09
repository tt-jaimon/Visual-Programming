
// Friend SpaceSet.h: interface of the CFriendSpaceSet class
//


#pragma once

// code generated on Thursday, May 7, 2015, 10:29 PM

class CFriendSpaceSet : public CRecordset
{
public:
	CFriendSpaceSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFriendSpaceSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	CStringW	m_user_name;
	CStringW	m_password;
	long	m_friend_id;
	CStringW	m_friend_name;
	CStringW	m_friend_category;
	CStringW	m_friend_nick_name;
	CStringW	m_date_of_birth;
	CStringW	m_address;
	CStringW	m_mobile_no;
	CStringW	m_email;
	CStringW	m_description;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

