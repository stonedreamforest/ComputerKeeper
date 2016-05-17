// MemoryOptimizer.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "MemoryOptimizer.h"
#include "afxdialogex.h"
#include <Psapi.h>


// MemoryOptimizer 对话框

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


// MemoryOptimizer 消息处理程序


BOOL MemoryOptimizer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值  
	/*if (!m_ButtonState)
	{
		return true;
	}*/
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
	return CDialogEx::OnEraseBkgnd(pDC);
}


void MemoryOptimizer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
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
	// 异常: OCX 属性页应返回 FALSE
}


void MemoryOptimizer::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取客户端窗口  
	m_MemoryButton.ShowWindow(SW_HIDE);
	ClenMemory();
	if (m_ButtonState)
	{
		SetTimer(1,100,NULL);
		m_BackgroundPic=IDB_BITMAP46;//背景图片
		MovebkPic(m_BackgroundPic);
		m_ButtonState=false;
		RECT rc;
		this->GetClientRect(&rc);  
		// 更新位置  
		m_CartoonPlay.MoveWindow(&rc, true);  
		CString fileName ;

		TCHAR path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,path);
		fileName.Format(L"%s\\flash3038.swf",path);

		// flash文件名  
		// 加载flash文件  
		m_CartoonPlay.LoadMovie(0, fileName);  
		// 播放  
		m_CartoonPlay.ShowWindow(SW_SHOW);
		m_CartoonPlay.Play(); 
	}
	if (!m_MemoryButton)
	{
		m_BackgroundPic=IDB_BITMAP54;//背景图片
		MovebkPic(m_BackgroundPic);
		m_ButtonState=true;
	}

//	Sleep(1000);
	//m_CartoonPlay.ShowWindow(SW_HIDE);
	
	
}



void MemoryOptimizer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
		xianshi=L"目前内存使用："+hh+L"G"+L"已清理内存"+hd+L"MB";
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

void MemoryOptimizer::ClenMemory()
{
	MEMORYSTATUSEX stcMemStatusEx={};
	stcMemStatusEx.dwLength=sizeof(stcMemStatusEx);
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG preUsedMem=stcMemStatusEx.ullTotalPhys-stcMemStatusEx.ullAvailPhys;
	m_Memzhanyong =(double)preUsedMem/1024/1024/1000;

	hh.Format(L"%0.2lf",m_Memzhanyong);
	//清理内存
	DWORD dwPIDList[1000]={0};
	DWORD bufSize=sizeof(dwPIDList);
	DWORD dwNeedSize=0;
	EnumProcesses(dwPIDList,bufSize,&dwNeedSize);
	for (DWORD i=0;i<dwNeedSize/sizeof(DWORD);i++)
	{
		HANDLE hProcess=OpenProcess(	PROCESS_SET_QUOTA,false,dwPIDList[i]);
		SetProcessWorkingSetSize(hProcess,-1,-1);
	}
	// 获取清理后的内存状态
	GlobalMemoryStatusEx(&stcMemStatusEx);
	DWORDLONG afterCleanUsedMem=stcMemStatusEx.ullTotalPhys-stcMemStatusEx.ullAvailPhys;
	m_delMemory=(preUsedMem-afterCleanUsedMem)/1024/1024;		//已删除内存
	hd.Format(L"%d",m_delMemory);


}

void MemoryOptimizer::WriteChar(int nHeight,int nWidth, int nEscapement,int nOrientation, int x,int y,CString context,CString fontStyle/*=L"宋体"*/,BYTE FontQuality/*=CLEARTYPE_QUALITY*/)
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
