#pragma once
#include "afxwin.h"
#include "ImageButton.h"

// VirusScanner 对话框

class VirusScanner : public CDialogEx
{
	DECLARE_DYNAMIC(VirusScanner)

public:
	VirusScanner(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VirusScanner();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	BOOL IsShow;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	CButton m_StartupVirus1;
//	CButton m_StartupButton2;
	ImageButton m_StartupVirus1;
	ImageButton m_StartupVirus2;
	virtual BOOL OnInitDialog();
	ImageButton m_AllKill;
	ImageButton m_AssignButton;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//以下为杀毒相关操作
public:
	void TraverseFolder(LPCTSTR szName,LPCTSTR filetype);//读取文件

	static DWORD WINAPI LightningProc(LPVOID lpThreadParameter);
	static DWORD WINAPI AllProc(LPVOID lpThreadParameter);

	static VirusScanner * m_this;
public:
	void MovebkPic(int BkgroundPic);
	int m_BackgroundPic;
	bool m_ButtonState;
	bool isInThead;
};
