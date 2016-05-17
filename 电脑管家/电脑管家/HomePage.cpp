// HomePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "HomePage.h"
#include "afxdialogex.h"
#include <winuser.h>

// HomePage �Ի���

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


// HomePage ��Ϣ�������


BOOL HomePage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 //TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if (!m_ButtonState)
	{
		return true;
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
	//return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL HomePage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//if (!m_ButtonState)
	//{
	//	return true;
	//}
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_HomeButton.MoveWindow(615,55,180,56);
	m_HomeButton.InitialImage(IDB_BITMAP4,IDB_BITMAP17,IDB_BITMAP16);

	m_ButtonState=true;
	m_BackgroundPic=IDB_BITMAP2;
	//SetDialogBkColor((RGB(0,0,255),RGB(255,0,0));
	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL HomePage::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	return CDialogEx::PreCreateWindow(cs);
}


LRESULT HomePage::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		pDC-> SetTextColor(RGB(0,0,0));     //������ɫ
		pDC-> SetBkMode(TRANSPARENT);       //���屳��ɫ   

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return (HBRUSH)::GetStockObject(NULL_BRUSH); // ���ñ���ɫ;
}


void HomePage::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

void HomePage::MovebkPicXia(int BkgroundPic)
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

void HomePage::MovebkPicYou(int BkgroundPic)
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

	for (int i = -30; i <=0; i = i++)
	{	
		pDC->StretchBlt(rect.Width()*i/30,0,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);

	
}

void HomePage::MovebkPicZuoxia(int BkgroundPic)
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

	for (int i = -30; i <=0; i = i++)
	{	
		pDC->StretchBlt(rect.Width()*i/30,rect.Height()*i/30,rect.Width(),rect.Height(),&dc,0,0,bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);	//�ָ�ԭ��λͼ	
		Sleep(10);
	}
	dc.SelectObject(pOldBitmap);
}

//���Ҵ���