#pragma once
#include "Picture1.h"
#include "GetInfoPer.h"
#include "GetOwerInfo.h"
#include "FaceOper.h"

// CSysMainUi 对话框

class CSysMainUi : public CDialogEx
{
	DECLARE_DYNAMIC(CSysMainUi)

public:
	CSysMainUi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysMainUi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAMAINUI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 实现
public:
	CGetInfoPer *m_pPerDlg; //截取人脸图片
	CPicture1   *m_pPicDlg; //人脸上传
	CGetOwerInfo*m_OwenInfo;//采集业主信息对话框
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGetperinfo();
	afx_msg void OnBnClickedBtnperinfo();
	afx_msg void OnClose();
	afx_msg void OnBnClickedGetoweinfo();
	afx_msg void OnBnClickedBtnsendowerinfo();
	afx_msg void OnBnClickedBtnfaceoper();
};
