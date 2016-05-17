// AssignKill.cpp : 实现文件
//

#include "stdafx.h"
#include "电脑管家.h"
#include "AssignKill.h"
#include "afxdialogex.h"


// AssignKill 对话框

IMPLEMENT_DYNAMIC(AssignKill, CDialogEx)

AssignKill::AssignKill(CWnd* pParent /*=NULL*/)
	: CDialogEx(AssignKill::IDD, pParent)
	, m_FilePathName(_T(""))
{
	m_IsKill=false;
}

AssignKill::~AssignKill()
{
}

void AssignKill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//	DDX_Control(pDX, IDC_EDIT1, m_FilePathName);
	DDX_Text(pDX, IDC_EDIT1, m_FilePathName);
}


BEGIN_MESSAGE_MAP(AssignKill, CDialogEx)
	ON_WM_DROPFILES()
	ON_EN_CHANGE(IDC_EDIT1, &AssignKill::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &AssignKill::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &AssignKill::OnBnClickedButton2)
END_MESSAGE_MAP()


// AssignKill 消息处理程序


void AssignKill::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT movecount=DragQueryFile(hDropInfo,-1,NULL,0);
	for (UINT i=0;i<movecount;i++)
	{
		TCHAR movefile[MAX_PATH]={0};
		DragQueryFile(hDropInfo,i,movefile,MAX_PATH);
		m_FilePathName=movefile;
		UpdateData(FALSE);
	}
	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);
}


void AssignKill::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	UpdateData(TRUE);

	// TODO:  在此添加控件通知处理程序代码
}


void AssignKill::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szDir[MAX_PATH];  
	BROWSEINFO bi;   
	ITEMIDLIST *pidl;   
	bi.hwndOwner = this->m_hWnd;   
	bi.pidlRoot = NULL;  
	bi.pszDisplayName = szDir;//这个是输出缓冲区   
	bi.lpszTitle = _T("选择输出文件夹："); //标题  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//使用新的界面,在win7中效果较好//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;  
	bi.lParam = 0;  
	bi.iImage = 0;  
	pidl = SHBrowseForFolder(&bi);//弹出对话框   
	if (pidl == NULL)//点了取消，或者选择了无效的文件夹则返回NULL  
		return;  

	if(SHGetPathFromIDList(pidl, szDir))   
		m_FilePathName = szDir;//szDir就是要获取的文件夹    
	UpdateData(FALSE);
}


void AssignKill::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_IsKill=true;
	EndDialog(0);
}


//BOOL AssignKill::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//#5312
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//
//#5312
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	// TODO:  在此添加额外的初始化
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	// 异常: OCX 属性页应返回 FALSE
//}
