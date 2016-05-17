// CleanSpace.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "CleanSpace.h"
#include "afxdialogex.h"
#include <wininet.h>
#include "UrlHist.h "
#pragma comment(lib,"Wininet.lib")

#define SWEEP_BUFFER_SIZE 10240
// CleanSpace �Ի���

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


// CleanSpace ��Ϣ�������


BOOL CleanSpace::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (!m_ClickFlag)
	{	
		//m_ImageButton1.ShowWindow(SW_SHOW);
		return TRUE;
	}
	CRect rect;	
	GetClientRect(&rect);	//���ر���λͼ	
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(m_BackgroundPic); //ͼƬID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
	CDC dc;	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//����λͼ	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
	dc.SelectObject(pOldBitmap);

	return TRUE;
}

//���ñ���ɫ
HBRUSH CleanSpace::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(0,0,0));     //������ɫ
		pDC-> SetBkMode(TRANSPARENT);       //���屳��ɫ   
		return (HBRUSH)::GetStockObject(NULL_BRUSH); // ���ñ���ɫ;
	}
	//if (nCtlColor==CTLCOLOR_BTN)
	//{
	//		/*pDC->SetTextColor(RGB(255,255,255));
	//		pDC->SetBkMode(RGB(255,255,255));*/
	//	COLORREF bkColor = RGB(239,239,239); //����ͼƬ����ɫֵ
	//	pDC->SetBkColor(bkColor);
	//	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	//}
	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������

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

//ȫ������ť
void CleanSpace::OnBnClickedButton1()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ClickFlag)
	{
		m_ImageButton1.ShowWindow(SW_HIDE);
		MovebkPic(IDB_BITMAP33);
		CleanInterface();		//�����������
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
	GetClientRect(&rect);	//���ر���λͼ	
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(m_BackgroundPic); //ͼƬID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);
	//����λͼ	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��

	for (int i = 30; i >=0; i = i--)
	{	
		pDC->StretchBlt(0,rect.Height()*i/30,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}

void CleanSpace::CleanInterface()
{
	//m_ImageButton1.MoveWindow(648,430,180,56);
//	m_ImageButton1.InitialImage(IDB_BITMAP34,IDB_BITMAP35,IDB_BITMAP36);
	m_ImageButton1.ShowWindow(SW_HIDE);
	WriteChar(30,0,0,0,50,30,L"��Ƶ��Ƶ����");
	WriteChar(30,0,0,0,50,90,L"ʹ�úۼ�");
	WriteChar(30,0,0,0,50,150,L"�����������");
	WriteChar(30,0,0,0,50,210,L"��������");
	WriteChar(30,0,0,0,50,270,L"�����������");
	WriteChar(30,0,0,0,50,330,L"ϵͳ����");
	WriteChar(30,0,0,0,50,390,L"������Ϸ����");
	Sleep(500);
	//��Ƶ��Ƶ���� ����
	WriteChar(20,0,0,0,750,30,L"����ɨ��...");
	Sleep(500);
	WriteChar(36,10,250,0,750,35,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);

	//���úۼ� ����
	WriteChar(20,0,0,0,750,90,L"����ɨ��...");
	CleanRASHistory();
	CleanRunHistory();
	CleanDocumentHistory();
	CleanPrevUserHistory();
	CleanNetContectHistory();
	CleanRemoteHistory();
	Sleep(500);
	WriteChar(36,10,250,0,750,95,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);

	//����������� ����
	WriteChar(20,0,0,0,750,150,L"����ɨ��...");
	CleanFileFindHistory();
	CleanCompFindHisroty();
	Sleep(500);
	WriteChar(36,10,250,0,750,155,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);

	//�������� ����
	WriteChar(20,0,0,0,750,210,L"����ɨ��...");
	CleanInternetCookie();
	CleanAddrBarHistory();
	CleanPasswordHistory();
	CleanFavoriteContent();
	CleanBrowseAddrHistory();
	Sleep(500);
	WriteChar(36,10,250,0,750,215,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);

	//����������� ����
	WriteChar(20,0,0,0,750,270,L"����ɨ��...");
	Sleep(500);
	WriteChar(36,10,250,0,750,275,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);

	//ϵͳ���� ����
	WriteChar(20,0,0,0,750,330,L"����ɨ��...");
	CleanInternetTemp();
	CleanSystemTemp();
	CleanRubbishStation();
	Sleep(500);
	WriteChar(36,10,250,0,750,335,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);
	//������Ϸ���� ����
	Sleep(500);
	WriteChar(20,0,0,0,750,390,L"����ɨ��...");
	WriteChar(36,10,250,0,750,395,L"���",TEXT("Arial"),ANTIALIASED_QUALITY);
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
	pDC->SetTextColor(RGB(0,0,0));     //������ɫ
	pDC->SetBkMode(TRANSPARENT);       //���屳��ɫ  

	pDC->TextOut(x,y,context,context.GetLength());
	//pDC->DrawText(L"����ɨ��",rect,DS_CENTER);

	pDC->SelectObject(po);//�ָ�֮ǰ���������
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
	{  //�õ���ʱĿ¼���������.
		EmptyDirectory(strPath);
	}
}
/**����Internet Cookie*/
VOID CleanSpace::CleanInternetCookie()
{
	CString strPath;	
	DeleteUrlCache(COOKIES);
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_COOKIES, FALSE);
	strPath.ReleaseBuffer();
	if(bSuccess)
	{//�õ�Ŀ¼�������
		EmptyDirectory(strPath);
	}
}
/**�����ַ����ʷ��¼*/
VOID CleanSpace::CleanAddrBarHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Internet Explorer\\TypedURLs"));
}



