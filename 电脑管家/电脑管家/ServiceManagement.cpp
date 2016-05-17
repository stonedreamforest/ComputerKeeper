// ServiceManagement.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "ServiceManagement.h"
#include "afxdialogex.h"
#include <vector>

// ServiceManagement �Ի���

IMPLEMENT_DYNAMIC(ServiceManagement, CDialogEx)

ServiceManagement::ServiceManagement(CWnd* pParent /*=NULL*/)
	: CDialogEx(ServiceManagement::IDD, pParent)
{
	isInitEnd=FALSE;
}

ServiceManagement::~ServiceManagement()
{
}

void ServiceManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ServiceList);
}


BEGIN_MESSAGE_MAP(ServiceManagement, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID__32771, &ServiceManagement::StartService)
	ON_COMMAND(ID__32772, &ServiceManagement::PauseService)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// ServiceManagement ��Ϣ�������


BOOL ServiceManagement::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	m_ServiceList.GetClientRect(rect);
	m_ServiceList.SetExtendedStyle(m_ServiceList.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//��ѡ�з��
	CString str[] ={_T(""), _T("����"), _T("��������"), _T("��ǰ����"), _T("��������"),  _T("�û���"), _T("������"),_T("·��")};

	for(int i=0; i<sizeof(str)/sizeof(str[0]); i++)
	{
		if (i==7)
		{
			m_ServiceList.InsertColumn(i, str[i], LVCFMT_LEFT, 500);
		}
		else if(i==6)
		{
			m_ServiceList.InsertColumn(i, str[i], LVCFMT_LEFT, 230);
		}
		else if(i==2)
		{
			m_ServiceList.InsertColumn(i, str[i], LVCFMT_LEFT, 210);
		}
		else if(i==4)
		{
			m_ServiceList.InsertColumn(i, str[i], LVCFMT_LEFT, 370);
		}
		else
		{
			m_ServiceList.InsertColumn(i, str[i], LVCFMT_LEFT, 150);
		}

	}
	m_ServiceList.DeleteColumn(0);//ɾ����0�� �������־���

	
	//m_ServiceList.SetLayeredWindowAttributes(RGB(0X80,0XC0,0XFF),255, LWA_COLORKEY);
	isInitEnd=true;

	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}

//��������
void ServiceManagement::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(!isInitEnd){
		return;
	}
	CRect rc ;
	GetClientRect(&rc);
	rc.DeflateRect(10,0,10,0);
	ServiceIndex();
	m_ServiceList.MoveWindow(rc,FALSE) ;
	// TODO: �ڴ˴������Ϣ����������
}


