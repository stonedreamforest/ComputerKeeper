// UninstallTool.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "UninstallTool.h"
#include "afxdialogex.h"
#include <vector>
#include "ListCtrl.h"
using namespace std;

// UninstallTool �Ի���

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


// UninstallTool ��Ϣ�������

typedef struct _SOFTINFO
{
	WCHAR szSoftName[MAX_PATH];		//�������
	WCHAR szSoftVer[MAX_PATH];		//����汾��
	WCHAR szSoftDate[MAX_PATH];		//�����װ����
	WCHAR szSoftInsPath[MAX_PATH];	//�����װ·��
	WCHAR szSoftUniPath[MAX_PATH];	//���ж��·��
	WCHAR szSoftVenrel[MAX_PATH];	//�����������
	WCHAR szSoftIco[MAX_PATH];		//���ͼ��·��
	WCHAR szURLInfo[MAX_PATH];		//��վ
	WCHAR HelpLink[MAX_PATH];		//��վ2
}SOFTINFO,*PSOFTINFO;

vector<SOFTINFO> m_VecSoftInfo;	//������������Ϣ

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	m_UniListCtrl.GetClientRect(rect);
	m_UniListCtrl.SetExtendedStyle(m_UniListCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|GWL_EXSTYLE);//��ѡ�з��
	CString str[] ={_T(""), _T("�������"), _T("�汾��"), _T("��װ����"), _T("��������")};
	for(int i=0; i<sizeof(str)/sizeof(str[0]); i++)
	{
		m_UniListCtrl.InsertColumn(i, str[i], LVCFMT_LEFT, 230);
	}
	m_UniListCtrl.DeleteColumn(0);//ɾ����0�� �������־���
	//m_Icon.Create(16,16, 1, 10, 4);
	//m_Icon.Add(AfxGetApp()->LoadIcon());
	UninstallIndex();
	m_UniListCtrl.SetLayeredWindowAttributes(RGB(0X80,0XC0,0XFF),255, LWA_COLORKEY);
	isInitEnd=true;

	
	return TRUE;  // return TRUE unless you set the focus to a control
}


void UninstallTool::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ m_UniListCtrl
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
	// TODO: �ڴ˴������Ϣ����������
}
//���������Ϣ
void UninstallTool::UninstallIndex()
{
	LONG nRet=RegOpenKeyEx(RootKey,lpSubKey,0,KEY_ENUMERATE_SUB_KEYS|KEY_QUERY_VALUE,&hkResult);
	if (nRet!=ERROR_SUCCESS)
	{
		return ;
	}
	DWORD dwIndex=0;
	//ѭ�������Ӽ�
	while (true)
	{

		DWORD dwKeyLen=MAX_KEY_LENGTH;
		//WCHAR szNewKeyName[MAX_PATH]={};
		TCHAR szNewKeyName[MAX_KEY_LENGTH] ;
		nRet=RegEnumKeyEx(hkResult,dwIndex,szNewKeyName,&dwKeyLen,NULL,NULL,NULL,NULL);
		if (nRet!=ERROR_SUCCESS)
		{
			break;		//�ɶϵ�����Ӧ����
		}
		//ͨ���õ����Ӽ�����µ��Ӽ�·��
		WCHAR strMidReg[MAX_PATH]={};
		swprintf_s(strMidReg,L"%s%s%s",lpSubKey,L"\\",szNewKeyName);
		//���µ��Ӽ���ȡ���
		HKEY hkValueKey=0;
		RegOpenKeyEx(RootKey,strMidReg,0,KEY_QUERY_VALUE,&hkValueKey);
		//��ȡ��ֵ
		DWORD dwNameLen=255;
		DWORD dwtype;
		RegQueryValueEx(hkValueKey,L"DisplayName",0,&dwtype,(LPBYTE)SoftInfo.szSoftName,&dwNameLen);//�����
		if(m_VecSoftInfo.size()>1)
		{
			if ((wcscmp(SoftInfo.szSoftName,m_VecSoftInfo[m_VecSoftInfo.size()-1].szSoftName)==0))
			{
				dwIndex++;
				continue;
			}
		}
		m_UniListCtrl.InsertItem(0,SoftInfo.szSoftName);
		dwNameLen=255;//���û�����¸�ֵ ��һ�ν���ȡ����·��
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"UninstallString",0,&dwtype,(LPBYTE)SoftInfo.szSoftUniPath,&dwNameLen);//ж��·��
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"DisplayIcon",0,&dwtype,(LPBYTE)SoftInfo.szSoftIco,&dwNameLen);//���·��
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"DisplayVersion",0,&dwtype,(LPBYTE)SoftInfo.szSoftVer,&dwNameLen);//�汾��
		m_UniListCtrl.SetItemText(0,1,SoftInfo.szSoftVer);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"Publisher",0,&dwtype,(LPBYTE)SoftInfo.szSoftVenrel,&dwNameLen);//��������
		m_UniListCtrl.SetItemText(0,3,SoftInfo.szSoftVenrel);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"InstallDate",0,&dwtype,(LPBYTE)SoftInfo.szSoftDate,&dwNameLen);//��װ����
		m_UniListCtrl.SetItemText(0,2,SoftInfo.szSoftDate);
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"URLInfoAbout",0,&dwtype,(LPBYTE)SoftInfo.szURLInfo,&dwNameLen);//��վ
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"HelpLink",0,&dwtype,(LPBYTE)SoftInfo.HelpLink,&dwNameLen);//��վ
		dwNameLen=255;
		dwtype=0;
		RegQueryValueEx(hkValueKey,L"InstallLocation",0,&dwtype,(LPBYTE)SoftInfo.szSoftInsPath,&dwNameLen);//��װ·��
		dwNameLen=255;
		dwIndex++;
		m_VecSoftInfo.push_back(SoftInfo);
	}
}


