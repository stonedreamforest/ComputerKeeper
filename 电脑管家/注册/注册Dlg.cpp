
// 注册Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "注册.h"
#include "注册Dlg.h"
#include "afxdialogex.h"
#include "winsock2.h"
#pragma comment(lib,"WS2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C注册Dlg 对话框



C注册Dlg::C注册Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C注册Dlg::IDD, pParent)
	, m_Name(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C注册Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}

BEGIN_MESSAGE_MAP(C注册Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C注册Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C注册Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// C注册Dlg 消息处理程序

BOOL C注册Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
//	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
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

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C注册Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C注册Dlg::OnPaint()
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
HCURSOR C注册Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD ThreadProc(LPVOID prama)
{
	SOCKET sockClient=(SOCKET)prama;
	int nRecvSize=0;
	while (true)
	{
		char buf[1024];
		//接受数据
		nRecvSize=recv(sockClient,buf,1024,0);
		if (nRecvSize==SOCKET_ERROR)
		{
			MessageBox(0,L"主程序已退出！",0,0);
			exit(0);			
		}
		else
		{
			printf("%s\n",buf);
		}
	}
}
BOOL InitWinSock()
{
	WSADATA stcData;
	int nResult=0;
	nResult=WSAStartup(MAKEWORD(2,2),&stcData);
	if (nResult==SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}
void C注册Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_Name);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_password);
	UpdateData(TRUE);
}


void C注册Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nErrCode=0;
	//初始化socket
	InitWinSock();
	//创建套接字
	SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(1234);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//连接服务器
	nErrCode=connect(sock,
		(sockaddr*)&addr,//ip地址
		sizeof(sockaddr_in));//ip 地址的大小
	if (SOCKET_ERROR==nErrCode)
	{
		MessageBox(L"未启动电脑管家");
		exit(0);
	}
	//发送消息
	CString PassCode=m_Name+L"*"+m_password;
	CStringA hh(PassCode);
	//hh->GetBuffer(m_Name);
	char * h = hh.GetBuffer();
	nErrCode=send(sock,h,20,0);
	if (SOCKET_ERROR==nErrCode)
	{
		MessageBox(L"连接电脑管家失败");
	}

}
