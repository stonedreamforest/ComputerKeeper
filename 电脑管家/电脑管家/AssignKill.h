#pragma once
#include "afxwin.h"


// AssignKill �Ի���

class AssignKill : public CDialogEx
{
	DECLARE_DYNAMIC(AssignKill)

public:
	AssignKill(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AssignKill();

// �Ի�������
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
//	CString m_str;		//��ק�ļ�����ʾ
	afx_msg void OnEnChangeEdit1();
	//CString m_FilePathName;
	CString m_FilePathName;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	bool m_IsKill;
//	virtual BOOL OnInitDialog();
};