void ServiceManagement::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow==FALSE)
	{
		return;
	}
	ServiceIndex();//�л�����ˢ��
	// TODO: �ڴ˴������Ϣ����������
}
//����״̬
TCHAR * ServiceManagement::TheCurrentState(DWORD TheState)
{
	switch (TheState)
	{
	case SERVICE_CONTINUE_PENDING:
		return _T("��������");
	case SERVICE_PAUSE_PENDING:
		return _T("��ͣ����");
	case SERVICE_PAUSED:
		return _T("��ͣ");
	case SERVICE_RUNNING:
		return _T("��������");
	case SERVICE_START_PENDING:
		return _T("��������");
	case SERVICE_STOP_PENDING:
		return _T("����ֹͣ");
	default:
		break;
	}
	return _T("δ����");
}
//��������
TCHAR * ServiceManagement::TheServiceType(DWORD TheType)
{
	switch (TheType)
	{
	case SERVICE_FILE_SYSTEM_DRIVER:
		return _T("�ļ�ϵͳ��������");
	case SERVICE_KERNEL_DRIVER:
		return _T("�豸��������");
	case SERVICE_WIN32_OWN_PROCESS:
		return _T("�÷������������Լ��Ĺ�����");
	default:
		break;
	}
	return _T("�÷���������������һ������");
}
//��������
TCHAR * ServiceManagement::TheStartType(DWORD TheType)
{
	switch (TheType)
	{
	case SERVICE_AUTO_START:
		return _T("������ƹ�������ϵͳ����ʱ�Զ���������");
	case SERVICE_BOOT_START:
		return _T("��ϵͳװ�س����������豸��������,��ֵ�����������������");
	case SERVICE_DEMAND_START:
		return _T("����ʼ�ɷ�����ƹ�����,��һ�����̵���startService����");
	case SERVICE_DISABLED:
		return _T("���������ķ���.������������,���´���Ĵ���error_service_disabled");
	default:
		break;
	}
	return _T("��ioinitsystem���������豸�������򡣴�ֵ�����������������");
}
//��������
void ServiceManagement::ServiceIndex()
{
	SC_HANDLE hSCM=OpenSCManager(NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	DWORD dwServiceNum=0;
	DWORD dwSize=0;
	EnumServicesStatusEx(hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,//���з���״̬
		NULL,0,&dwSize,&dwServiceNum,
		NULL,NULL);
	//������Ҫ���ڴ� �ڶ��ε���
	LPENUM_SERVICE_STATUS_PROCESS pEnumSerice=(LPENUM_SERVICE_STATUS_PROCESS)LocalAlloc(LPTR,dwSize);
	//�ڶ���ö��
	BOOL bStattus=EnumServicesStatusEx(hSCM,
		SC_ENUM_PROCESS_INFO,
		SERVICE_WIN32,
		SERVICE_STATE_ALL,//���з���״̬
		(PBYTE)pEnumSerice,dwSize,&dwSize,&dwServiceNum,
		NULL,NULL);
	//������Ϣ
	for (DWORD i=0;i<dwServiceNum;i++)
	{
		//��ȡ������Ϣ

		//	pEnumSerice[i].lpDisplayName;
		//	pEnumSerice[i].lpServiceName;//������
		//pEnumSerice[i].ServiceStatusProcess.dwCurrentState;//����״̬
		//pEnumSerice[i].ServiceStatusProcess.dwServiceType;//�����ִ������
		TCHAR *ServiceType=TheServiceType(pEnumSerice[i].ServiceStatusProcess.dwServiceType);

		//	_stprintf_s(ServiceType,_T("%d"),);
		//��ȡ��ǰ����
		TCHAR* CurrentState=TheCurrentState(pEnumSerice[i].ServiceStatusProcess.dwCurrentState);
		//	_stprintf_s(CurrentState,_T("%d"),);
		m_ServiceList.InsertItem(0,pEnumSerice[i].lpServiceName);
		m_ServiceList.SetItemText(0,1,ServiceType);
		m_ServiceList.SetItemText(0,2,CurrentState);
		//��ȡ����������ϸ��Ϣ
		SC_HANDLE hService=OpenService(hSCM,pEnumSerice[i].lpServiceName,SERVICE_QUERY_CONFIG);

		//��һ�ε��û�ȡ��Ҫ�Ļ�������С
		QueryServiceConfig(hService,NULL,0,&dwSize);
		//�����ڴ�
		LPQUERY_SERVICE_CONFIG pServiceConfig=(LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR,dwSize);
		//�ڶ��ε��û�ȡ��Ϣ
		QueryServiceConfig(hService,pServiceConfig,dwSize,&dwSize);
		//ͨ�������ȡ���Ľṹ����Ϣ���嵽��Ҫ��ֵ

		TCHAR *StartType=TheStartType(pServiceConfig->dwStartType);;//��ȡ��������
		//_stprintf_s(StartType,_T("%d"),);
		//	_stprintf_s(StartType,_T("%d"),pServiceConfig->dwStartType);
		m_ServiceList.SetItemText(0,3,StartType);
		m_ServiceList.SetItemText(0,4,pServiceConfig->lpLoadOrderGroup);
		m_ServiceList.SetItemText(0,5,pServiceConfig->lpServiceStartName);
		m_ServiceList.SetItemText(0,6,pServiceConfig->lpBinaryPathName);

		m_VecServiceList.push_back(pEnumSerice+i);
	}
}

//�˵�
void ServiceManagement::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	m_ServiceList.GetClientRect(&rect);//�ɵ����Χ  
	CPoint p;

	//GetPhysicalCursorPos(&p);//�������
	GetCursorPos(&p);
	rect.DeflateRect(0,23,0,0);
	m_ServiceList.ClientToScreen(rect);//������Ļ����
	if (rect.PtInRect(p))//�ж��Ƿ��ڿͻ���listctrl��Χ��
	{
		CMenu Menu;
		Menu.LoadMenuW(IDR_MENU1);//�˵���Դ
		CMenu *SubMenu=Menu.GetSubMenu(0);
		SubMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON,p.x,p.y,this);
		//SubMenu->Detach();
		//Menu.DestroyMenu();//����
	}
}

