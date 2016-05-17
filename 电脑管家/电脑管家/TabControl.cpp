// TabControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "TabControl.h"


// TabControl

IMPLEMENT_DYNAMIC(TabControl, CTabCtrl)

TabControl::TabControl()
{
	m_dlgCount = 0;
}

TabControl::~TabControl()
{
}


BEGIN_MESSAGE_MAP(TabControl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &TabControl::OnTcnSelchange)
	ON_WM_DRAWITEM()
//	ON_WM_NCHITTEST()
//ON_WM_DROPFILES()
END_MESSAGE_MAP()



// TabControl ��Ϣ�������




void TabControl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD sel=this->GetCurSel();
	for (DWORD i=0;i<m_dlgCount;i++)
	{
		if (sel==i)
		{
			setshow(i);
		}
		else
		{
			m_processDlg[i]->ShowWindow(SW_HIDE);
		}
	}
	*pResult = 0;
}

void TabControl::addDlg(DWORD count,...)
{
	va_list vl;
	va_start(vl,count);
	for (DWORD i=0;i<count;i++)
	{
		UINT uid=va_arg(vl,UINT);
		m_processDlg[i]=va_arg(vl,CDialogEx*);
		m_processDlg[i]->Create(uid,this);
		m_dlgCount++;
	}
	va_end(vl);
}

void TabControl::setshow(int sel)
{
	CRect rect;
	GetClientRect(&rect);	
	rect.DeflateRect(-11,22,1,1);//��У����

	m_processDlg[sel]->MoveWindow(rect);
	m_processDlg[sel]->ShowWindow(SW_SHOW);
}


void TabControl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡTabControl���ؼ��Ĺ������� 

// 	TC_ITEM tci;
// 	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
// 	CRect rect(lpDrawItemStruct->rcItem);
// 	TCHAR szTabText[256];
// 	memset(szTabText,'\0',sizeof(szTabText));
// 	tci.mask = TCIF_TEXT;
// 	tci.pszText = szTabText;
// 	tci.cchTextMax = sizeof(szTabText) -1;
// 	GetItem(lpDrawItemStruct->itemID, &tci);
// 	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)
// 	{
// 		pDC->TextOut(rect.left+5, rect.top+5, tci.pszText);
// 	}
// 	if ((lpDrawItemStruct->itemState & ODS_SELECTED) && 
// 		(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
// 	{
// 		//Make the color of text of the selected tab to be BLUE.
// 		pDC->SetTextColor(RGB(0,0,255));
// 		pDC->TextOut(rect.left+5, rect.top+5, tci.pszText);
// 	}
	//CTabCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


//LRESULT TabControl::OnNcHitTest(CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	//return HTCAPTION;
	//::SendMessage(GetParent()->m_hWnd,WM_NCHITTEST,0,0);
//	return 25;
	//return CTabCtrl::OnNcHitTest(point);
//}

