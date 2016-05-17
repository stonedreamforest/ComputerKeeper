#pragma once
#include "afxwin.h"
#include "ImageButton.h"
#include "MemoryOptimizer.h"
// HomePage 对话框

class HomePage : public CDialogEx
{
	DECLARE_DYNAMIC(HomePage)

public:
	HomePage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HomePage();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	ImageButton m_HomeButton;
	afx_msg void OnBnClickedButton1();
	MemoryOptimizer m_mem;

	void MovebkPicZuo(int BkgroundPic);		//左进
	void MovebkPicXia(	int BkgroundPic);	//下进
	void MovebkPicYou(	int BkgroundPic);	//右进
	void MovebkPicZuoxia(	int BkgroundPic);//上进
	int m_BackgroundPic;
	bool m_ButtonState;
};