void UninstallTool::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	m_UniListCtrl.GetClientRect(&rect);//�ɵ����Χ  
	CPoint p;

	//GetPhysicalCursorPos(&p);//�������
	GetCursorPos(&p);
	rect.DeflateRect(0,23,0,0);
	m_UniListCtrl.ClientToScreen(rect);//������Ļ����
	if (rect.PtInRect(p))//�ж��Ƿ��ڿͻ���listctrl��Χ��
	{
		CMenu Menu;
		Menu.LoadMenuW(IDR_MENU2);//�˵���Դ
		CMenu *SubMenu=Menu.GetSubMenu(0);
		SubMenu->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON,p.x,p.y,this);
		//SubMenu->Detach();
		//Menu.DestroyMenu();//����
	}
}


void UninstallTool::Uninstall()
{
	// TODO: �ڴ���������������

	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
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
	// TODO: �ڴ���������������
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			_stprintf_s(http,_T("http://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=1&rsv_idx=1&ch=&tn=baiduerr&bar=&wd=%s&rn=&rsv_enter=1"),m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftName);
			ShellExecute(NULL,_T ("open"),http, NULL, NULL, SW_SHOWNORMAL);
		}
	}
}

//�ٷ���վ
void UninstallTool::OfficialWebsite()
{
	// TODO: �ڴ���������������
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
//	int n;
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
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


//���ļ�·��
void UninstallTool::OpenFilePath()
{
	// TODO: �ڴ���������������
	POSITION pos = m_UniListCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)//�ж��Ƿ�Ϊ��
	{
		return;
	}
	else
	{
		//�ɰ�ctrl+���ѡ�ж��н�������
		while (pos)
		{
			int nItem = m_UniListCtrl.GetNextSelectedItem(pos);
			CString NewfilePath(m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftUniPath);
			int index =NewfilePath.ReverseFind(_T('\\'));//�ض�EXE�ļ���
			NewfilePath = NewfilePath.Left(index);
			int Result=(int)ShellExecute(NULL,L"open",NewfilePath,NULL,NULL, SW_SHOW );
			//����ʧ��ʱ  ��һ�ַ�ʽ����
			if (Result<=32)//�ٷ��ĵ�˵������ֵ����32 ���Ǵ���  ���ҵ������������ Ҳ���Ҵ��� ���������δ�� �ļ����ܴ� 
			{
				ShellExecute(NULL,L"open",m_VecSoftInfo[m_VecSoftInfo.size()-(nItem+1)].szSoftInsPath,NULL,NULL, SW_SHOW );
			}
		}
	}
}

////���� ENTER ESC����Ӧ 
BOOL UninstallTool::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->wParam==VK_RETURN)
	{
		//Do anything what you want to
		return true;//����enter��Ϣ��Ӧ
	}
	if(pMsg->wParam == VK_ESCAPE)  
	{  
		return true;  //����esc��Ϣ��Ӧ
	}  
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH UninstallTool::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(255,0,0));     //������ɫ
		pDC-> SetBkMode(TRANSPARENT);       //���屳��ɫ   

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return (HBRUSH)::GetStockObject(NULL_BRUSH); // ���ñ���ɫ;
}


//BOOL UninstallTool::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	CRect rect;	
//	GetClientRect(&rect);	//���ر���λͼ	
//	CBitmap bmpBackground;
//	bmpBackground.LoadBitmap(IDB_BITMAP39); //ͼƬID	
//	BITMAP bitmap;   
//	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
//	CDC dc;	dc.CreateCompatibleDC(pDC);
//	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//����λͼ	
//	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��
//	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
//	dc.SelectObject(pOldBitmap);
//	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
//}
