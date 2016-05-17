#include "stdafx.h"
#include "MyListCtrl.h"

#define IDC_BUTTON_ID 0x5678		//��ť��ID

CMyListCtrl::CMyListCtrl(void)
{
	m_currRowID = -1;
	m_uID = IDC_BUTTON_ID;
}


CMyListCtrl::~CMyListCtrl(void)
{
}
BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM_REFLECT()
	//ON_NOTIFY_REFLECT(LVN_INSERTITEM, &CMyListCtrl::OnLvnInsertitem)
	ON_NOTIFY_REFLECT(LVN_ENDSCROLL, &CMyListCtrl::OnLvnEndScroll)
END_MESSAGE_MAP()


void CMyListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( m_nItemHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_nItemHeight;

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMyListCtrl::SetItemHeight(UINT nHeight)
{
	m_nItemHeight = nHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}


void CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

// 	int    nItem = lpDrawItemStruct->itemID;
// 	CDC*   pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
// 	CRect   rcBound, rcLabel, rcIcon;
// 	//����б���ͼ��,��ǩ,���������
// 	GetItemRect ( nItem, rcIcon, LVIR_ICON );
// 	GetItemRect ( nItem, rcLabel, LVIR_LABEL );
// 	GetItemRect ( nItem, rcBound, LVIR_BOUNDS );




	//ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);  
	CDC dc;   
	dc.Attach(lpDrawItemStruct->hDC);  
//	ASSERT(NULL != dc.GetSafeHdc());  



	//3.  �Ի����ý�����У���һ����ɫ��ѡ��
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&  
		(lpDrawItemStruct->itemState & ODS_FOCUS))  
	{  
		CBrush br(RGB(255, 0, 0));  
		CRect ct = lpDrawItemStruct->rcItem;
		ct.DeflateRect(1,1,1,1);
		dc.FrameRect(&ct, &br);  
	}  

	//4.  �ػ��ı����ı�������Ҫ�ػ�һ�� �������ı���ʾ������
	//Draw the text. 
	CString strText(_T(""));  
	CRect rcItem;  
	for(int i=0; i<GetHeaderCtrl()->GetItemCount(); i++)  
	{  
		strText = GetItemText(lpDrawItemStruct->itemID, i);  
		GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem);  
		rcItem.left += 5;  
		dc.DrawText(  
			strText,  
			strText.GetLength(),  
			&rcItem,  
			DT_LEFT|DT_SINGLELINE|DT_VCENTER);  
	}
	
	dc.Detach();  

}

void CMyListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if( m_nItemHeight > 0 )
		lpMeasureItemStruct->itemHeight = m_nItemHeight;
}


//void CMyListCtrl::OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	// TODO: Add your control notification handler code here
//	CButton *btn = new CButton;
//	int rowID = pNMListView->iItem;	//�ڼ���
//	int x = 600;					//��ť��ʼxƫ��			
//	int y = 20;					    //��ť��ʼyƫ��	
//	int rowHight = 100;				//�и�
//	int btnHight = 50;
//	int btnwidth = 150;
//	if (m_currRowID!=rowID)
//	{
//		CString title;
//		title.Format(L"��ť��Ӧ����%d",rowID);
//		btn->Create(title,WS_CHILD | WS_VISIBLE,CRect(x,y+rowHight*rowID,x+btnwidth,y+rowHight*rowID+btnHight),this,pNMListView->iItem);
//		btn->ShowWindow(SW_SHOW);
//		m_currRowID=rowID;
//	}
//	
//	*pResult = 0;
//}

void CMyListCtrl::createItemButton(int nItem, int nSubItem, HWND hMain)
{
	//CRect rect;
	int offset = 0;

	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) 
		return ;

//	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);			//�õ����п��


	int rowID =nItem;	//�ڼ���
	int x = 670;					//��ť��ʼxƫ��	
	int y = 20;					    //��ť��ʼyƫ��	
	int rowHight = 100;				//�и�
	int btnHight = 50;
	int btnwidth = 150;
	CRect rect(x,y+rowHight*rowID,x+btnwidth,y+rowHight*rowID+btnHight);
	// Now scroll if we need to expose the column
	//CRect rcClient;
	//GetClientRect(rcClient);
	//if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	//{
	//	CSize size;
	//	size.cx = offset + rect.left;
	//	size.cy = 0;
	//	Scroll(size);
	//	rect.left -= size.cx;
	//}

	//rect.left += offset;	
	//rect.right = rect.left + GetColumnWidth(nSubItem);
	//if(rect.right > rcClient.right) 
	//	rect.right = rcClient.right;
	////basic code end

	//rect.bottom = rect.top + rect.Height();

	//int iPageCout = GetCountPerPage();
	//if ( nItem >= iPageCout )
	//{
	//	rect.top += rect.Height();
	//	rect.bottom += rect.Height();
	//}

	
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE;		//���
	ListButton *pButton = new ListButton(nItem,nSubItem,rect,hMain);
	m_uID++;
	pButton->Create(_T("��ֹ������"),dwStyle, rect, this, m_uID);
	m_mButton.insert( make_pair( nItem, pButton ) );

	int iTopIndex = GetTopIndex();
	if ( iTopIndex > 0 )
	{
		updateListCtrlButtonPos();
	}

	return;
}

void CMyListCtrl::updateListCtrlButtonPos()
{
	int iTopIndex = GetTopIndex();		//��õ�������
	int nItem = iTopIndex;
	button_map::iterator iter;
	button_map::iterator iterUp;
	int iLine = 0;
#ifdef USE_TOPINDEX_BUTTON
	iter = m_mButton.find( iTopIndex );
	iterUp = m_mButton.begin();
	while ( iter != m_mButton.end() )
	{
		iterUp->second->EnableWindow( iter->second->bEnable );
		iter ++;
		iterUp++;
	}
#else
	for ( ; nItem < GetItemCount(); nItem++ )
	{
		iter = m_mButton.find(nItem);
		if( iter!= m_mButton.end() )
		{
			CRect rect;
			iterUp = m_mButton.find(iLine);
			rect = iterUp->second->m_rect;
			iter->second->MoveWindow( &rect );
			iter->second->ShowWindow( SW_SHOW );
			if( iLine < iTopIndex )
			{
				iterUp->second->ShowWindow( SW_HIDE );
			}
			iLine++;
		}
	}
#endif
}

void CMyListCtrl::enableButton(BOOL bFlag, int iItem)
{
	button_map::iterator iter;
#ifdef USE_TOPINDEX_BUTTON
	int iTopIndex = GetTopIndex();
	int nItem = iItem - iTopIndex;
	iter = m_mButton.find( iItem );
	if ( iter != m_mButton.end() )
	{
		iter->second->bEnable = bFlag;
	}
	iter = m_mButton.find( nItem );
	if ( iter != m_mButton.end() )
	{
		iter->second->EnableWindow( bFlag );
	}
#else
	iter = m_mButton.find( iItem );
	if ( iter != m_mButton.end() )
	{
		iter->second->EnableWindow( bFlag );
	}
#endif

}


void CMyListCtrl::OnLvnEndScroll(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Internet Explorer 5.5 ����߰汾��
	// ���� _WIN32_IE ������ >= 0x0560��


	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	updateListCtrlButtonPos();	//��Ӧ��Ϣ
		*pResult = 0;
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
