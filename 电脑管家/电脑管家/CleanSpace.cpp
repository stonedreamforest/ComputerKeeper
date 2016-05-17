// CleanSpace.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "CleanSpace.h"
#include "afxdialogex.h"
#include <wininet.h>
#include "UrlHist.h "
#pragma comment(lib,"Wininet.lib")

#define SWEEP_BUFFER_SIZE 10240
// CleanSpace 对话框

IMPLEMENT_DYNAMIC(CleanSpace, CDialogEx)

CleanSpace::CleanSpace(CWnd* pParent /*=NULL*/)
	: CDialogEx(CleanSpace::IDD, pParent)
{
	m_ClickFlag=false;
}

CleanSpace::~CleanSpace()
{
}

void CleanSpace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, m_ImageButton);
	DDX_Control(pDX, IDC_BUTTON2, m_ImageButton1);
}


BEGIN_MESSAGE_MAP(CleanSpace, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CleanSpace::OnBnClickedButton1)
END_MESSAGE_MAP()


// CleanSpace 消息处理程序


BOOL CleanSpace::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (!m_ClickFlag)
	{	
		//m_ImageButton1.ShowWindow(SW_SHOW);
		return TRUE;
	}
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
}

//设置背景色
HBRUSH CleanSpace::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(0,0,0));     //字体颜色
		pDC-> SetBkMode(TRANSPARENT);       //字体背景色   
		return (HBRUSH)::GetStockObject(NULL_BRUSH); // 设置背景色;
	}
	//if (nCtlColor==CTLCOLOR_BTN)
	//{
	//		/*pDC->SetTextColor(RGB(255,255,255));
	//		pDC->SetBkMode(RGB(255,255,255));*/
	//	COLORREF bkColor = RGB(239,239,239); //背景图片的颜色值
	//	pDC->SetBkColor(bkColor);
	//	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	//}
	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

}


BOOL CleanSpace::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//m_ImageButton.SubclassDlgItem(IDC_BUTTON1,this);
	m_ImageButton1.MoveWindow(648,430,180,56);
	m_BackgroundPic=IDB_BITMAP1;
	m_ImageButton1.InitialImage(IDB_BITMAP3,IDB_BITMAP24,IDB_BITMAP25);
	m_ClickFlag=true;
	return TRUE;  // return TRUE unless you set the focus to a control
}

//全面清理按钮
void CleanSpace::OnBnClickedButton1()
{
	
	// TODO: 在此添加控件通知处理程序代码
	if (m_ClickFlag)
	{
		m_ImageButton1.ShowWindow(SW_HIDE);
		MovebkPic(IDB_BITMAP33);
		CleanInterface();		//正在清理界面
		m_ClickFlag=false;
	}
	if (!m_ClickFlag)
	{
		MovebkPic(IDB_BITMAP1);
		m_ImageButton1.MoveWindow(648,430,180,56);
		m_ImageButton1.InitialImage(IDB_BITMAP3,IDB_BITMAP24,IDB_BITMAP25);
		m_ClickFlag=true;
		m_ImageButton1.ShowWindow(SW_SHOW);
	}
	
}
void CleanSpace::MovebkPic(int BkgroundPic)
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
		pDC->StretchBlt(0,rect.Height()*i/30,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}

