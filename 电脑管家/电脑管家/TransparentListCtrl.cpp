// TransparentListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
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



// TransparentListCtrl ��Ϣ�������




void TransparentListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
