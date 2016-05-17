
// 电脑管家Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "电脑管家Dlg.h"
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
C电脑管家Dlg * C电脑管家Dlg::m_this=NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C电脑管家Dlg 对话框



C电脑管家Dlg::C电脑管家Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C电脑管家Dlg::IDD, pParent)
{
	m_IsWindowHide=false;
	IsShowIma=TRUE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_this=this;
}

void C电脑管家Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(C电脑管家Dlg, CDialogEx)
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
ON_BN_CLICKED(IDC_BUTTON1, &C电脑管家Dlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON7, &C电脑管家Dlg::OnBnClickedButton7)
ON_BN_CLICKED(IDC_BUTTON2, &C电脑管家Dlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON3, &C电脑管家Dlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &C电脑管家Dlg::OnBnClickedButton4)
ON_WM_MOUSEMOVE()
ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &C电脑管家Dlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// C电脑管家Dlg 消息处理程序

BOOL C电脑管家Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

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
	m_CloseButton.MoveWindow(winRect.right-btnRect.right,2,btnRect.right,btnRect.bottom-4);		//调校按钮位置 参数无视吧
	m_ShoWinButton.MoveWindow(winRect.right-btnRect.right-23,2,btnRect.right,btnRect.bottom-4);
	m_MenuButton.MoveWindow(winRect.right-btnRect.right-50,2,btnRect.right+5,btnRect.bottom-4);
	m_CloudButton.MoveWindow(winRect.right-btnRect.right-77,2,btnRect.right+6,btnRect.bottom-4);
	//m_MailButton.MoveWindow(winRect.right-btnRect.right-92,2,btnRect.right,btnRect.bottom-2);
	//m_CloseButton.MoveWindow(453,)
	// TODO: 在此添加额外的初始化代码
	::RegisterHotKey(this->GetSafeHwnd(),0xa001,MOD_CONTROL|MOD_SHIFT,'P');//注册热键 
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

	m_Tab.InsertItem(0,_T("首页体检"));
	m_Tab.InsertItem(1,_T("病毒查杀"));
	m_Tab.InsertItem(2,_T("服务管理"));
	m_Tab.InsertItem(3,_T("软件卸载"));
	m_Tab.InsertItem(4,_T("启动项管理"));
	m_Tab.InsertItem(5,_T("垃圾清理"));
	m_Tab.InsertItem(6,_T("内存优化"));
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C电脑管家Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C电脑管家Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C电脑管家Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//热键 
void C电脑管家Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nHotKeyId==0xa001)
	{
		//隐藏窗口
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




BOOL C电脑管家Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	CRect rect;	
// 	GetWindowRect(&rect);	//加载背景位图	
// 	CBitmap bmpBackground;
// 	bmpBackground.LoadBitmap(IDB_BITMAP2); //图片ID	
// 	BITMAP bitmap;   
// 	bmpBackground.GetBitmap(&bitmap); 	//选择位图	//创建内存DC	
// 	CDC dc;	dc.CreateCompatibleDC(pDC);
// 	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//绘制位图	
// 	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式。
// 	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
// 	dc.SelectObject(pOldBitmap);	
	return TRUE;
}


LRESULT C电脑管家Dlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return HTCAPTION;
	//return CDialogEx::OnNcHitTest(point);
}





HBRUSH C电脑管家Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);


	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(255,0,0));     //字体颜色
		pDC-> SetBkColor(TRANSPARENT);       //字体背景色   
		
	}
	// TODO: Return a different brush if the default is not desired


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}




//关闭
void C电脑管家Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}

//显示
void C电脑管家Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	//ShowWindow(SW_HIDE);
	CloseWindow();
}

//菜单
void C电脑管家Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
}

//云
void C电脑管家Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"你有20秒注册时间",L"提示",0);
	InintWinSock();//注册登录
	InitTCP();
	
}


void C电脑管家Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	int i=0;
}


void C电脑管家Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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


void C电脑管家Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void C电脑管家Dlg::InintWinSock()
{
	WSADATA stcData;
	int nResult=0;
	//指定需要使用的wincsock规范最高版本 并初始化 winsock 装入winscok.dll
	nResult=WSAStartup(MAKEWORD(2,2),&stcData);
	if (nResult==SOCKET_ERROR)
	{
		MessageBox(L"服务器出错了！");
	}
	return ;
}

void C电脑管家Dlg::InitTCP()
{
	int nErrcode=0;//错误代码
	//创建套接字
	SOCKET sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	//设置套接字非阻塞模式
	unsigned long u1=1;	//设置套接字选项
	int nRet=ioctlsocket(sock,FIONBIO,&u1);

	//初始化ip地址  
	sockaddr_in addr;
	addr.sin_family=AF_INET;	//地址家族
	addr.sin_port=htons(1234);	//端口号  大端到小端
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");//IP地址  本地:127.0.0.1
	//取得本地主机名称
	//char szHost[MAX_PATH]={0};
	//gethostbyname(szHost);
	//通过主机名取到地址信息
	//HOSTENT *pHost=gethostbuname(szHost);

	//绑定套接字
	nErrcode=bind(sock,	//套接字
		(sockaddr*)&addr,//	ip 地址
		sizeof(sockaddr_in));//ip 地址结构体大小 
	if (SOCKET_ERROR==nErrcode)
	{
		printf("ip地址绑定失败");
		closesocket(sock);	//关闭套接字
		WSACleanup();		//释放套接字
	}
	//监听
	nErrcode=listen(sock,
		SOMAXCONN);//能够同时连接的最大数目
	if (SOCKET_ERROR==nErrcode)
	{
		MessageBox(L"服务器有问题");
		goto CloseSock;
	}
	int nAddrSize=sizeof(sockaddr_in);
//	system
	WinExec(".\\注册.exe",0);
	while (true)
	{
		sockaddr_in addrClient;
		memset(&addrClient,0,sizeof(sockaddr_in));

		addrClient.sin_family=AF_INET;
		//连接
		SOCKET ClientSocket=accept(sock,
			(sockaddr*)&addrClient,
			&nAddrSize);
		if (INVALID_SOCKET==ClientSocket)
		{
			continue;
		}
	//	NAME PlayName;
	//	PlayName.Sock=ClientSocket;
	//	g_player.push_back(PlayName);	//保存连接套接字
		//创建线程  结构客户端的消息
	CreateThread(0,0,ThreadProc,(LPVOID)ClientSocket,0,0);
	}
	return ;
CloseSock:
	closesocket(sock);
	WSACleanup();
	return ;
}

DWORD WINAPI C电脑管家Dlg::ThreadProc(LPVOID prama)
{
	SOCKET sockClient=(SOCKET)prama;
	int nRecvSize=0;
	while (true)
	{
		char buf[1024]={0};
		//接受客户端发送的数据
		nRecvSize=recv(sockClient,	//套接字
			buf,		//接受的缓冲区大小
			1024,		//缓冲区大小
			0);			//影响该函数的行为
		//0  无特殊行为
		//MSB_OOB :使用有用的数据复制到接受缓冲区 不用系统缓冲区中删除

		if (SOCKET_ERROR!=nRecvSize)//SOCKET_ERROR  -1
		{
			return 0;
		}
	}
}





