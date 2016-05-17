
// 电脑管家Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TabControl.h"
#include "afxwin.h"
#include "ImageButton.h"
// C电脑管家Dlg 对话框
class C电脑管家Dlg : public CDialogEx
{
// 构造
public:
	C电脑管家Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CTabCtrl m_Tab;
//	TabControl m_TabControl;
	TabControl m_Tab;
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	bool IsShowIma;
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	bool m_IsWindowHide;
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	ImageButton m_CloseButton;	//关闭窗口
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	ImageButton m_ShoWinButton;	//最小化

	afx_msg void OnBnClickedButton2();
	ImageButton m_MenuButton;
	afx_msg void OnBnClickedButton3();
	ImageButton m_CloudButton;
	afx_msg void OnBnClickedButton4();
	ImageButton m_MailButton;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);


	void InintWinSock();
	void  InitTCP();
	static DWORD WINAPI ThreadProc(LPVOID prama);
	static C电脑管家Dlg * m_this;
};
