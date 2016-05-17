// VirusScanner.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "VirusScanner.h"
#include "afxdialogex.h"
#include "AssignKill.h"

// VirusScanner 对话框

IMPLEMENT_DYNAMIC(VirusScanner, CDialogEx)


VirusScanner * VirusScanner::m_this = NULL;
VirusScanner::VirusScanner(CWnd* pParent /*=NULL*/)
	: CDialogEx(VirusScanner::IDD, pParent)
{
	IsShow=FALSE;
	m_this = this;
	m_ButtonState=false;
	isInThead=false;
}

VirusScanner::~VirusScanner()
{
}

void VirusScanner::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_BUTTON1, m_StartupButton1);
	//  DDX_Control(pDX, IDC_BUTTON2, m_StartupButton2);
	DDX_Control(pDX, IDC_BUTTON1, m_StartupVirus1);
	DDX_Control(pDX, IDC_BUTTON2, m_StartupVirus2);
	DDX_Control(pDX, IDC_BUTTON3, m_AllKill);
	DDX_Control(pDX, IDC_BUTTON4, m_AssignButton);
}


BEGIN_MESSAGE_MAP(VirusScanner, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON3, &VirusScanner::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &VirusScanner::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &VirusScanner::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &VirusScanner::OnBnClickedButton2)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// VirusScanner 消息处理程序


void VirusScanner::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (!IsShow)
	{
		return;
	}
	m_AllKill.ShowWindow(SW_HIDE);
	m_AssignButton.ShowWindow(SW_HIDE);

	// TODO: 在此处添加消息处理程序代码
}


void VirusScanner::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow==FALSE)
	{
		return;
	}
	// TODO: 在此处添加消息处理程序代码
}


BOOL VirusScanner::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isInThead)
	{
		m_BackgroundPic=IDB_BITMAP46;
		goto there;
	}
	if (!m_ButtonState)
	{
		return true;
	}
there:	CRect rect;	
	GetClientRect(&rect);	//加载背景位图	
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(m_BackgroundPic); //图片ID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//选择位图	//创建内存DC	
	CDC dc;	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//绘制位图	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式。
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
	dc.SelectObject(pOldBitmap);	
	return TRUE;
}


BOOL VirusScanner::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_StartupVirus1.MoveWindow(410,250,150,55);
	m_StartupVirus2.MoveWindow(560,250,27,55);
	m_BackgroundPic=IDB_BITMAP5;
	m_ButtonState=true;
	m_StartupVirus1.InitialImage(IDB_BITMAP7,IDB_BITMAP18,IDB_BITMAP19);
	m_StartupVirus2.InitialImage(IDB_BITMAP8,IDB_BITMAP20,IDB_BITMAP21);
	return TRUE;  // return TRUE unless you set the focus to a control

}

DWORD WINAPI VirusScanner::AllProc(LPVOID lpThreadParameter)
{
	m_this->isInThead=true;
	WCHAR DiskName[MAX_PATH] = {0};
	GetLogicalDriveStrings(MAX_PATH,DiskName);
	int i = 0,j=0;
	for (; DiskName[i]!='\0'&& i < MAX_PATH; i++,j++)
	{
		m_this->TraverseFolder(DiskName,L".txt.exe.dll");
		i+=wcslen(&DiskName[i]);
		
	}
	if (!m_this->m_ButtonState)
	{

	m_this->	m_BackgroundPic=IDB_BITMAP5;//背景图片
	m_this->	MovebkPic(m_this->m_BackgroundPic);
	m_this->	m_ButtonState=true;
	m_this->	isInThead=false;

		//	m_AllKill.ShowWindow(SW_SHOW);
		//	m_AssignButton.ShowWindow(SW_SHOW)
	m_this->	m_StartupVirus1.ShowWindow(SW_SHOW);
	m_this->	m_StartupVirus2.ShowWindow(SW_SHOW);
	}
	return 0;
}
//全盘杀毒
void VirusScanner::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBoxA( 0,,0,0 );
	m_AllKill.ShowWindow(SW_HIDE);
	m_AssignButton.ShowWindow(SW_HIDE);
	m_StartupVirus1.ShowWindow(SW_HIDE);
	m_StartupVirus2.ShowWindow(SW_HIDE);
	if (m_ButtonState)
	{
		m_BackgroundPic=IDB_BITMAP46;//背景图片
		MovebkPic(m_BackgroundPic);
		m_ButtonState=false;
	}
	CreateThread(0,0,AllProc,0,0,0);

}

