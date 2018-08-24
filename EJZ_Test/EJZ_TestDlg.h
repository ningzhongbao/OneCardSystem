
// EJZ_TestDlg.h : 头文件
//

#pragma once


// CEJZ_TestDlg 对话框
class CEJZ_TestDlg : public CDialogEx
{
// 构造
public:
	CEJZ_TestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EJZ_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	HBITMAP m_hPhotoBitmap;
	char * m_pBMPBuffer;
	
	VARIANT            varBLOB;
	SAFEARRAY        *psa;

	DWORD m_nFileLen;
public:
	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedButton2();
};
