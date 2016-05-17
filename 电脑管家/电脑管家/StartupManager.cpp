// StartupManager.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "StartupManager.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

//HKEY RootKey=HKEY_LOCAL_MACHINE;	//主键
#define MAX_KEY_LENGTH 1024
#define MAX_VALUE_NAME 16383 

typedef struct _STARTINFO
{
	TCHAR szNewKeyName[MAX_KEY_LENGTH];
	TCHAR szNewValueName[MAX_KEY_LENGTH];

}STARTINFO,*PSTARTINFO;

vector<STARTINFO> m_VecStartupInfo;	//保存软件相关信息
// StartupManager 对话框


 
LPCTSTR lpStartupSubKey=L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run";
//Software\\Microsoft\\Windows\\CurrentVersion\\Run
//SOFTWARE\\Wow6432Node\\Microsofe\\Windows\\CurrentVersion\\Uninstall"
HKEY hkStartupResult;

IMPLEMENT_DYNAMIC(StartupManager, CDialogEx)

StartupManager::StartupManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(StartupManager::IDD, pParent)
{
	isInitEnd=FALSE;
	m_ButtonState=FALSE;
}

StartupManager::~StartupManager()
{
}

void StartupManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_StartupButton);
	//	DDX_Control(pDX, IDC_LIST2, m_StartupListBox);
	DDX_Control(pDX, IDC_LIST1, m_StartupListCtrl);
	DDX_Control(pDX, IDC_BUTTON2, m_BackButton);
}


BEGIN_MESSAGE_MAP(StartupManager, CDialogEx)
//	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &StartupManager::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
//	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_MESSAGE( WM_BN_CLICK, onBnCLick)
	ON_BN_CLICKED(IDC_BUTTON2, &StartupManager::OnBnClickedButton2)
END_MESSAGE_MAP()


// StartupManager 消息处理程序


BOOL StartupManager::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CRect rect;	
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
	//return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL StartupManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_BackgroundPic=IDB_BITMAP6;
	m_StartupButton.MoveWindow(40,40,180,54);
	m_StartupButton.InitialImage(IDB_BITMAP9,IDB_BITMAP22,IDB_BITMAP23);
	m_ButtonState=true;
//	m_hbrush=CreateSolidBrush(NULL_BRUSH);
	//m_StartupListCtrl.getwindow
//	m_StartupListCtrl.SetWindowLong(GWL_EXSTYLE,\
//		GetWindowLong(GWL_EXSTYLE)^0x80000);
	
	//initListBox();
//	DeleteRun(0);
	//m_StartupListBox.
	isInitEnd=TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


void StartupManager::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_ButtonState)
	{
		m_StartupButton.ShowWindow(SW_HIDE);
		m_BackgroundPic=IDB_BITMAP47;	
		MovebkPic(m_BackgroundPic);
	}	
	m_StartupListCtrl.SetExtendedStyle(m_StartupListCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|GWL_EXSTYLE);//可选中风格
	CString str[] ={_T("1")};
	CRect rect;
	GetClientRect(rect);
	for(int i=0; i<sizeof(str)/sizeof(str[0]); i++)
	{

		m_StartupListCtrl.InsertColumn(i, str[i], LVCFMT_LEFT, rect.right);
	}
	m_StartupListCtrl.SetItemHeight(100);		//设置行高
	initListBox();
	m_StartupListCtrl.ShowWindow(SW_SHOW);
	//m_BackButton.MoveWindow(200,200,180,55);
	//m_BackButton.ShowWindow(SW_SHOW);
	//m_BackButton.InitialImage(IDB_BITMAP48,IDB_BITMAP49,IDB_BITMAP50);
}