void CleanSpace::CleanInterface()
{
	//m_ImageButton1.MoveWindow(648,430,180,56);
//	m_ImageButton1.InitialImage(IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36);
	m_ImageButton1.ShowWindow(SW_HIDE);
	WriteChar(30,0,0,0,50,30,L"视频音频垃圾");
	WriteChar(30,0,0,0,50,90,L"使用痕迹");
	WriteChar(30,0,0,0,50,150,L"常用软件垃圾");
	WriteChar(30,0,0,0,50,210,L"上网垃圾");
	WriteChar(30,0,0,0,50,270,L"聊天软件垃圾");
	WriteChar(30,0,0,0,50,330,L"系统垃圾");
	WriteChar(30,0,0,0,50,390,L"网络游戏垃圾");
	Sleep(500);
	//视频音频垃圾 清理
	WriteChar(20,0,0,0,750,30,L"正在扫描...");
	Sleep(500);
	WriteChar(36,10,250,0,750,35,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);

	//试用痕迹 清理
	WriteChar(20,0,0,0,750,90,L"正在扫描...");
	CleanRASHistory();
	CleanRunHistory();
	CleanDocumentHistory();
	CleanPrevUserHistory();
	CleanNetContectHistory();
	CleanRemoteHistory();
	Sleep(500);
	WriteChar(36,10,250,0,750,95,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);

	//常用软件垃圾 清理
	WriteChar(20,0,0,0,750,150,L"正在扫描...");
	CleanFileFindHistory();
	CleanCompFindHisroty();
	Sleep(500);
	WriteChar(36,10,250,0,750,155,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);

	//上网垃圾 清理
	WriteChar(20,0,0,0,750,210,L"正在扫描...");
	CleanInternetCookie();
	CleanAddrBarHistory();
	CleanPasswordHistory();
	CleanFavoriteContent();
	CleanBrowseAddrHistory();
	Sleep(500);
	WriteChar(36,10,250,0,750,215,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);

	//聊天软件垃圾 清理
	WriteChar(20,0,0,0,750,270,L"正在扫描...");
	Sleep(500);
	WriteChar(36,10,250,0,750,275,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);

	//系统垃圾 清理
	WriteChar(20,0,0,0,750,330,L"正在扫描...");
	CleanInternetTemp();
	CleanSystemTemp();
	CleanRubbishStation();
	Sleep(500);
	WriteChar(36,10,250,0,750,335,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);
	//网络游戏垃圾 清理
	Sleep(500);
	WriteChar(20,0,0,0,750,390,L"正在扫描...");
	WriteChar(36,10,250,0,750,395,L"完成",TEXT("Arial"),ANTIALIASED_QUALITY);
}

void CleanSpace::WriteChar(int nHeight,int  nWidth, int nEscapement,int nOrientation,
						   int x,int y,CString context,CString fontStyle,BYTE FontQuality)
{

	CDC* pDC = GetDC();
	CFont m_font;
	m_font.CreateFont(nHeight,nWidth,nEscapement,nOrientation,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,FontQuality, VARIABLE_PITCH,fontStyle);
	//m_font.CreateFont(36,10,250,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
	//	CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));

	CFont *po = (CFont *)pDC->SelectObject(m_font);
	pDC->SetTextColor(RGB(0,0,0));     //字体颜色
	pDC->SetBkMode(TRANSPARENT);       //字体背景色  

	pDC->TextOut(x,y,context,context.GetLength());
	//pDC->DrawText(L"正在扫描",rect,DS_CENTER);

	pDC->SelectObject(po);//恢复之前的字体对像
	//pDC->DeleteTempMap()
	ReleaseDC(pDC);
}

VOID CleanSpace::CleanInternetTemp()
{
	CString strPath;;
	DeleteUrlCache(FILES);
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_INTERNET_CACHE, FALSE);   
	strPath.ReleaseBuffer();
	if(bSuccess)
	{  //得到临时目录，并清空它.
		EmptyDirectory(strPath);
	}
}
/**清理Internet Cookie*/
VOID CleanSpace::CleanInternetCookie()
{
	CString strPath;	
	DeleteUrlCache(COOKIES);
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_COOKIES, FALSE);
	strPath.ReleaseBuffer();
	if(bSuccess)
	{//得到目录，并清空
		EmptyDirectory(strPath);
	}
}
/**清理地址栏历史记录*/
VOID CleanSpace::CleanAddrBarHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Internet Explorer\\TypedURLs"));
}



