// AssignKill.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���Թܼ�.h"
#include "AssignKill.h"
#include "afxdialogex.h"


// AssignKill �Ի���

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


// AssignKill ��Ϣ�������


void AssignKill::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	UpdateData(TRUE);

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void AssignKill::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szDir[MAX_PATH];  
	BROWSEINFO bi;   
	ITEMIDLIST *pidl;   
	bi.hwndOwner = this->m_hWnd;   
	bi.pidlRoot = NULL;  
	bi.pszDisplayName = szDir;//��������������   
	bi.lpszTitle = _T("ѡ������ļ��У�"); //����  
	bi.ulFlags = BIF_NEWDIALOGSTYLE;//ʹ���µĽ���,��win7��Ч���Ϻ�//BIF_RETURNONLYFSDIRS;   
	bi.lpfn = NULL;  
	bi.lParam = 0;  
	bi.iImage = 0;  
	pidl = SHBrowseForFolder(&bi);//�����Ի���   
	if (pidl == NULL)//����ȡ��������ѡ������Ч���ļ����򷵻�NULL  
		return;  

	if(SHGetPathFromIDList(pidl, szDir))   
		m_FilePathName = szDir;//szDir����Ҫ��ȡ���ļ���    
	UpdateData(FALSE);
}


void AssignKill::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	return TRUE;  // return TRUE unless you set the focus to a control
//#5313
//	// �쳣: OCX ����ҳӦ���� FALSE
//}
