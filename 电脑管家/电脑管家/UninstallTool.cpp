// UninstallTool.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "UninstallTool.h"
#include "afxdialogex.h"
#include <vector>
#include "ListCtrl.h"
using namespace std;

// UninstallTool 对话框

IMPLEMENT_DYNAMIC(UninstallTool, CDialogEx)

UninstallTool::UninstallTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(UninstallTool::IDD, pParent)
{
	isInitEnd=false;
}

UninstallTool::~UninstallTool()
{
}

void UninstallTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_UniListCtrl);
}


BEGIN_MESSAGE_MAP(UninstallTool, CDialogEx)
	ON_WM_DRAWITEM()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID__32773, &UninstallTool::Uninstall)
	ON_COMMAND(ID__32774, &UninstallTool::SearchInfo)
	ON_COMMAND(ID__32775, &UninstallTool::OfficialWebsite)
	ON_COMMAND(ID__32776, &UninstallTool::OpenFilePath)
	ON_WM_CTLCOLOR()
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// UninstallTool 消息处理程序

typedef struct _SOFTINFO
{
	WCHAR szSoftName[MAX_PATH];		//软件名称
	WCHAR szSoftVer[MAX_PATH];		//软件版本号
	WCHAR szSoftDate[MAX_PATH];		//软件安装日期
	WCHAR szSoftInsPath[MAX_PATH];	//软件安装路径
	WCHAR szSoftUniPath[MAX_PATH];	//软件卸载路径
	WCHAR szSoftVenrel[MAX_PATH];	//软件发布厂商
	WCHAR szSoftIco[MAX_PATH];		//软件图标路径
	WCHAR szURLInfo[MAX_PATH];		//网站
	WCHAR HelpLink[MAX_PATH];		//网站2
}SOFTINFO,*PSOFTINFO;

vector<SOFTINFO> m_VecSoftInfo;	//保存软件相关信息

#define MAX_KEY_LENGTH 1024
#define MAX_VALUE_NAME 16383  
LPCTSTR lpSubKey=L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
//Software\\Microsoft\\Windows\\CurrentVersion\\Run
//SOFTWARE\\Wow6432Node\\Microsofe\\Windows\\CurrentVersion\\Uninstall"
HKEY hkResult;
SOFTINFO SoftInfo;

BOOL UninstallTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CRect rect;
	m_UniListCtrl.GetClientRect(rect);
	m_UniListCtrl.SetExtendedStyle(m_UniListCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|GWL_EXSTYLE);//可选中风格
	CString str[] ={_T(""), _T("软件名称"), _T("版本号"), _T("安装日期"), _T("发布厂商")};
	for(int i=0; i<sizeof(str)/sizeof(str[0]); i++)
	{
		m_UniListCtrl.InsertColumn(i, str[i], LVCFMT_LEFT, 230);
	}
	m_UniListCtrl.DeleteColumn(0);//删除第0列 用以文字居中
	//m_Icon.Create(16,16, 1, 10, 4);
	//m_Icon.Add(AfxGetApp()->LoadIcon());
	UninstallIndex();
	m_UniListCtrl.SetLayeredWindowAttributes(RGB(0X80,0XC0,0XFF),255, LWA_COLORKEY);
	isInitEnd=true;

	
	return TRUE;  // return TRUE unless you set the focus to a control
}


void UninstallTool::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值 m_UniListCtrl
	if(nIDCtl==IDC_LIST1)
	{
		m_UniListCtrl.DrawItem(lpDrawItemStruct);
	}		
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void UninstallTool::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(!isInitEnd){
		return;
	}
	CRect rc ;
	GetClientRect(&rc);
	rc.DeflateRect(10,0,8,0);
	m_UniListCtrl.MoveWindow(rc,FALSE) ;
	// TODO: 在此处添加消息处理程序代码
}
//加载软件信息
void UninstallTool::UninstallIndex()
{
	LONG nRet=RegOpenKeyEx(RootKey,lpSubKey,0,KEY_ENUMERATE_SUB_KEYS|KEY_QUERY_VALUE,&hkResult);
	if (nRet!=ERROR_SUCCESS)
	{
		return ;
	}
	DWORD dwIndex=0;
	//循环遍历子键
	while (true)
	{

		DWORD dwKeyLen=MAX_KEY_LENGTH;
		//WCHAR szNewKeyName[MAX_PATH]={};
		TCHAR szNewKeyName[MAX_KEY_LENGTH] ;
		nRet=RegEnumKeyEx(hkResult,dwIndex,szNewKeyName,&dwKeyLen,NULL,NULL,NULL,NULL);
		if (nRet!=ERROR_SUCCESS)
		{
			break;		//可断点检查相应错误
		}
		//通过得到的子键组合新的子键路径
		WCHAR strMidReg[MAX_PATH]={};
		swprintf_s(strMidReg,L"%s%s%s",lpSubKey,L"\\",szNewKeyName);
		//打开新的子键获取句柄
		HKEY hkValueKey=0;
		RegOpenKeyEx(RootKey,strMidReg,0,KEY_QUERY_VALUE,&hkValueKey);
		//获取键值
		DWORD dwNameLen=255;
		DWORD dwtype;
		RegQueryValueEx(hkValueKey,L"DisplayName",0,&dwtype,(LPBYTE)SoftInfo.szSoftName,&dwNameLen);//软件名
		if(m_VecSoftInfo.size()>1)
		{
			if ((wcscmp(SoftInfo.szSoftName,m_VecSoftInfo[m_VecSoftInfo.size()-1].szSoftName)==0))
			{
				dwIndex++;
				continue;
			}
		}
		m_UniListCtrl.InsertItem(0,SoftInfo.szSoftName);
		dwNameLen=255;//如果没有重新赋值 下一次将获取不到路径
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"UninstallString",0,&dwtype,(LPBYTE)SoftInfo.szSoftUniPath,&dwNameLen);//卸载路径
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"DisplayIcon",0,&dwtype,(LPBYTE)SoftInfo.szSoftIco,&dwNameLen);//光标路径
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"DisplayVersion",0,&dwtype,(LPBYTE)SoftInfo.szSoftVer,&dwNameLen);//版本号
		m_UniListCtrl.SetItemText(0,1,SoftInfo.szSoftVer);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"Publisher",0,&dwtype,(LPBYTE)SoftInfo.szSoftVenrel,&dwNameLen);//发布厂商
		m_UniListCtrl.SetItemText(0,3,SoftInfo.szSoftVenrel);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"InstallDate",0,&dwtype,(LPBYTE)SoftInfo.szSoftDate,&dwNameLen);//安装日期
		m_UniListCtrl.SetItemText(0,2,SoftInfo.szSoftDate);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"URLInfoAbout",0,&dwtype,(LPBYTE)SoftInfo.szURLInfo,&dwNameLen);//网站
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"HelpLink",0,&dwtype,(LPBYTE)SoftInfo.HelpLink,&dwNameLen);//网站
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"InstallLocation",0,&dwtype,(LPBYTE)SoftInfo.szSoftInsPath,&dwNameLen);//安装路径
		dwNameLen=255;
		dwIndex++;
		m_VecSoftInfo.push_back(SoftInfo);
	}
}


