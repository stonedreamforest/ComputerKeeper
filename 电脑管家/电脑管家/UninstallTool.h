#pragma once
#include "afxcmn.h"
#include "ListCtrl.h"


// UninstallTool �Ի���

class UninstallTool : public CDialogEx
{
	DECLARE_DYNAMIC(UninstallTool)

public:
	UninstallTool(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~UninstallTool();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	bool isInitEnd;
	ListCtrl m_UniListCtrl;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void UninstallIndex();
	CImageList  m_Icon;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void Uninstall();
	afx_msg void SearchInfo();
	afx_msg void OfficialWebsite();
	afx_msg void OpenFilePath();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
