
// ���Թܼ�Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "���Թܼ�Dlg.h"
#include "afxdialogex.h"
#include "HomePage.h"
#include "VirusScanner.h"
#include "ServiceManagement.h"
#include "UninstallTool.h"
#include "StartupManager.h"
#include "CleanSpace.h"
#include "MemoryOptimizer.h"
#include <winsock2.h>
#pragma comment(lib,"WS2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
C���Թܼ�Dlg * C���Թܼ�Dlg::m_this=NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
//	ON_WM_ERASEBKGND()
//	ON_WM_CONTEXTMENU()
//	ON_WM_DRAWITEM()
//	ON_WM_NCHITTEST()
//	ON_WM_DRAWITEM()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// C���Թܼ�Dlg �Ի���



C���Թܼ�Dlg::C���Թܼ�Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C���Թܼ�Dlg::IDD, pParent)
{
	m_IsWindowHide=false;
	IsShowIma=TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_this=this;
}

void C���Թܼ�Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_BUTTON1, m_CloseButton);
	DDX_Control(pDX, IDC_BUTTON7, m_ShoWinButton);
	DDX_Control(pDX, IDC_BUTTON2, m_MenuButton);
	DDX_Control(pDX, IDC_BUTTON3, m_CloudButton);
//	DDX_Control(pDX, IDC_BUTTON4, m_MailButton);
}

BEGIN_MESSAGE_MAP(C���Թܼ�Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_SIZE()
//ON_WM_ERASEBKGND()
ON_WM_HOTKEY()
ON_WM_ERASEBKGND()
ON_WM_NCHITTEST()
//ON_WM_DRAWITEM()
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON1, &C���Թܼ�Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON7, &C���Թܼ�Dlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON2, &C���Թܼ�Dlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &C���Թܼ�Dlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &C���Թܼ�Dlg::OnBnClickedButton4)
ON_WM_MOUSEMOVE()
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &C���Թܼ�Dlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// C���Թܼ�Dlg ��Ϣ�������

BOOL C���Թܼ�Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

//	ShowWindow(SW_MINIMIZE);
	m_CloseButton.InitialImage(IDB_BITMAP10,IDB_BITMAP30,IDB_BITMAP31);
	m_ShoWinButton.InitialImage(IDB_BITMAP11,IDB_BITMAP15,IDB_BITMAP32);
	m_MenuButton.InitialImage(IDB_BITMAP12,IDB_BITMAP26,IDB_BITMAP29);
	m_CloudButton.InitialImage(IDB_BITMAP13,IDB_BITMAP27,IDB_BITMAP28);
//	m_MailButton.InitialImage(IDB_BITMAP14);
	CRect winRect;
	CRect btnRect(0,0,23,24);
	GetClientRect(&winRect);
	//m_CloseButton.GetClientRect(&btnRect);
	m_CloseButton.MoveWindow(winRect.right-btnRect.right,2,btnRect.right,btnRect.bottom-4);		//��У��ťλ�� �������Ӱ�
	m_ShoWinButton.MoveWindow(winRect.right-btnRect.right-23,2,btnRect.right,btnRect.bottom-4);
	m_MenuButton.MoveWindow(winRect.right-btnRect.right-50,2,btnRect.right+5,btnRect.bottom-4);
	m_CloudButton.MoveWindow(winRect.right-btnRect.right-77,2,btnRect.right+6,btnRect.bottom-4);
	//m_MailButton.MoveWindow(winRect.right-btnRect.right-92,2,btnRect.right,btnRect.bottom-2);
	//m_CloseButton.MoveWindow(453,)
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	::RegisterHotKey(this->GetSafeHwnd(),0xa001,MOD_CONTROL|MOD_SHIFT,'P');//ע���ȼ� 
	CImageList ImageList;
	ImageList.Create(32,21,ILC_COLOR32|ILC_MASK,7,1);
	TabControl *pApp=(TabControl *)AfxGetApp( );	
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));//IDI_ICON5
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
//	AfxGetApp()->LoadStandardIcon(MAKEINTRESOURCE(IDI_ICON1));
//	::LoadIcon(NULL,MAKEINTRESOURCE(IDI_ICON1));
	TCITEM tcitem;

	m_Tab.InsertItem(0,_T("��ҳ���"));
	m_Tab.InsertItem(1,_T("������ɱ"));
	m_Tab.InsertItem(2,_T("�������"));
	m_Tab.InsertItem(3,_T("���ж��"));
	m_Tab.InsertItem(4,_T("���������"));
	m_Tab.InsertItem(5,_T("��������"));
	m_Tab.InsertItem(6,_T("�ڴ��Ż�"));
	m_Tab.addDlg(7,
		IDD_DIALOG1,new HomePage,
		IDD_DIALOG2,new VirusScanner,
		IDD_DIALOG3,new ServiceManagement,
		IDD_DIALOG4,new UninstallTool,
		IDD_DIALOG5,new StartupManager,
		IDD_DIALOG6,new CleanSpace,
		IDD_DIALOG7,new MemoryOptimizer);
	m_Tab.SetImageList(&ImageList);
	ImageList.Detach();
	tcitem.mask=TCIF_IMAGE;
	for (int i=0;i<7;i++)
	{
		m_Tab.GetItem(i,&tcitem);
		tcitem.iImage=i;
		m_Tab.SetItem(i,&tcitem);
	}
	m_Tab.setshow(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C���Թܼ�Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C���Թܼ�Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C���Թܼ�Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//�ȼ� 
void C���Թܼ�Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nHotKeyId==0xa001)
	{
		//���ش���
		if (m_IsWindowHide==true)
		{
			ShowWindow(SW_SHOW);
			m_IsWindowHide=false;
		}
		else
		{
			ShowWindow(SW_HIDE);
			m_IsWindowHide=true;
		}
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}




