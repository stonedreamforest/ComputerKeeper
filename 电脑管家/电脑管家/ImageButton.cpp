// ImageButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "ImageButton.h"
#include "Resource.h"


// ImageButton

IMPLEMENT_DYNAMIC(ImageButton, CButton)

ImageButton::ImageButton()
{
	m_IsHighLight=false;//Ĭ�ϰ�ťû�д��ڸ���״̬ 
	m_uStyle=DFCS_BUTTONPUSH;//���ڵ�Ĭ����ʽ 
	m_HighLightTextColor=RGB(255,255,255);//Ĭ�ϸ�������Ϊ��ɫ 
	m_HighLightBkColor=RGB(255,255,255);//Ĭ�ϸ�������ɫΪ��ɫ 
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



// ImageButton ��Ϣ�������




//void ImageButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	//���ݴ������ͻ��ƿؼ� 
//	::DrawFrameControl(lpDrawItemStruct->hDC,&lpDrawItemStruct->rcItem,DFC_BUTTON,m_uStyle); 
//	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC); 
//	//��ȡ��ť���ı���Ϣ 
//	CString strText; 
//	GetWindowText(strText); 
//	LONG dist=0;//�������� 
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
//		dist=3;//�������� 
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

	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ݴ������ͻ��ƿؼ� 
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);

	CRect rect;	
	GetClientRect(&rect);	//���ر���λͼ	
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
	bmpBackground.LoadBitmap(MAKEINTRESOURCE(m_ImageButton)); //ͼƬID	
	BITMAP bitmap;   
	bmpBackground.GetBitmap(&bitmap); 	//ѡ��λͼ	//�����ڴ�DC	
	CDC dc;	
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap=dc.SelectObject(&bmpBackground);	//����λͼ	
	SetStretchBltMode(pDC->m_hDC,STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ��
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
	dc.SelectObject(pOldBitmap);

// 	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);
// 	CRect _rt;
// 	this->GetClientRect(_rt);
// 
// 	CDC dcBuffer;//��̨����
// 	dcBuffer.CreateCompatibleDC(pDC);
// 	CBitmap dfbmp;//���ú�̨�����С
// 	dfbmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP3));
// 	dfbmp.CreateCompatibleBitmap(pDC,_rt.right,_rt.bottom);
// 	dcBuffer.SelectObject(&dfbmp);
// 	dcBuffer.SetBkMode(TRANSPARENT);

	

}
//��ʼ��ͼƬ
void ImageButton::InitialImage(int normal,int hover,int down)
{
	m_pic_normal= normal;	//����
	m_pic_down	= down;		//����
	m_pic_hover	= hover;	//�����ͣ
}


void ImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��Ҫ�ֶ�����TME_LEAVE��Ϣ��TME_HOVER��Ϣ
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE | TME_HOVER;	// Ҫ��������Ϣ
	tme.hwndTrack = this->m_hWnd;			// ָ��Ϊ��ť����
	tme.dwHoverTime = 20;					// �Ҿ���Ӧ���Ǽ��ļ����ÿ20������һ��
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}


void ImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//һֱ�ڰ�ť�Ϸ������ظ�����
	if (m_bIsMouseHower == TRUE)
	{
		return;
	}
	//��һ������������
	m_bIsMouseHower = TRUE;

	m_btnState = MOUSEOVER;					//��ť״̬�������ͣ״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseHover(nFlags, point);
}


void ImageButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�뿪�󴥷�
	m_bIsMouseHower = FALSE;
	m_btnState = NORMAL;					  //��ť״̬������״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnMouseLeave();
	
}

void ImageButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = FALSE;
	m_btnState = MOUSEOVER;					//��ť״̬���ָ���ͣ״̬
	InvalidateRect(NULL, TRUE); 
	CButton::OnLButtonUp(nFlags, point);
}	

void ImageButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bIsButtonDown = TRUE;
	m_btnState = BUTTONDOWN;					//��ť״̬�������״̬
	InvalidateRect(NULL, TRUE);
	CButton::OnLButtonDown(nFlags, point);
}

