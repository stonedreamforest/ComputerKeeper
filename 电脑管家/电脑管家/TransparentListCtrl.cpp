// TransparentListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "TransparentListCtrl.h"


// TransparentListCtrl

IMPLEMENT_DYNAMIC(TransparentListCtrl, CListCtrl)

TransparentListCtrl::TransparentListCtrl()
{

}

TransparentListCtrl::~TransparentListCtrl()
{
}


BEGIN_MESSAGE_MAP(TransparentListCtrl, CListCtrl)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// TransparentListCtrl 消息处理程序




void TransparentListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
