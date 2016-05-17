#pragma once
#include "afxwin.h"
#include "ImageButton.h"
#include "shockwaveflash1.h"


// MemoryOptimizer �Ի���

class MemoryOptimizer : public CDialogEx
{
	DECLARE_DYNAMIC(MemoryOptimizer)

public:
	MemoryOptimizer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MemoryOptimizer();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	ImageButton m_MemoryButton;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CShockwaveflash1 m_CartoonPlay;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	bool m_Time;

	void MovebkPic(int BkgroundPic);
	int m_BackgroundPic;
	bool m_ButtonState;
	double m_Memzhanyong;
	int m_delMemory;
	CString hh;
	CString hd;
	void ClenMemory();	//�����ڴ�
	void WriteChar(int nHeight,int  nWidth, int nEscapement,int nOrientation,
		int x,int y,CString context,CString fontStyle=L"����",BYTE FontQuality=CLEARTYPE_QUALITY);	//��������
};
