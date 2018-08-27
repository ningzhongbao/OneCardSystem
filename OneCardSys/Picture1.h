#pragma once
#include "afxwin.h"


// CPicture1 对话框
#include <vector>
#include "Protocol.h"
#include "afxcmn.h"
using namespace std;

class CPicture1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPicture1)

public:
	CPicture1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPicture1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	CString				m_image_path;			//图像路径 
	DWORD				m_nFileLen;			//文件长度
	char				*pBufImgDate;      //存储二进制图片数据
	CString				m_csFileName;      //路径文件名
	vector<CString>		m_FileList;        //文件名
	CString				csDirParth;        //
	CString				m_AllPath;				//listbox选择的路径；
	OPEN_DOOR_PROTO     m_Protocol;     //协议包
public:
	char *LoadImaData(CString imagPath);     //获取图片数据 
	void GetFileFromDir(CString csDirPath);  //获取图片路径
	void JxFileName(CString jpgName);
	void Ui_Show_Info(CString filename);

public:	
	CStatic m_Image;
	afx_msg void OnBnClickedAddPerface();
	afx_msg void OnBnClickedDelePerface();
	CString m_Image_String;
	afx_msg void OnBnClickedCannel();
	CString m_Name;
	CString m_IDCard;
	CString m_DyId;
	CString m_LcId;
	CString m_LcIdd;
	CString m_ShId;
	afx_msg void OnBnClickedIdok();
	afx_msg void OnBnClickedOpenFacepath();
	CListBox m_ListBox;
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedDeleList();
};