/**清理密码记录*/
VOID CleanSpace::CleanPasswordHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, 	TEXT("Software\\Microsoft\\Internet Explorer\\IntelliForms"));
}
/**清理收藏夹内容*/
VOID CleanSpace::CleanFavoriteContent()
{
	CString strPath;	   
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_FAVORITES, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{ //得到目录，并清空 
		EmptyDirectory(strPath);
	}
}
/**清理RAS记录*/
VOID CleanSpace::CleanRASHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\RAS Autodial\\Addresses"));
}
/**清理系统临时文件夹*/
VOID CleanSpace::CleanSystemTemp()
{
	CString strPath;										 
	BOOL bSuccess = GetTempPath(MAX_PATH, strPath.GetBuffer(MAX_PATH));

	strPath.ReleaseBuffer();
	if (bSuccess)//得到系统临时目录
	{
		EmptyDirectory(strPath, TRUE);
	}
}

/**清理垃圾回收站*/
VOID CleanSpace::CleanRubbishStation()
{
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}
/**清理运行记录*/
VOID CleanSpace::CleanRunHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU"));
}

/**清理文档记录*/
VOID CleanSpace::CleanDocumentHistory()
{
	CString strPath;												   

	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_RECENT, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{
		EmptyDirectory(strPath);
	}

	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RecentDocs"));
}
/**清理上次用户登录记录*/
VOID CleanSpace::CleanPrevUserHistory()
{
	SHDeleteValue(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
		TEXT("DefaultUserName"));
	SHDeleteValue(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
		TEXT("AltDefaultUserName"));
	SHDeleteValue(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon"), 
		TEXT("DefaultUserName"));
}
/**清理文件查找记录*/
VOID CleanSpace::CleanFileFindHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Doc Find Spec MRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ContainingTextMRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\FilesNamedMRU"));
}