HBRUSH StartupManager::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==   CTLCOLOR_LISTBOX)   
	{   
		pDC->SetBkMode(TRANSPARENT);   
		//此处设置字体的颜色   
		pDC->SetTextColor(RGB(0,0,0));   
		return (HBRUSH)::GetStockObject(NULL_BRUSH); // 设置背景色;
	}   
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void StartupManager::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(!isInitEnd){
		return;
	}
	CRect rc ;
	GetClientRect(&rc);
	rc.DeflateRect(10,0,10,0);
	m_StartupListCtrl.MoveWindow(rc,TRUE) ;

	// TODO: 在此处添加消息处理程序代码

}
STARTINFO info;
void StartupManager::initListBox()
{
	LONG nRet=RegOpenKeyEx(RootKey,lpStartupSubKey,0,KEY_ENUMERATE_SUB_KEYS|KEY_QUERY_VALUE,&hkStartupResult);
	if (nRet!=ERROR_SUCCESS)
	{
		return ;
	}

	DWORD dwIndex=0;
	//循环遍历子键
	while (true)
	{
		
		DWORD dwKeyLen=MAX_KEY_LENGTH;

		nRet=RegEnumValue(hkStartupResult,dwIndex,info.szNewKeyName,&dwKeyLen,NULL,NULL,(PBYTE)info.szNewValueName,&dwKeyLen);
		if (nRet!=ERROR_SUCCESS)
		{
			break;		//可断点检查相应错误
		}
		TCHAR SynthesisStr[2048];		//合成字符串
		_stprintf_s(SynthesisStr,_T("[%s]%s"),info.szNewKeyName,info.szNewValueName);
		m_StartupListCtrl.InsertItem(dwIndex,SynthesisStr);
		m_StartupListCtrl.createItemButton(dwIndex, 
											2,		//点击按钮（在第二例）处理的值  未做
											this->GetSafeHwnd() );		//创建按钮
		dwIndex++;
		m_VecStartupInfo.push_back(info);		
	}
	RegCloseKey(hkStartupResult);

}

//点击LISR控件按钮响应事件
LRESULT StartupManager::onBnCLick(WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;		//获取第几行
	int nSubItem = (int)lParam;		//获取第几列
	nSubItem--;						//createItemButton()  第二个参数 并没什么用  测试参数
// #ifdef USE_TOPINDEX_BUTTON
// 	int iTopIndex = m_StartupListCtrl.GetTopIndex();
// 	nItem = iTopIndex + nItem;
// #endif

//  	CString szItemText = m_StartupListCtrl.GetItemText( nItem, nSubItem );
//  	int iValue = _wtoi( szItemText );
//  	iValue --;
//  	if( iValue == 0)
//  	{
//  	//	m_StartupListCtrl.deleteItemEx( nItem );
//  	}
//  	else
//  	{
//  		szItemText.Format( _T("%d"),iValue );
//  		m_StartupListCtrl.SetItemText( nItem, nSubItem, szItemText );
//  	}
 	
	DeleteRun(nItem);
	button_map::iterator iter;
	iter = m_StartupListCtrl.m_mButton.find( nItem );
	iter->second->SetWindowText(L"已禁止");
	return 0;
}





//************************************
// 函数名:    AddRun
// 描  述:    StartupManager::AddRun
// 权  限:    public 
// 返回值:    BOOL
// 限定符:   
// 参  数:    CString cRunName
// 参  数:    CString cRunPath
//************************************
BOOL StartupManager::AddRun( CString cRunName,CString cRunPath )
{
	HKEY hSubKey;
	HKEY RootKey=HKEY_LOCAL_MACHINE;
	LPCTSTR lpSubKey=_T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run\\");
	long lReturn=RegOpenKeyEx(RootKey,lpSubKey,0,KEY_WRITE,&hSubKey);
	if (lReturn==ERROR_SUCCESS)
	{
		CString fullNamePath;
		fullNamePath.Format(_T("\"%s\""), cRunPath);
		RegSetValueEx(hSubKey,cRunName,0,REG_SZ,(const unsigned char *)(LPCTSTR)fullNamePath,fullNamePath.GetLength());

		RegCloseKey(hSubKey);
	}
	return TRUE;
}

/************************************************************************/
/* 函数名称：DeleteRun
   函数功能：删除启动项
   说明    ：
/************************************************************************/
BOOL StartupManager::DeleteRun( int  nIndex )
{
	//RegDeleteValue(hSubKey,g_RunInfo.szNewKeyName);
	HKEY hSubKey;
	HKEY RootKey=HKEY_LOCAL_MACHINE;
	LPCTSTR lpSubKey=_T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run\\");
	long lReturn=RegOpenKeyEx(RootKey,lpSubKey,0,KEY_WRITE,&hSubKey);
	if (lReturn==ERROR_SUCCESS)
	{
		RegDeleteValue(hSubKey,m_VecStartupInfo[nIndex].szNewKeyName);
		RegCloseKey(hSubKey);
	}
	
	return TRUE;
}

void StartupManager::MovebkPic(int BkgroundPic)
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



//返回按钮
void StartupManager::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

}
