#pragma once
#include "ImageButton.h"
#include "afxwin.h"



//清理垃圾类型
enum DEL_RUBBISH_TYPE
{
	CLEAN_INTERNET_TEMP = 0, CLEAN_INTERNET_COOKIE, CLEAN_ADDRBAR_HISTORY, CLEAN_FORM_HISTORY,
	CLEAN_PASSWORD_HISTORY, CLEAN_FAVORITE_CONTENT, CLEAN_RAS_HISTORY, CLEAN_SYSTEM_TEMP, 
	CLEAN_RUBBISH_STATION, CLEAN_RUN_HISTORY, CLEAN_DOCUMENT_HISTORY, CLEAN_PREVUSER_HISTORY,
	CLEAN_FILEFIND_HISTORY, CLEAN_COMPFIND_HISTORY, CLEAN_NETCONTECT_HISTORY, CLEAN_REMOTE_HISTORY,
	CLEAN_BROWSEADDR_HISTORY, CLEAN_OTHER
};

//清理的缓冲类型
enum DEL_CACHE_TYPE
{
	FILES = 0, COOKIES
};

//成功清理的类型
enum CLEAN_SUCCESS_TYPE
{
	CLEAN_SUCCESS_INTERNET = 0,
	CLEAN_SUCCESS_LOCAL,
	CLEAN_SUCCESS_OTHER
};

enum OPTIMIZATION_TIPS_TYPE
{
	OPTIMIZATION_TIPS_START = 0,
	OPTIMIZATION_TIPS_END
};

enum SOFTWARE_TIPS_TYPE
{
	SOFTWARE_TIPS_START = 0,
	SOFTWARE_TIPS_END
};

enum NAME_IN_WHERE
{
	NAME_IN_NONE = 0,
	NAME_IN_RUN,
	NAME_IN_DISABLED
};
// CleanSpace 对话框

class CleanSpace : public CDialogEx
{
	DECLARE_DYNAMIC(CleanSpace)

public:
	CleanSpace(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CleanSpace();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//ImageButton m_ImageButton;
	afx_msg void OnBnClickedButton1();
	//CButton m_ImageButton;
	ImageButton m_ImageButton1;
	int m_BackgroundPic;
	bool m_ClickFlag;
private:
	VOID CleanInternetTemp();			/**清理Interner临时文件*/
	VOID CleanInternetCookie();			/**清理Internet Cookie*/
	VOID CleanAddrBarHistory();			/**清理地址栏历史记录*/

	VOID CleanPasswordHistory();		/**清理密码记录*/
	VOID CleanFavoriteContent();		/**清理收藏夹内容*/
	VOID CleanRASHistory();				/**清理RAS记录*/
	VOID CleanSystemTemp();				/**清理系统临时文件夹*/
	VOID CleanRubbishStation();			/**清理垃圾回收站*/	
	VOID CleanRunHistory();				/**清理运行记录*/
	VOID CleanDocumentHistory();		/**清理文档记录*/
	VOID CleanPrevUserHistory();		/**清理上次用户登录记录*/
	VOID CleanFileFindHistory();		/**清理文件查找记录*/
	VOID CleanCompFindHisroty();		/**清理查找计算机记录*/
	VOID CleanNetContectHistory();		/**清理网联记录*/
	VOID CleanRemoteHistory();			/**清理远程连接记录*/
	VOID CleanBrowseAddrHistory();		/**清理浏览网址记录*/
private:

	BOOL DeleteUrlCache(DEL_CACHE_TYPE type);				/**清除Url缓存*/
	BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE, 
						BOOL bWipeIndexDat = FALSE);		/**清空一个目录*/
	BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);			/**擦除文件内容*/

	void WriteChar(int nHeight,int  nWidth, int nEscapement,int nOrientation,
		int x,int y,CString context,CString fontStyle=L"宋体",BYTE FontQuality=CLEARTYPE_QUALITY);	//设置字体
	void CleanInterface();		//正在清理界面
	void MovebkPic(	int BkgroundPic);			//移动背景图

};