/**���������¼*/
VOID CleanSpace::CleanPasswordHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, 	TEXT("Software\\Microsoft\\Internet Explorer\\IntelliForms"));
}
/**�����ղؼ�����*/
VOID CleanSpace::CleanFavoriteContent()
{
	CString strPath;	   
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_FAVORITES, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{ //�õ�Ŀ¼������� 
		EmptyDirectory(strPath);
	}
}
/**����RAS��¼*/
VOID CleanSpace::CleanRASHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\RAS Autodial\\Addresses"));
}
/**����ϵͳ��ʱ�ļ���*/
VOID CleanSpace::CleanSystemTemp()
{
	CString strPath;										 
	BOOL bSuccess = GetTempPath(MAX_PATH, strPath.GetBuffer(MAX_PATH));

	strPath.ReleaseBuffer();
	if (bSuccess)//�õ�ϵͳ��ʱĿ¼
	{
		EmptyDirectory(strPath, TRUE);
	}
}

/**������������վ*/
VOID CleanSpace::CleanRubbishStation()
{
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}
/**�������м�¼*/
VOID CleanSpace::CleanRunHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU"));
}

/**�����ĵ���¼*/
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
/**�����ϴ��û���¼��¼*/
VOID CleanSpace::CleanPrevUserHistory()
{
	SHDeleteValue(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
		TEXT("DefaultUserName"));
	SHDeleteValue(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"), 
		TEXT("AltDefaultUserName"));
	SHDeleteValue(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon"), 
		TEXT("DefaultUserName"));
}
/**�����ļ����Ҽ�¼*/
VOID CleanSpace::CleanFileFindHistory()
{
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Doc Find Spec MRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ContainingTextMRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\FilesNamedMRU"));
}

/**������Ҽ������¼*/
VOID CleanSpace::CleanCompFindHisroty()
{
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FindComputerMRU"));
	SHDeleteKey(HKEY_CURRENT_USER, 
		TEXT("Software\\Microsoft\\Internet Explorer\\Explorer Bars\\{C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1}\\ComputerNameMRU"));
}
/**����������¼*/
VOID CleanSpace::CleanNetContectHistory()
{
	CString strPath;	   
	BOOL bSuccess = SHGetSpecialFolderPath(NULL, strPath.GetBuffer(MAX_PATH), CSIDL_NETHOOD, FALSE);
	strPath.ReleaseBuffer();
	if (bSuccess)
	{ //�õ�Ŀ¼�������
		EmptyDirectory(strPath);
	}
}
/**����Զ�����Ӽ�¼*/
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
/**���������ַ��¼*/
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
		return;				//û�ҵ���¼����
		/*hr = pUrlHistoryStg2->ClearHistory(); 
		pUrlHistoryStg2->Release();*/
		
	}

	//delete pUrlHistoryStg2;

	// ���������벻����
	// ��������ģ������������ܹ���.
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


///////////////////////////////���������� 

/**���Url����*/
BOOL CleanSpace::DeleteUrlCache(DEL_CACHE_TYPE type)
{
	BOOL bRet = FALSE;   //����ֵ
	HANDLE hEntry;
	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;  
	DWORD dwEntrySize;

	//delete the files
	dwEntrySize = 0;
	//���INTERNET_CACHE_ENTRY_INFO�Ĵ�С   
	hEntry = FindFirstUrlCacheEntry(NULL, NULL, &dwEntrySize);		//�˴���ȡ���ݴ�С������
	//������Ӧ��С�Ļ�����
	lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new TCHAR[dwEntrySize];
	//��ý���ڵľ��
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

/**���һ��Ŀ¼*/
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

		//ȥ��ֻ������
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
/**�����ļ�����*/
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










