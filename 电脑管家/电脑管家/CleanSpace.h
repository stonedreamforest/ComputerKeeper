#pragma once
#include "ImageButton.h"
#include "afxwin.h"



//������������
enum DEL_RUBBISH_TYPE
{
	CLEAN_INTERNET_TEMP = 0, CLEAN_INTERNET_COOKIE, CLEAN_ADDRBAR_HISTORY, CLEAN_FORM_HISTORY,
	CLEAN_PASSWORD_HISTORY, CLEAN_FAVORITE_CONTENT, CLEAN_RAS_HISTORY, CLEAN_SYSTEM_TEMP, 
	CLEAN_RUBBISH_STATION, CLEAN_RUN_HISTORY, CLEAN_DOCUMENT_HISTORY, CLEAN_PREVUSER_HISTORY,
	CLEAN_FILEFIND_HISTORY, CLEAN_COMPFIND_HISTORY, CLEAN_NETCONTECT_HISTORY, CLEAN_REMOTE_HISTORY,
	CLEAN_BROWSEADDR_HISTORY, CLEAN_OTHER
};

//����Ļ�������
enum DEL_CACHE_TYPE
{
	FILES = 0, COOKIES
};

//�ɹ����������
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
// CleanSpace �Ի���

class CleanSpace : public CDialogEx
{
	DECLARE_DYNAMIC(CleanSpace)

public:
	CleanSpace(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CleanSpace();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	VOID CleanInternetTemp();			/**����Interner��ʱ�ļ�*/
	VOID CleanInternetCookie();			/**����Internet Cookie*/
	VOID CleanAddrBarHistory();			/**�����ַ����ʷ��¼*/

	VOID CleanPasswordHistory();		/**���������¼*/
	VOID CleanFavoriteContent();		/**�����ղؼ�����*/
	VOID CleanRASHistory();				/**����RAS��¼*/
	VOID CleanSystemTemp();				/**����ϵͳ��ʱ�ļ���*/
	VOID CleanRubbishStation();			/**������������վ*/	
	VOID CleanRunHistory();				/**�������м�¼*/
	VOID CleanDocumentHistory();		/**�����ĵ���¼*/
	VOID CleanPrevUserHistory();		/**�����ϴ��û���¼��¼*/
	VOID CleanFileFindHistory();		/**�����ļ����Ҽ�¼*/
	VOID CleanCompFindHisroty();		/**������Ҽ������¼*/
	VOID CleanNetContectHistory();		/**����������¼*/
	VOID CleanRemoteHistory();			/**����Զ�����Ӽ�¼*/
	VOID CleanBrowseAddrHistory();		/**���������ַ��¼*/
private:

	BOOL DeleteUrlCache(DEL_CACHE_TYPE type);				/**���Url����*/
	BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE, 
						BOOL bWipeIndexDat = FALSE);		/**���һ��Ŀ¼*/
	BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile);			/**�����ļ�����*/

	void WriteChar(int nHeight,int  nWidth, int nEscapement,int nOrientation,
		int x,int y,CString context,CString fontStyle=L"����",BYTE FontQuality=CLEARTYPE_QUALITY);	//��������
	void CleanInterface();		//�����������
	void MovebkPic(	int BkgroundPic);			//�ƶ�����ͼ

};
