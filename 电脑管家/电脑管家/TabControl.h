#pragma once


// TabControl

class TabControl : public CTabCtrl
{
	DECLARE_DYNAMIC(TabControl)

public:
	TabControl();
	virtual ~TabControl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CDialogEx *m_processDlg[10];
	void addDlg(DWORD count,...);
	void setshow(int sel);
	DWORD m_dlgCount;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnDropFiles(HDROP hDropInfo);
};


