#pragma once


// ListCtrl

class ListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(ListCtrl)

public:
	ListCtrl();
	virtual ~ListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


