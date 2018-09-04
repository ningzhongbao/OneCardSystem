
// OneCardSysDlg.h : 头文件
//

#pragma once
#include "SysMainUi.h"

// COneCardSysDlg 对话框
class COneCardSysDlg : public CDialogEx
{
// 构造
public:
	COneCardSysDlg(CWnd* pParent = NULL);	// 标准构造函数
	~COneCardSysDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ONECARDSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CPropertySheet	m_sheet;	 // 属性页，用于容纳下面4个标签（页面）
	CPicture1       m_Picture;   //显示添加人脸信息属性页
	

// 实现
public:

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:	
	CString m_strUser;
	CString m_strPwd;
	afx_msg void OnBnClickedBtnlogin();
	afx_msg void OnBnClickedBtncannel();
};
