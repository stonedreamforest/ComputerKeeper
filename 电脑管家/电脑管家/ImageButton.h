#pragma once


// ImageButton

class ImageButton : public CButton
{
	DECLARE_DYNAMIC(ImageButton)

public:
	ImageButton();
	virtual ~ImageButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	bool m_IsHighLight;//��¼��ť�Ƿ��ڸ���״̬�ı�־ 
	UINT m_uStyle;//��¼��ť���͵ı��� 
	COLORREF m_HighLightTextColor;//�ı�������ɫֵ 
	COLORREF m_HighLightBkColor;//����������ɫֵ 
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	int m_ImageButton;
	int m_pic_normal;	//����
	int m_pic_down;		//����
	int m_pic_hover;	//�����ͣ
	void InitialImage(int normal,int hover=0,int down=0);			//��ʼ��ͼƬ
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	enum BUTTONSTATE{ NORMAL, MOUSEOVER, BUTTONDOWN };
	BUTTONSTATE m_btnState;					//��ť״̬
	bool m_bIsButtonDown;
	bool m_bIsMouseHower;
};