/**清理查找计算机记录*/
VOID CleanSpace::CleanCompFindHisroty()
{
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FindComputerMRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ComputerNameMRU"));
}
/**清理网联记录*/
VOID CleanSpace::CleanNetContectHistory()
{
	CString strPath;	   
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_NETHOOD, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{ //得到目录，并清空
		EmptyDirectory(strPath);
	}
}
/**清理远程连接记录*/
VOID CleanSpace::CleanRemoteHistory()
{
	CString sKey;
	for (int i=1; i<=8; i++)
	{
		sKey.Format(TEXT("Machine%d"), i);
		SHDeleteValue(HKEY_CURRENT_USER, 
			TEXT("Software\\Microsoft\\Telnet"), sKey);

		sKey.Format(TEXT("Service%d"), i);
		SHDeleteValue(HKEY_CURRENT_USER, 
			TEXT("Software\\Microsoft\\Telnet"), sKey);

		sKey.Format(TEXT("TermType%d"), i);
		SHDeleteValue(HKEY_CURRENT_USER, 
			TEXT("Software\\Microsoft\\Telnet"), sKey);
	}

	SHDeleteValue(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Telnet"), TEXT("LastMachine"));
	SHDeleteValue(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Telnet"), TEXT("LastService"));
	SHDeleteValue(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Telnet"), TEXT("LastTermType"));
}
/**清理浏览网址记录*/
VOID CleanSpace::CleanBrowseAddrHistory()
{
	HRESULT hr;
	CString strPath;	
	IUrlHistoryStg2* pUrlHistoryStg2 = NULL;
	hr = CoCreateInstance(CLSID_CUrlHistory, NULL, 
		CLSCTX_INPROC_SERVER, IID_IUrlHistoryStg2, 
		(VOID**)&pUrlHistoryStg2);
	if (SUCCEEDED(hr))
	{
		return;				//没找到记录返回
		/*hr = pUrlHistoryStg2->ClearHistory(); 
		pUrlHistoryStg2->Release();*/
		
	}

	//delete pUrlHistoryStg2;

	// 如果上面代码不能清
	// 则有下面的，不完美，但能工作.
	GetWindowsDirectory(strPath.GetBuffer(MAX_PATH), MAX_PATH);
	strPath.ReleaseBuffer();
	strPath += TEXT("\\History");
	EmptyDirectory(strPath, FALSE, TRUE);

	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_HISTORY, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{
		EmptyDirectory(strPath, FALSE, TRUE);
	}
}


///////////////////////////////辅助清理函数 

/**清除Url缓存*/
BOOL CleanSpace::DeleteUrlCache(DEL_CACHE_TYPE type)
{
	BOOL bRet = FALSE;   //返回值
	HANDLE hEntry;
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
	DWORD dwEntrySize;

	//delete the files
	dwEntrySize = 0;
	//获得INTERNET_CACHE_ENTRY_INFO的大小   
	hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);		//此处获取数据大小有问题
	//分配响应大小的缓冲区
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
	//获得进入口的句柄
	hEntry = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwEntrySize);

	if (hEntry)
	{
		do
		{
			if (type == FILES &&
				!(lpCacheEntry -> CacheEntryType & COOKIE_CACHE_ENTRY))
			{
				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
			}
			else if (type == COOKIES &&
				(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
			{
				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
			}
			dwEntrySize = 0;
			FindNextUrlCacheEntry(hEntry, NULL, &dwEntrySize);
			delete [] lpCacheEntry; 
			lpCacheEntry = NULL;
			lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
		}
		while (FindNextUrlCacheEntry(hEntry, lpCacheEntry, &dwEntrySize));

		bRet = TRUE;
	}

	if (lpCacheEntry)
	{
		delete [] lpCacheEntry;
		lpCacheEntry = NULL;
	}
	return bRet;
}

/**清空一个目录*/
BOOL CleanSpace::EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni /*= FALSE*/, 
								BOOL bWipeIndexDat /*= FALSE*/)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	CString sFullPath;
	CString sFindFilter;
	DWORD dwAttributes = 0;

	sFindFilter = szPath;
	sFindFilter += TEXT("\\*.*");
	if ((hFind = FindFirstFile(sFindFilter, &wfd)) == INVALID_HANDLE_VALUE)
		return FALSE;

	do
	{
		if (_tcscmp(wfd.cFileName, TEXT(".")) == 0 || 
			_tcscmp(wfd.cFileName, TEXT("..")) == 0 ||
			(bDeleteDesktopIni == FALSE && _tcsicmp(wfd.cFileName, TEXT("desktop.ini")) == 0))
		{
			continue;
		}

		sFullPath = szPath;
		sFullPath += TEXT("\\");
		sFullPath += wfd.cFileName;

		//去掉只读属性
		dwAttributes = GetFileAttributes(sFullPath);
		if (dwAttributes & FILE_ATTRIBUTE_READONLY)
		{
			dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes(sFullPath, dwAttributes);
		}

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			EmptyDirectory(sFullPath, bDeleteDesktopIni, bWipeIndexDat);
			RemoveDirectory(sFullPath);
		}
		else
		{
			if (bWipeIndexDat && _tcsicmp(wfd.cFileName, TEXT("index.dat")) == 0)
			{
				WipeFile(szPath, wfd.cFileName);
			}
			DeleteFile(sFullPath);
		}
	}
	while (FindNextFile(hFind, &wfd));
	FindClose(hFind);

	return TRUE;
}
/**擦除文件内容*/
BOOL CleanSpace::WipeFile(LPCTSTR szDir, LPCTSTR szFile)
{
	CString sPath;
	HANDLE	hFile;
	DWORD	dwSize;
	DWORD	dwWrite;
	TCHAR	sZero[SWEEP_BUFFER_SIZE];
	memset(sZero, 0, SWEEP_BUFFER_SIZE);

	sPath = szDir;
	sPath += TEXT("\\");
	sPath += szFile;

	hFile = CreateFile(sPath, GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSize = GetFileSize(hFile, NULL);

	//skip file header (actually, I don't know the file format of index.dat)
	dwSize -= 64;
	SetFilePointer(hFile, 64, NULL, FILE_BEGIN);

	while (dwSize > 0)
	{
		if (dwSize > SWEEP_BUFFER_SIZE)
		{
			WriteFile(hFile, sZero, SWEEP_BUFFER_SIZE, &dwWrite, NULL);
			dwSize -= SWEEP_BUFFER_SIZE;
		}
		else
		{
			WriteFile(hFile, sZero, dwSize, &dwWrite, NULL);
			break;
		}
	}

	CloseHandle(hFile);
	return TRUE;
}










