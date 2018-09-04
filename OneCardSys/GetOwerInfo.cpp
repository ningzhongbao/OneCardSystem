// GetOwerInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetOwerInfo.h"
#include "afxdialogex.h"


// CGetOwerInfo 对话框

IMPLEMENT_DYNAMIC(CGetOwerInfo, CDialogEx)

CGetOwerInfo::CGetOwerInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GetOwerInfo, pParent)
{

}

CGetOwerInfo::~CGetOwerInfo()
{
}

void CGetOwerInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetOwerInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetOwerInfo::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGetOwerInfo 消息处理程序


void CGetOwerInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
