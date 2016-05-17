// StartupManager.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "StartupManager.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

//HKEY RootKey=HKEY_LOCAL_MACHINE;	//����
#define MAX_KEY_LENGTH 1024
#define MAX_VALUE_NAME 16383 

typedef struct _STARTINFO
{
	TCHAR szNewKeyName[MAX_KEY_LENGTH];
	TCHAR szNewValueName[MAX_KEY_LENGTH];

}STARTINFO,*PSTARTINFO;

vector<STARTINFO> m_VecStartupInfo;	//������������Ϣ
// StartupManager �Ի���


 
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


// StartupManager ��Ϣ�������


BOOL StartupManager::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
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

	// �쳣: OCX ����ҳӦ���� FALSE
}


void StartupManager::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_ButtonState)
	{
		m_StartupButton.ShowWindow(SW_HIDE);
		m_BackgroundPic=IDB_BITMAP47;	
		MovebkPic(m_BackgroundPic);
	}	
	m_StartupListCtrl.SetExtendedStyle(m_StartupListCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|GWL_EXSTYLE);//��ѡ�з��
	CString str[] ={_T("1")};
	CRect rect;
	GetClientRect(rect);
	for(int i=0; i<sizeof(str)/sizeof(str[0]); i++)
	{

		m_StartupListCtrl.InsertColumn(i, str[i], LVCFMT_LEFT, rect.right);
	}
	m_StartupListCtrl.SetItemHeight(100);		//�����и�
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
		//�˴������������ɫ   
		pDC->SetTextColor(RGB(0,0,0));   
		return (HBRUSH)::GetStockObject(NULL_BRUSH); // ���ñ���ɫ;
	}   
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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

	// TODO: �ڴ˴������Ϣ����������

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
	//ѭ�������Ӽ�
	while (true)
	{
		
		DWORD dwKeyLen=MAX_KEY_LENGTH;

		nRet=RegEnumValue(hkStartupResult,dwIndex,info.szNewKeyName,&dwKeyLen,NULL,NULL,(PBYTE)info.szNewValueName,&dwKeyLen);
		if (nRet!=ERROR_SUCCESS)
		{
			break;		//�ɶϵ�����Ӧ����
		}
		TCHAR SynthesisStr[2048];		//�ϳ��ַ���
		_stprintf_s(SynthesisStr,_T("[%s]%s"),info.szNewKeyName,info.szNewValueName);
		m_StartupListCtrl.InsertItem(dwIndex,SynthesisStr);
		m_StartupListCtrl.createItemButton(dwIndex, 
											2,		//�����ť���ڵڶ����������ֵ  δ��
											this->GetSafeHwnd() );		//������ť
		dwIndex++;
		m_VecStartupInfo.push_back(info);		
	}
	RegCloseKey(hkStartupResult);

}

//���LISR�ؼ���ť��Ӧ�¼�
LRESULT StartupManager::onBnCLick(WPARAM wParam, LPARAM lParam)
{
	int nItem = (int)wParam;		//��ȡ�ڼ���
	int nSubItem = (int)lParam;		//��ȡ�ڼ���
	nSubItem--;						//createItemButton()  �ڶ������� ��ûʲô��  ���Բ���
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
	iter->second->SetWindowText(L"�ѽ�ֹ");
	return 0;
}





//************************************
// ������:    AddRun
// ��  ��:    StartupManager::AddRun
// Ȩ  ��:    public 
// ����ֵ:    BOOL
// �޶���:   
// ��  ��:    CString cRunName
// ��  ��:    CString cRunPath
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
/* �������ƣ�DeleteRun
   �������ܣ�ɾ��������
   ˵��    ��
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
		pDC->StretchBlt(rect.Width()*i/30,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}



//���ذ�ť
void StartupManager::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
