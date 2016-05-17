#pragma once
#include "afxwin.h"
#include "ImageButton.h"
#include "afxcmn.h"
#include "ListCtrl.h"
#include "MyListCtrl.h"

// StartupManager 对话框
#define  WM_BN_CLICK  WM_USER + 100
#define  USE_TOPINDEX_BUTTON

class StartupManager : public CDialogEx
{
	DECLARE_DYNAMIC(StartupManager)

public:
	StartupManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StartupManager();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	ImageButton m_StartupButton;
	ImageButton m_BackButton;
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	HBRUSH   m_hbrush;  
//	CListBox m_StartupListBox;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL isInitEnd;

	void initListBox();
	CMyListCtrl m_StartupListCtrl;
//	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);

public:
	afx_msg LRESULT onBnCLick( WPARAM wParam, LPARAM lParam );	//LIST 控件的按钮

	BOOL DeleteRun( int  nIndex );
	BOOL AddRun( CString cRunName,CString cRunPath );
	void MovebkPic(int BkgroundPic);
	int m_BackgroundPic;
	bool m_ButtonState;
	afx_msg void OnBnClickedButton2();

};
