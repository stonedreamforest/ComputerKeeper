// MemoryOptimizer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "MemoryOptimizer.h"
#include "afxdialogex.h"
#include <Psapi.h>


// MemoryOptimizer �Ի���

IMPLEMENT_DYNAMIC(MemoryOptimizer, CDialogEx)

MemoryOptimizer::MemoryOptimizer(CWnd* pParent /*=NULL*/)
	: CDialogEx(MemoryOptimizer::IDD, pParent)
{
	m_Time=false;
	m_ButtonState=false;
}

MemoryOptimizer::~MemoryOptimizer()
{
}

void MemoryOptimizer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_MemoryButton);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_CartoonPlay);
}


BEGIN_MESSAGE_MAP(MemoryOptimizer, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &MemoryOptimizer::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &MemoryOptimizer::OnBnClickedButton2)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// MemoryOptimizer ��Ϣ�������


BOOL MemoryOptimizer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ  
	/*if (!m_ButtonState)
	{
		return true;
	}*/
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
	return CDialogEx::OnEraseBkgnd(pDC);
}


void MemoryOptimizer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


BOOL MemoryOptimizer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_MemoryButton.MoveWindow(100,100,180,55);
	m_MemoryButton.InitialImage(IDB_BITMAP51,IDB_BITMAP52,IDB_BITMAP53);
	m_BackgroundPic=IDB_BITMAP37;
	m_Time=true;
	m_ButtonState=true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MemoryOptimizer::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�ͻ��˴���  
	m_MemoryButton.ShowWindow(SW_HIDE);
	ClenMemory();
	if (m_ButtonState)
	{
		SetTimer(1,100,NULL);
		m_BackgroundPic=IDB_BITMAP46;//����ͼƬ
		MovebkPic(m_BackgroundPic);
		m_ButtonState=false;
		RECT rc;
		this->GetClientRect(&rc);  
		// ����λ��  
		m_CartoonPlay.MoveWindow(&rc, true);  
		CString fileName ;

		TCHAR path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,path);
		fileName.Format(L"%s\\flash3038.swf",path);

		// flash�ļ���  
		// ����flash�ļ�  
		m_CartoonPlay.LoadMovie(0, fileName);  
		// ����  
		m_CartoonPlay.ShowWindow(SW_SHOW);
		m_CartoonPlay.Play(); 
	}
	if (!m_MemoryButton)
	{
		m_BackgroundPic=IDB_BITMAP54;//����ͼƬ
		MovebkPic(m_BackgroundPic);
		m_ButtonState=true;
	}

//	Sleep(1000);
	//m_CartoonPlay.ShowWindow(SW_HIDE);
	
	
}



void MemoryOptimizer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_Time=false;
	CRect wndCt;
	GetClientRect(&wndCt);
	CRect ct;
	m_CartoonPlay.GetClientRect(&ct);
	
	if (!ct.Width() || !ct.Height())
	{
		KillTimer(1);
		m_CartoonPlay.StopPlay();
		m_CartoonPlay.ShowWindow(SW_HIDE);
		//SetWindowText(hd);
		CString xianshi;
		xianshi=L"Ŀǰ�ڴ�ʹ�ã�"+hh+L"G"+L"�������ڴ�"+hd+L"MB";
		WriteChar(25,0,0,0,240,165,xianshi);
		Sleep(2000);
		m_BackgroundPic=IDB_BITMAP37;
		MovebkPic(m_BackgroundPic);
		m_MemoryButton.ShowWindow(SW_SHOW);
		m_CartoonPlay.MoveWindow(wndCt);
		m_ButtonState=true;
		return;
	}
	ct.DeflateRect(7*ct.Width()/ct.Height(),7,7*ct.Width()/ct.Height(),7);
	
	m_CartoonPlay.MoveWindow((wndCt.Width()-ct.Width())/2,
							 (wndCt.Height()-ct.Height())/2,
							 ct.Width(),
							 ct.Height());
	CDialogEx::OnTimer(nIDEvent);
}

void MemoryOptimizer::MovebkPic(int BkgroundPic)
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

void MemoryOptimizer::ClenMemory()
{
	MEMORYSTATUSEX stcMemStatusEx={};
	stcMemStatusEx.dwLength=sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsedMem=stcMemStatusEx.ullTotalPhys-stcMemStatusEx.ullAvailPhys;
	m_Memzhanyong =(double)preUsedMem/1024/1024/1000;

	hh.Format(L"%0.2lf",m_Memzhanyong);
	//�����ڴ�
	DWORD dwPIDList[1000]={0};
	DWORD bufSize=sizeof(dwPIDList);
	DWORD dwNeedSize=0;
	EnumProcesses(dwPIDList,bufSize,&dwNeedSize);
	for (DWORD i=0;i<dwNeedSize/sizeof(DWORD);i++)
	{
		HANDLE hProcess=OpenProcess(	PROCESS_SET_QUOTA,false,dwPIDList[i]);
		SetProcessWorkingSetSize(hProcess,-1,-1);
	}
	// ��ȡ�������ڴ�״̬
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUsedMem=stcMemStatusEx.ullTotalPhys-stcMemStatusEx.ullAvailPhys;
	m_delMemory=(preUsedMem-afterCleanUsedMem)/1024/1024;		//��ɾ���ڴ�
	hd.Format(L"%d",m_delMemory);


}

void MemoryOptimizer::WriteChar(int nHeight,int nWidth, int nEscapement,int nOrientation, int x,int y,CString context,CString fontStyle/*=L"����"*/,BYTE FontQuality/*=CLEARTYPE_QUALITY*/)
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