SERVICE_STATUS servicestatus;
SERVICE_STATUS_HANDLE servicestatushandle;
void WINAPI ServiceCtrlHandler(DWORD dwControl)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_PAUSE:
		servicestatus.dwCurrentState = SERVICE_PAUSE_PENDING;
		servicestatus.dwCurrentState = SERVICE_PAUSED;
		break;
	case SERVICE_CONTROL_CONTINUE:
		servicestatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
		SetServiceStatus(servicestatushandle, &servicestatus);
		servicestatus.dwCurrentState = SERVICE_RUNNING;
		break;
	case SERVICE_CONTROL_STOP:
		servicestatus.dwCurrentState = SERVICE_STOP_PENDING;
		SetServiceStatus(servicestatushandle, &servicestatus);
		servicestatus.dwCurrentState = SERVICE_STOPPED;
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		break;
	case SERVICE_CONTROL_INTERROGATE:
		servicestatus.dwCurrentState = SERVICE_RUNNING;
		break;
	}
	SetServiceStatus(servicestatushandle, &servicestatus);
}
//��������
void ServiceManagement::StartService()
{
	// TODO: �ڴ���������������
	servicestatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//���ܷ��� 
	POSITION pos = m_ServiceList.GetFirstSelectedItemPosition();
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
		while (pos)
		{
			int nItem = m_ServiceList.GetNextSelectedItem(pos);
			SERVICE_STATUS_HANDLE hServiceStatus = RegisterServiceCtrlHandler(
					m_VecServiceList[m_VecServiceList.size()-(nItem+1)]->lpServiceName,
					ServiceCtrlHandler);
			m_ServiceList.SetItemText(nItem,2,L"��������");
			servicestatus.dwCurrentState=SERVICE_RUNNING;
			SetServiceStatus(servicestatushandle, &servicestatus);
		}
	}
}


//��ͣ����
void ServiceManagement::PauseService()
{
	// TODO: �ڴ���������������
	servicestatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;//���ܷ��� 
	POSITION pos = m_ServiceList.GetFirstSelectedItemPosition();
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
		while (pos)
		{
			int nItem = m_ServiceList.GetNextSelectedItem(pos);
			SERVICE_STATUS_HANDLE hServiceStatus = RegisterServiceCtrlHandler(
				m_VecServiceList[m_VecServiceList.size()-(nItem+1)]->lpServiceName,
				ServiceCtrlHandler);
			m_ServiceList.SetItemText(nItem,2,L"δ����");
			servicestatus.dwCurrentState=SERVICE_STOPPED;
			SetServiceStatus(servicestatushandle, &servicestatus);
		}
	}
}

//���� ENTER ESC����Ӧ 
BOOL ServiceManagement::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->wParam==VK_RETURN)
	{
		//Do anything what you want to
		return true;//����enter��Ϣ��Ӧ
	}
	if(pMsg->wParam == VK_ESCAPE)  
	{  
		return true;  //����esc��Ϣ��Ӧ
	}  
	return CDialogEx::PreTranslateMessage(pMsg);
}


//BOOL ServiceManagement::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CRect rect;	
//	GetClientRect(&rect);	//���ر���λͼ	
//	CBitmap bmpBackground;
//	bmpBackground.LoadBitmap(IDB_BITMAP38); //ͼƬID	
//	BITMAP bitmap;   
//	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
//	CDC dc;	dc.CreateCompatibleDC(pDC);
//	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//����λͼ	
//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��
//	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
//	dc.SelectObject(pOldBitmap);
//	Sleep(100);
//	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
//}
