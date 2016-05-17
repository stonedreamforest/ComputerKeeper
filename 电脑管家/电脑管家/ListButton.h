#pragma once
#include "afxwin.h"
class ListButton :
	public CButton
{
public:
	ListButton(void);
	ListButton( int nItem, int nSubItem, CRect rect, HWND hParent );
	~ListButton(void);
public:
	int m_inItem;
	int m_inSubItem;
	CRect m_rect;
	HWND m_hParent;
	BOOL bEnable;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClicked();
};

