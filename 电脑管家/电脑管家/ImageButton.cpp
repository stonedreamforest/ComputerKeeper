// ImageButton.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "ImageButton.h"
#include "Resource.h"


// ImageButton

IMPLEMENT_DYNAMIC(ImageButton, CButton)

ImageButton::ImageButton()
{
	m_IsHighLight=false;//默认按钮没有处于高亮状态 
	m_uStyle=DFCS_BUTTONPUSH;//窗口的默认样式 
	m_HighLightTextColor=RGB(255,255,255);//默认高亮字体为红色 
	m_HighLightBkColor=RGB(255,255,255);//默认高亮背景色为绿色 
	m_ImageButton =0;
}

ImageButton::~ImageButton()
{
}


BEGIN_MESSAGE_MAP(ImageButton, CButton)
//	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// ImageButton 消息处理程序




//void ImageButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	//依据窗口类型绘制控件 
//	::DrawFrameControl(lpDrawItemStruct->hDC,&lpDrawItemStruct->rcItem,DFC_BUTTON,m_uStyle); 
//	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC); 
//	//获取按钮的文本信息 
//	CString strText; 
//	GetWindowText(strText); 
//	LONG dist=0;//缩进距离 
//	CBrush brush; 
//	CRect rect; 
//	CRect focusRect; 
//	if(m_IsHighLight) 
//	{ 
//		brush.CreateSolidBrush(m_HighLightBkColor); 
//	} 
//	else 
//	{ 
//		brush.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE)); 
//	} 
//	rect.CopyRect(&lpDrawItemStruct->rcItem); 
//	dist=2; 
//	rect.left+=dist; 
//	rect.right-=dist; 
//	rect.top+=dist; 
//	rect.bottom-=dist; 
//	::FillRect(lpDrawItemStruct->hDC,&rect,(HBRUSH)brush.m_hObject); 
//	::SetBkMode(lpDrawItemStruct->hDC,TRANSPARENT); 
//	COLORREF crOldColor; 
//	if(m_IsHighLight) 
//	{ 
//		crOldColor=::SetTextColor(lpDrawItemStruct->hDC,m_HighLightTextColor); 
//	} 
//	else 
//	{ 
//		crOldColor=::SetTextColor(lpDrawItemStruct->hDC,RGB(0,0,0)); 
//	} 
//	::DrawText(lpDrawItemStruct->hDC,strText,strText.GetLength(),&lpDrawItemStruct->rcItem,DT_SINGLELINE|DT_VCENTER|DT_CENTER); 
//	::SetTextColor(lpDrawItemStruct->hDC,crOldColor); 
//	if(::GetFocus()==this->m_hWnd) 
//	{ 
//		focusRect.CopyRect(&lpDrawItemStruct->rcItem); 
//		dist=3;//缩进距离 
//		focusRect.left+=dist; 
//		focusRect.right-=dist; 
//		focusRect.top+=dist; 
//		focusRect.bottom-=dist; 
//		::DrawFocusRect(lpDrawItemStruct->hDC,(LPRECT)&focusRect); 
//	} 
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}


void ImageButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//依据窗口类型绘制控件 
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);

	CRect rect;	
	GetClientRect(&rect);	//加载背景位图	
	CBitmap bmpBackground;
	

	switch (m_btnState)
	{
	case NORMAL:		
		m_ImageButton = m_pic_normal;
		break;
	case MOUSEOVER:
		m_ImageButton = m_pic_hover;
		break;
	case BUTTONDOWN:
		m_ImageButton = m_pic_down;
		break;
	}
	if (m_ImageButton==0)
	{
		m_ImageButton = m_pic_normal;
	}
	bmpBackground.LoadBitmap(MAKEINTRESOURCE(m_ImageButton)); //图片ID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//选择位图	//创建内存DC	
	CDC dc;	
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//绘制位图	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//设置指定设备环境中的位图拉伸模式。
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//恢复原有位图	
	dc.SelectObject(pOldBitmap);

// 	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
// 	CRect _rt;
// 	this->GetClientRect(_rt);
// 
// 	CDC dcBuffer;//后台缓存
// 	dcBuffer.CreateCompatibleDC(pDC);
// 	CBitmap dfbmp;//设置后台缓存大小
// 	dfbmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP3));
// 	dfbmp.CreateCompatibleBitmap(pDC,_rt.right,_rt.bottom);
// 	dcBuffer.SelectObject(&dfbmp);
// 	dcBuffer.SetBkMode(TRANSPARENT);

	

}
//初始化图片
void ImageButton::InitialImage(int normal,int hover,int down)
{
	m_pic_normal= normal;	//正常
	m_pic_down	= down;		//按下
	m_pic_hover	= hover;	//鼠标悬停
}


void ImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//需要手动触发TME_LEAVE消息和TME_HOVER消息
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;	// 要触发的消息
	tme.hwndTrack = this->m_hWnd;			// 指定为按钮窗口
	tme.dwHoverTime = 20;					// 我觉得应该是检测的间隔，每20毫秒检测一次
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}


void ImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//一直在按钮上方，则不重复触发
	if (m_bIsMouseHower == TRUE)
	{
		return;
	}
	//第一次上来，触发
	m_bIsMouseHower = TRUE;

	m_btnState = MOUSEOVER;					//按钮状态，鼠标悬停状态
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseHover(nFlags, point);
}


void ImageButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//离开后触发
	m_bIsMouseHower = FALSE;
	m_btnState = NORMAL;					  //按钮状态，正常状态
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseLeave();
	
}

void ImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = FALSE;
	m_btnState = MOUSEOVER;					//按钮状态，恢复悬停状态
	InvalidateRect(NULL, TRUE); 
	CButton::OnLButtonUp(nFlags, point);
}	

void ImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = TRUE;
	m_btnState = BUTTONDOWN;					//按钮状态，被点击状态
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}