BOOL C���Թܼ�Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
// 	CRect rect;	
// 	GetWindowRect(&rect);	//���ر���λͼ	
// 	CBitmap bmpBackground;
// 	bmpBackground.LoadBitmap(IDB_BITMAP2); //ͼƬID	
// 	BITMAP bitmap;   
// 	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
// 	CDC dc;	dc.CreateCompatibleDC(pDC);
// 	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//����λͼ	
// 	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��
// 	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
// 	dc.SelectObject(pOldBitmap);	
	return TRUE;
}


LRESULT C���Թܼ�Dlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return HTCAPTION;
	//return CDialogEx::OnNcHitTest(point);
}





HBRUSH C���Թܼ�Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(255,0,0));     //������ɫ
		pDC-> SetBkColor(TRANSPARENT);       //���屳��ɫ   
		
	}
	// TODO: Return a different brush if the default is not desired


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}




//�ر�
void C���Թܼ�Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}

//��ʾ
void C���Թܼ�Dlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ShowWindow(SW_HIDE);
	CloseWindow();
}

//�˵�
void C���Թܼ�Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//��
void C���Թܼ�Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"����20��ע��ʱ��",L"��ʾ",0);
	InintWinSock();//ע���¼
	InitTCP();
	
}


void C���Թܼ�Dlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i=0;
}


void C���Թܼ�Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect btnRect;
	m_ShoWinButton.GetClientRect(&btnRect);
	BOOL flag = btnRect.PtInRect(point);
	if (flag)
	{
		m_ShoWinButton.InitialImage(IDB_BITMAP15);
		m_ShoWinButton.Invalidate(TRUE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void C���Թܼ�Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void C���Թܼ�Dlg::InintWinSock()
{
	WSADATA stcData;
	int nResult=0;
	//ָ����Ҫʹ�õ�wincsock�淶��߰汾 ����ʼ�� winsock װ��winscok.dll
	nResult=WSAStartup(MAKEWORD(2,2),&stcData);
	if (nResult==SOCKET_ERROR)
	{
		MessageBox(L"�����������ˣ�");
	}
	return ;
}

void C���Թܼ�Dlg::InitTCP()
{
	int nErrcode=0;//�������
	//�����׽���
	SOCKET sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	//�����׽��ַ�����ģʽ
	unsigned long u1=1;	//�����׽���ѡ��
	int nRet=ioctlsocket(sock,FIONBIO,&u1);

	//��ʼ��ip��ַ  
	sockaddr_in addr;
	addr.sin_family=AF_INET;	//��ַ����
	addr.sin_port=htons(1234);	//�˿ں�  ��˵�С��
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//IP��ַ  ����:127.0.0.1
	//ȡ�ñ�����������
	//char szHost[MAX_PATH]={0};
	//gethostbyname(szHost);
	//ͨ��������ȡ����ַ��Ϣ
	//HOSTENT *pHost=gethostbuname(szHost);

	//���׽���
	nErrcode=bind(sock,	//�׽���
		(sockaddr*)&addr,//	ip ��ַ
		sizeof(sockaddr_in));//ip ��ַ�ṹ���С 
	if (SOCKET_ERROR==nErrcode)
	{
		printf("ip��ַ��ʧ��");
		closesocket(sock);	//�ر��׽���
		WSACleanup();		//�ͷ��׽���
	}
	//����
	nErrcode=listen(sock,
		SOMAXCONN);//�ܹ�ͬʱ���ӵ������Ŀ
	if (SOCKET_ERROR==nErrcode)
	{
		MessageBox(L"������������");
		goto CloseSock;
	}
	int nAddrSize=sizeof(sockaddr_in);
//	system
	WinExec(".\\ע��.exe",0);
	while (true)
	{
		sockaddr_in addrClient;
		memset(&addrClient,0,sizeof(sockaddr_in));

		addrClient.sin_family=AF_INET;
		//����
		SOCKET ClientSocket=accept(sock,
			(sockaddr*)&addrClient,
			&nAddrSize);
		if (INVALID_SOCKET==ClientSocket)
		{
			continue;
		}
	//	NAME PlayName;
	//	PlayName.Sock=ClientSocket;
	//	g_player.push_back(PlayName);	//���������׽���
		//�����߳�  �ṹ�ͻ��˵���Ϣ
	CreateThread(0,0,ThreadProc,(LPVOID)ClientSocket,0,0);
	}
	return ;
CloseSock:
	closesocket(sock);
	WSACleanup();
	return ;
}

DWORD WINAPI C���Թܼ�Dlg::ThreadProc(LPVOID prama)
{
	SOCKET sockClient=(SOCKET)prama;
	int nRecvSize=0;
	while (true)
	{
		char buf[1024]={0};
		//���ܿͻ��˷��͵�����
		nRecvSize=recv(sockClient,	//�׽���
			buf,		//���ܵĻ�������С
			1024,		//��������С
			0);			//Ӱ��ú�������Ϊ
		//0  ��������Ϊ
		//MSB_OOB :ʹ�����õ����ݸ��Ƶ����ܻ����� ����ϵͳ��������ɾ��

		if (SOCKET_ERROR!=nRecvSize)//SOCKET_ERROR  -1
		{
			return 0;
		}
	}
}





