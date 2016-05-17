#pragma once
#include "afxwin.h"
#include "ImageButton.h"
#include "MemoryOptimizer.h"
// HomePage �Ի���

class HomePage : public CDialogEx
{
	DECLARE_DYNAMIC(HomePage)

public:
	HomePage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HomePage();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

	void MovebkPicZuo(int BkgroundPic);		//���
	void MovebkPicXia(	int BkgroundPic);	//�½�
	void MovebkPicYou(	int BkgroundPic);	//�ҽ�
	void MovebkPicZuoxia(	int BkgroundPic);//�Ͻ�
	int m_BackgroundPic;
	bool m_ButtonState;
};
