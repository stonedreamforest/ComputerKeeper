#pragma once
#include "afxcmn.h"
#include "ListButton.h"
#include <map>
using namespace std;

typedef map<int,ListButton*>button_map;



class CMyListCtrl :	public CListCtrl
{
public:
	CMyListCtrl(void);
	~CMyListCtrl(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
public:
	int m_nItemHeight;
	void SetItemHeight(UINT nHeight);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
//	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);

	int m_currRowID;
public:
	void createItemButton( int nItem, int nSubItem, HWND hMain );

	button_map m_mButton;
	UINT m_uID;

	void updateListCtrlButtonPos();
	void enableButton( BOOL bFlag, int iItem );

	afx_msg void OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult);
};