//指定位置杀毒
void VirusScanner::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBoxA( 0,md5FileValue("C:\\Users\\Administrator\\Desktop\\图片\\杀毒\\指定位置1.bmp"),0,0 );


	//if (m_ButtonState)
	//{
	//	m_BackgroundPic=IDB_BITMAP46;//背景图片
	//	MovebkPic(m_BackgroundPic);
	//	m_ButtonState=false;
	//}
	//TraverseFolder(L"C:\\Users\\Administrator\\Desktop\\图片\\杀毒",L".bmp");
	//if (!m_ButtonState)
	//{
	//	m_BackgroundPic=IDB_BITMAP5;//背景图片
	//	MovebkPic(m_BackgroundPic);
	//	m_ButtonState=true;
	////	m_AllKill.ShowWindow(SW_SHOW);
	////	m_AssignButton.ShowWindow(SW_SHOW);
	//	m_StartupVirus1.ShowWindow(SW_SHOW);
	//	m_StartupVirus2.ShowWindow(SW_SHOW);
	AssignKill dlg;
	dlg.DoModal();
	if (dlg.m_IsKill)
	{
		m_AllKill.ShowWindow(SW_HIDE);
		m_AssignButton.ShowWindow(SW_HIDE);
		m_StartupVirus1.ShowWindow(SW_HIDE);
		m_StartupVirus2.ShowWindow(SW_HIDE);
		if (wcscmp(dlg.m_FilePathName,L"")==0)
		{
			m_StartupVirus1.ShowWindow(SW_SHOW);
			m_StartupVirus2.ShowWindow(SW_SHOW);
			return;
		}
		if (m_ButtonState)
		{
			m_BackgroundPic=IDB_BITMAP46;//背景图片
			MovebkPic(m_BackgroundPic);
			m_ButtonState=false;
		}
		TraverseFolder(dlg.m_FilePathName,L".bmp");
		dlg.m_IsKill=false;
		dlg.m_FilePathName=L"";
		if (!m_ButtonState)
		{

			m_BackgroundPic=IDB_BITMAP5;//背景图片
			MovebkPic(m_BackgroundPic);
			m_ButtonState=true;
			//	m_AllKill.ShowWindow(SW_SHOW);
			//	m_AssignButton.ShowWindow(SW_SHOW)
			m_StartupVirus1.ShowWindow(SW_SHOW);
			m_StartupVirus2.ShowWindow(SW_SHOW);
		}
		return;
	}
	m_AllKill.ShowWindow(SW_HIDE);
	m_AssignButton.ShowWindow(SW_HIDE);
}
DWORD WINAPI VirusScanner::LightningProc(LPVOID lpThreadParameter)
{
	//C:\\Program Files (x86)   C:\\Program Files  D:\Program Files
	m_this->isInThead=true;
	WCHAR DiskName[MAX_PATH][MAX_PATH] = {
						_T("C:\\Program Files (x86)"),		//闪电杀毒查杀的范围
						_T("C:\\Program Files"),
						_T("D:\\Program Files"),
						_T("D:\\Program Files (x86)"),
						_T("E:\\Program Files"),
						_T("E:\\Program Files (x86)"),
	};
	int i = 0;
	for (; i<7; i++)
	{
		m_this->TraverseFolder(DiskName[i],L".txt.exe.dll.mp3.avi");	//填写要扫描的类型
	}
	if (!m_this->m_ButtonState)
	{

	m_this->	m_BackgroundPic=IDB_BITMAP5;//背景图片
	m_this->	MovebkPic(m_this->m_BackgroundPic);
	m_this->	m_ButtonState=true;
	m_this->	isInThead=false;
		//	m_AllKill.ShowWindow(SW_SHOW);
		//	m_AssignButton.ShowWindow(SW_SHOW)
	m_this->	m_StartupVirus1.ShowWindow(SW_SHOW);
	m_this->	m_StartupVirus2.ShowWindow(SW_SHOW);
	}
	return 1;
}

//闪电杀毒
void VirusScanner::OnBnClickedButton1()
{

	m_AllKill.ShowWindow(SW_HIDE);
	m_AssignButton.ShowWindow(SW_HIDE);
	m_StartupVirus1.ShowWindow(SW_HIDE);
	m_StartupVirus2.ShowWindow(SW_HIDE);
	if (m_ButtonState)
	{
		m_BackgroundPic=IDB_BITMAP46;//背景图片
		MovebkPic(m_BackgroundPic);
		m_ButtonState=false;
	}
	CreateThread(0,0,LightningProc,0,0,0);


	// TODO: 在此添加控件通知处理程序代码
	//MessageBoxA( 0,md5FileValue("C:\\Users\\Administrator\\Desktop\\图片\\杀毒\\指定位置1.bmp"),0,0 );
	
}

