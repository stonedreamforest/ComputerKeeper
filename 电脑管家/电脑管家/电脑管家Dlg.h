
// ���Թܼ�Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TabControl.h"
#include "afxwin.h"
#include "ImageButton.h"
// C���Թܼ�Dlg �Ի���
class C���Թܼ�Dlg : public CDialogEx
{
// ����
public:
	C���Թܼ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	ImageButton m_CloseButton;	//�رմ���
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	ImageButton m_ShoWinButton;	//��С��

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
	static C���Թܼ�Dlg * m_this;
};
