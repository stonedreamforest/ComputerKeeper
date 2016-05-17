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
	bool m_IsHighLight;//记录按钮是否处于高亮状态的标志 
	UINT m_uStyle;//记录按钮类型的变量 
	COLORREF m_HighLightTextColor;//文本高亮颜色值 
	COLORREF m_HighLightBkColor;//背景高亮颜色值 
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	int m_ImageButton;
	int m_pic_normal;	//正常
	int m_pic_down;		//按下
	int m_pic_hover;	//鼠标悬停
	void InitialImage(int normal,int hover=0,int down=0);			//初始化图片
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	enum BUTTONSTATE{ NORMAL, MOUSEOVER, BUTTONDOWN };
	BUTTONSTATE m_btnState;					//按钮状态
	bool m_bIsButtonDown;
	bool m_bIsMouseHower;
};


