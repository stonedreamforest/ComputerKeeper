#include "stdafx.h"
#include "ListButton.h"

#define  WM_BN_CLICK  WM_USER + 100
ListButton::ListButton(void)
{
}

ListButton::ListButton(int nItem, int nSubItem, CRect rect, HWND hParent)
{
	m_inItem = nItem;			//����
	m_inSubItem = nSubItem;
	m_rect = rect;
	m_hParent = hParent;
	bEnable = TRUE;
}


ListButton::~ListButton(void)
{
}
BEGIN_MESSAGE_MAP(ListButton, CButton)
	ON_CONTROL_REFLECT(BN_CLICKED, &ListButton::OnBnClicked)
END_MESSAGE_MAP()


void ListButton::OnBnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage( m_hParent, WM_BN_CLICK, m_inItem, m_inSubItem );
}
