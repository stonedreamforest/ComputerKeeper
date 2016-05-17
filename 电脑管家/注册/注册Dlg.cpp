
// ע��Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ע��.h"
#include "ע��Dlg.h"
#include "afxdialogex.h"
#include "winsock2.h"
#pragma comment(lib,"WS2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// Cע��Dlg �Ի���



Cע��Dlg::Cע��Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cע��Dlg::IDD, pParent)
	, m_Name(_T(""))
	, m_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cע��Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}

BEGIN_MESSAGE_MAP(Cע��Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cע��Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cע��Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cע��Dlg ��Ϣ�������

BOOL Cע��Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cע��Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cע��Dlg::OnPaint()
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
HCURSOR Cע��Dlg::OnQueryDragIcon()
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
		//��������
		nRecvSize=recv(sockClient,buf,1024,0);
		if (nRecvSize==SOCKET_ERROR)
		{
			MessageBox(0,L"���������˳���",0,0);
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
void Cע��Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_Name);
	GetDlgItem(IDC_EDIT2)->GetWindowText(m_password);
	UpdateData(TRUE);
}


void Cע��Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nErrCode=0;
	//��ʼ��socket
	InitWinSock();
	//�����׽���
	SOCKET sock=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(1234);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//���ӷ�����
	nErrCode=connect(sock,
		(sockaddr*)&addr,//ip��ַ
		sizeof(sockaddr_in));//ip ��ַ�Ĵ�С
	if (SOCKET_ERROR==nErrCode)
	{
		MessageBox(L"δ�������Թܼ�");
		exit(0);
	}
	//������Ϣ
	CString PassCode=m_Name+L"*"+m_password;
	CStringA hh(PassCode);
	//hh->GetBuffer(m_Name);
	char * h = hh.GetBuffer();
	nErrCode=send(sock,h,20,0);
	if (SOCKET_ERROR==nErrCode)
	{
		MessageBox(L"���ӵ��Թܼ�ʧ��");
	}

}
