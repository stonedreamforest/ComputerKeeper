#include "stdafx.h"
#include "MyListCtrl.h"

#define IDC_BUTTON_ID 0x5678		//按钮的ID

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
// 	//获得列表项图标,标签,及项的区域
// 	GetItemRect ( nItem, rcIcon, LVIR_ICON );
// 	GetItemRect ( nItem, rcLabel, LVIR_LABEL );
// 	GetItemRect ( nItem, rcBound, LVIR_BOUNDS );




	//ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);  
	CDC dc;   
	dc.Attach(lpDrawItemStruct->hDC);  
//	ASSERT(NULL != dc.GetSafeHdc());  



	//3.  自绘设置焦点的行，画一个红色框选中
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&  
		(lpDrawItemStruct->itemState & ODS_FOCUS))  
	{  
		CBrush br(RGB(255, 0, 0));  
		CRect ct = lpDrawItemStruct->rcItem;
		ct.DeflateRect(1,1,1,1);
		dc.FrameRect(&ct, &br);  
	}  

	//4.  重绘文本，文本内容需要重绘一遍 ；否则文本显示不出来
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
//	int rowID = pNMListView->iItem;	//第几行
//	int x = 600;					//按钮初始x偏移			
//	int y = 20;					    //按钮初始y偏移	
//	int rowHight = 100;				//行高
//	int btnHight = 50;
//	int btnwidth = 150;
//	if (m_currRowID!=rowID)
//	{
//		CString title;
//		title.Format(L"按钮对应的行%d",rowID);
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

//	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);			//得到行列宽高


	int rowID =nItem;	//第几行
	int x = 670;					//按钮初始x偏移	
	int y = 20;					    //按钮初始y偏移	
	int rowHight = 100;				//行高
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

	
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE;		//风格
	ListButton *pButton = new ListButton(nItem,nSubItem,rect,hMain);
	m_uID++;
	pButton->Create(_T("禁止自启动"),dwStyle, rect, this, m_uID);
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
	int iTopIndex = GetTopIndex();		//获得单击行数
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
	// 此功能要求 Internet Explorer 5.5 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0560。


	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	updateListCtrlButtonPos();	//响应消息
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码

}
