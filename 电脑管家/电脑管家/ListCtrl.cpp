// ListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "ListCtrl.h"


// ListCtrl

IMPLEMENT_DYNAMIC(ListCtrl, CListCtrl)

ListCtrl::ListCtrl()
{
	

}

ListCtrl::~ListCtrl()
{
}


BEGIN_MESSAGE_MAP(ListCtrl, CListCtrl)
//	ON_WM_CREATE()
END_MESSAGE_MAP()



// ListCtrl 消息处理程序
void ListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

//	ASSERT(lpDrawItemStruct->CtlType == ODT_LISTVIEW);  
	CDC dc;   
	dc.Attach(lpDrawItemStruct->hDC);  
//	ASSERT(NULL != dc.GetSafeHdc());  

	// Save these value to restore them when done drawing.  
	COLORREF crOldTextColor = dc.GetTextColor();  
	COLORREF crOldBkColor = dc.GetBkColor();  

	// 1. 自绘seleteed 的行，设置为系统的选中色
	//If this item is selected, set the background color   
	// and the text color to appropriate values. Also, erase  
	// rect by filling it with the background color.  
	if ( (lpDrawItemStruct->itemAction | ODA_SELECT) &&  
		(lpDrawItemStruct->itemState & ODS_SELECTED))  
	{  
		dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));  
		dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));  
		dc.FillSolidRect(&lpDrawItemStruct->rcItem,   
			::GetSysColor(COLOR_HIGHLIGHT));  
	}

	//2. 自绘偶数行和奇数行，设置为不同的颜色
	else   
	{  
		if(lpDrawItemStruct->itemID%2) //偶数行  
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255,255,132));
			
		else        //奇数行
			dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255,187,255)); 
			
	}  

	//3.  自绘设置焦点的行，画一个红色框选中
	//If this item has the focus, draw a red frame around the  
	// item's rect.  
	if ((lpDrawItemStruct->itemAction | ODA_FOCUS) &&  
		(lpDrawItemStruct->itemState & ODS_FOCUS))  
	{  
		CBrush br(RGB(255, 0, 0));  
		dc.FrameRect(&lpDrawItemStruct->rcItem, &br);  
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

//	 Reset the background color and the text color back to their  
//	 original values.  
	dc.SetTextColor(crOldTextColor);  
	dc.SetBkColor(crOldBkColor);  
	dc.Detach();  

}