void UninstallTool::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	m_UniListCtrl.GetClientRect(&rect);//可点击范围  
	CPoint p;

	//GetPhysicalCursorPos(&p);//鼠标坐标
	GetCursorPos(&p);
	rect.DeflateRect(0,23,0,0);
	m_UniListCtrl.ClientToScreen(rect);//基于屏幕坐标
	if (rect.PtInRect(p))//判断是否在客户区listctrl范围内
	{
		CMenu Menu;
		Menu.LoadMenuW(IDR_MENU2);//菜单资源
		CMenu *SubMenu=Menu.GetSubMenu(0);
		SubMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON,p.x,p.y,this);
		//SubMenu->Detach();
		//Menu.DestroyMenu();//销毁
	}
}


void UninstallTool::Uninstall()
{
	// TODO: 在此添加命令处理程序代码

	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	else
	{
		//可按ctrl+左键选中多行结束进程
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			ShellExecute(NULL,L"open",m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftUniPath,NULL,NULL, SW_SHOW ); 
		}
	}
}

TCHAR http[MAX_PATH];
void UninstallTool::SearchInfo()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	else
	{
		//可按ctrl+左键选中多行结束进程
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			_stprintf_s(http,_T("http://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&ch=&tn=baiduerr&bar=&wd=%s&rn=&rsv_enter=1"),m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftName);
			ShellExecute(NULL,_T ("open"),http, NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

//官方网站
void UninstallTool::OfficialWebsite()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
//	int n;
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	else
	{
		//可按ctrl+左键选中多行结束进程
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			if (!wcscmp(m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szURLInfo,L""))
				//m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szURLInfo[0]=='\0\0')
			{
				if (!wcscmp(m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].HelpLink,L""))
				{
					_stprintf_s(http,_T("http://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&ch=&tn=baiduerr&bar=&wd=%s&rn=&rsv_enter=1"),
						m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftName);
					ShellExecute(NULL,_T ("open"),http, NULL, NULL, SW_SHOWNORMAL);					
				}		
				ShellExecute(NULL,L"open",m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].HelpLink,NULL,NULL, SW_SHOW ); 
			}
			else 
			{			
				ShellExecute(NULL,L"open",m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szURLInfo,NULL,NULL, SW_SHOW ); 
			}			
		}
	}
}


//打开文件路径
void UninstallTool::OpenFilePath()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	else
	{
		//可按ctrl+左键选中多行结束进程
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			CString NewfilePath(m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftUniPath);
			int index =NewfilePath.ReverseFind(_T('\\'));//截断EXE文件名
			NewfilePath = NewfilePath.Left(index);
			int Result=(int)ShellExecute(NULL,L"open",NewfilePath,NULL,NULL, SW_SHOW );
			//调用失败时  另一种方式调用
			if (Result<=32)//官方文档说明返回值大于32 便是错误  但我单步调并非如此 也许我错了 但在这儿并未错 文件夹能打开 
			{
				ShellExecute(NULL,L"open",m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftInsPath,NULL,NULL, SW_SHOW );
			}
		}
	}
}

////阻塞 ENTER ESC键响应 
BOOL UninstallTool::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->wParam==VK_RETURN)
	{
		//Do anything what you want to
		return true;//阻塞enter消息响应
	}
	if(pMsg->wParam == VK_ESCAPE)  
	{  
		return true;  //阻塞esc消息响应
	}  
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH UninstallTool::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(255,0,0));     //字体颜色
		pDC-> SetBkMode(TRANSPARENT);       //字体背景色   

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return (HBRUSH)::GetStockObject(NULL_BRUSH); // 设置背景色;
}


//BOOL UninstallTool::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CRect rect;	
//	GetClientRect(&rect);	//加载背景位图	
//	CBitmap bmpBackground;
//	bmpBackground.LoadBitmap(IDB_BITMAP39); //图片ID	
//	BITMAP bitmap;   
//	bmpBackground.GetBitmap(&bitmap); 	//选择位图	//创建内存DC	
//	CDC dc;	dc.CreateCompatibleDC(pDC);
//	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//绘制位图	
//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式。
//	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
//	dc.SelectObject(pOldBitmap);
//	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
//}
