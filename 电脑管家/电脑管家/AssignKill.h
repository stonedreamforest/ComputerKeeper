#pragma once
#include "afxwin.h"


// AssignKill 对话框

class AssignKill : public CDialogEx
{
	DECLARE_DYNAMIC(AssignKill)

public:
	AssignKill(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AssignKill();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
//	CString m_str;		//拖拽文件名显示
	afx_msg void OnEnChangeEdit1();
	//CString m_FilePathName;
	CString m_FilePathName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	bool m_IsKill;
//	virtual BOOL OnInitDialog();
};