//更多
void VirusScanner::OnBnClickedButton2()
{
	m_AllKill.MoveWindow(410,305,177,39);
	m_AllKill.InitialImage(IDB_BITMAP40,IDB_BITMAP41,IDB_BITMAP42);
	m_AssignButton.MoveWindow(410,344,177,37);
	m_AssignButton.InitialImage(IDB_BITMAP43,IDB_BITMAP44,IDB_BITMAP45);
	m_AllKill.ShowWindow(SW_SHOW);
	m_AssignButton.ShowWindow(SW_SHOW);
//	clock_t start, finish; 

//	
	// TODO: 在此添加控件通知处理程序代码
}


void VirusScanner::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect btnRT;
	
	//m_StartupVirus1;//闪电杀毒
	//m_StartupVirus2;//下拉框按钮
	//m_AllKill;      //全盘杀毒
	//m_AssignButton; //指定位置杀毒
	
	m_StartupVirus1.GetClientRect(&btnRT);
	if(btnRT.PtInRect(point)){return;}
	m_StartupVirus2.GetClientRect(&btnRT);
	if(btnRT.PtInRect(point)){return;}
	m_AllKill.GetClientRect(&btnRT);
	if(btnRT.PtInRect(point)){return;}
	m_AssignButton.GetClientRect(&btnRT);
	if(btnRT.PtInRect(point)){return;}

	m_AllKill.ShowWindow(SW_HIDE);
	m_AssignButton.ShowWindow(SW_HIDE);

	
	CDialogEx::OnLButtonDown(nFlags, point);
}

//************************************
// 函数名:    TraverseFolder
// 描  述:    VirusScanner::TraverseFolder
// 权  限:    public 
// 返回值:    void
// 限定符:   
// 参  数:    LPCTSTR szName
// 参  数:    LPCTSTR filetype
//************************************
void VirusScanner::TraverseFolder(LPCTSTR szName,LPCTSTR filetype)
{
	WIN32_FIND_DATAW findFileData={0};
	TCHAR szFind[MAX_PATH] = {_T("\0")};
	CString pipei=filetype;//pipei 匹配O(∩_∩)O~
	BOOL bRet;
	CString fileRootPath = szName;
	CString filePath = fileRootPath+_T("\\*.*");
	HANDLE hwnd=FindFirstFile(filePath,&findFileData);
	if (hwnd==INVALID_HANDLE_VALUE)//没找到文件
	{
		MessageBox(_T("该文件路径不存在"),_T("错误"),NULL);
		return;
	}
	while (true)
	{
		if (_tcscmp(findFileData.cFileName,_T("."))==0||
			_tcscmp(findFileData.cFileName,_T(".."))==0 )
		{
			bRet=FindNextFile(hwnd,&findFileData);
			if (!bRet)
			{
				break;
			}
			continue;
		}
		CString path = fileRootPath+ _T("\\")+ findFileData.cFileName;
		int index = path.ReverseFind(_T('.'));
		CString pix  = path.Right(path.GetLength()-index);
		if (pipei.Find(pix)!=-1)
		{
			char *MD5="bacf0d5cec1d91f252b42c39d0bea5ca";//你认为的文件是病毒的MD5的值  

			CStringA ff(path);
			char * h = md5FileValue(ff.GetBuffer());
			if (strcmp(h,MD5)==0)
			{
				//DeleteFile(path);
				MessageBox(L"已查杀");
			}
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			_tcscpy_s(szFind,MAX_PATH,szName);
			_tcscat_s(szFind,_T("\\"));
			_tcscat_s(szFind,findFileData.cFileName);
			TraverseFolder(szFind,pipei);
		}
		bRet=FindNextFile(hwnd,&findFileData);
		if (bRet==0)
		{
			break;
		}

	}
}

void VirusScanner::MovebkPic(int BkgroundPic)
{
	m_BackgroundPic=BkgroundPic;
	CDC* pDC = GetDC();
	CRect rect;	
	GetClientRect(&rect);	//加载背景位图	
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(m_BackgroundPic); //图片ID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//选择位图	//创建内存DC	
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);
	//绘制位图	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式。

	for (int i = 30; i >=0; i = i--)
	{	
		pDC->StretchBlt(rect.Width()*i/30,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}


