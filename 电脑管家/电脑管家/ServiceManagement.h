#pragma once
#include "afxcmn.h"
#include <vector>
#include <winsvc.h>
#include "ListCtrl.h"

using namespace std;

// ServiceManagement �Ի���

class ServiceManagement : public CDialogEx
{
	DECLARE_DYNAMIC(ServiceManagement)

public:
	ServiceManagement(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ServiceManagement();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	ListCtrl m_ServiceList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	vector<LPENUM_SERVICE_STATUS_PROCESS> m_VecServiceList;
	bool isInitEnd;
	TCHAR *TheCurrentState(DWORD TheState);//״̬
	TCHAR *TheServiceType(DWORD TheType);//��ǰ����
	TCHAR *TheStartType(DWORD TheType);//��������
	void ServiceIndex();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void StartService();
	afx_msg void PauseService();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
