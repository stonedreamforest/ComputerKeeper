// HomePage.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "HomePage.h"
#include "afxdialogex.h"
#include <winuser.h>

// HomePage 对话框

IMPLEMENT_DYNAMIC(HomePage, CDialogEx)

HomePage::HomePage(CWnd* pParent /*=NULL*/)
	: CDialogEx(HomePage::IDD, pParent)
{
	m_ButtonState=false;
}

HomePage::~HomePage()
{
}

void HomePage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_HomeButton);
}


BEGIN_MESSAGE_MAP(HomePage, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &HomePage::OnBnClickedButton1)
END_MESSAGE_MAP()


// HomePage 消息处理程序


BOOL HomePage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 //TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (!m_ButtonState)
	{
		return true;
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
	//return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL HomePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//if (!m_ButtonState)
	//{
	//	return true;
	//}
	// TODO:  在此添加额外的初始化
	m_HomeButton.MoveWindow(615,55,180,56);
	m_HomeButton.InitialImage(IDB_BITMAP4,IDB_BITMAP17,IDB_BITMAP16);

	m_ButtonState=true;
	m_BackgroundPic=IDB_BITMAP2;
	//SetDialogBkColor((RGB(0,0,255),RGB(255,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}


BOOL HomePage::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDialogEx::PreCreateWindow(cs);
}


LRESULT HomePage::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	return HTCAPTION;
//	 ;
	:: SendMessage(AfxGetApp()->m_pMainWnd->m_hWnd,WM_NCHITTEST,0,0);
//	return 25;
	return CDialogEx::OnNcHitTest(point);
}


HBRUSH HomePage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC-> SetTextColor(RGB(0,0,0));     //字体颜色
		pDC-> SetBkMode(TRANSPARENT);       //字体背景色   

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return (HBRUSH)::GetStockObject(NULL_BRUSH); // 设置背景色;
}


void HomePage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
		if (m_ButtonState)
		{
			m_BackgroundPic=IDB_BITMAP55;
			MovebkPicXia(m_BackgroundPic);
			m_BackgroundPic=IDB_BITMAP56;
			MovebkPicYou(m_BackgroundPic);
			m_BackgroundPic=IDB_BITMAP57;
			MovebkPicZuoxia(m_BackgroundPic);
			m_mem.ClenMemory();
			m_HomeButton.ShowWindow(SW_HIDE);

			m_ButtonState=false;
		}
		if (!m_ButtonState)
		{
			//m_BackgroundPic=IDB_BITMAP55;
			MovebkPicXia(IDB_BITMAP2);
			m_HomeButton.MoveWindow(615,55,180,56);
			m_HomeButton.InitialImage(IDB_BITMAP4,IDB_BITMAP17,IDB_BITMAP16);
			m_ButtonState=true;
			m_HomeButton.ShowWindow(SW_SHOW);
		}
}

void HomePage::MovebkPicZuo(int BkgroundPic)
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

void HomePage::MovebkPicXia(int BkgroundPic)
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

void HomePage::MovebkPicYou(int BkgroundPic)
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

	for (int i = -30; i <=0; i = i++)
	{	
		pDC->StretchBlt(rect.Width()*i/30,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);

	
}

void HomePage::MovebkPicZuoxia(int BkgroundPic)
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

	for (int i = -30; i <=0; i = i++)
	{	
		pDC->StretchBlt(rect.Width()*i/30,rect.Height()*i/30,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}

//下右带入