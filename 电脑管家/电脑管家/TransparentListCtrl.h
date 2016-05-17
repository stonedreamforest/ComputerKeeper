#pragma once


// TransparentListCtrl

class TransparentListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(TransparentListCtrl)

public:
	TransparentListCtrl();
	virtual ~TransparentListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};


