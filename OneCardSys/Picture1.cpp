// Picture1.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "Picture1.h"
#include "afxdialogex.h"


// CPicture1 对话框

IMPLEMENT_DYNAMIC(CPicture1, CDialogEx)

CPicture1::CPicture1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PERSON_INFO, pParent)
	, m_Image_String(_T(""))
	, m_Name(_T(""))
	, m_IDCard(_T(""))
	, m_XQName(_T(""))
	, m_DyId(_T(""))
	, m_LcId(_T(""))
	, m_LcIdd(_T(""))
	, m_ShId(_T(""))
{

}

CPicture1::~CPicture1()
{
}

void CPicture1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_Image);
	DDX_Text(pDX, IDC_Face_Path, m_Image_String);
	DDX_Text(pDX, IDC_Name, m_Name);
	DDX_Text(pDX, IDC_ID, m_IDCard);
	DDX_Text(pDX, IDC_XQName, m_XQName);
	DDX_Text(pDX, IDC_Ele, m_DyId);
	DDX_Text(pDX, IDC_LD, m_LcId);
	DDX_Text(pDX, IDC_CH, m_LcIdd);
	DDX_Text(pDX, IDC_SH, m_ShId);
}


BEGIN_MESSAGE_MAP(CPicture1, CDialogEx)
	ON_BN_CLICKED(IDC_Add_PerFace, &CPicture1::OnBnClickedAddPerface)
	ON_BN_CLICKED(IDC_Dele_PerFace, &CPicture1::OnBnClickedDelePerface)
	ON_BN_CLICKED(IDC_Cannel, &CPicture1::OnBnClickedCannel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IDOK, &CPicture1::OnBnClickedIdok)
END_MESSAGE_MAP()


// CPicture1 消息处理程序


void _ShowCtrlImage(CStatic* imageCtrl, CString strImagePath, CString strExt)
{
	if (strImagePath.IsEmpty() || -1 == strImagePath.Find(strExt.GetBuffer(0)))
		return;

	CImage image;
	image.Load(strImagePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	imageCtrl->GetClientRect(rectControl);

	CDC *pDc = imageCtrl->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	imageCtrl->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
	//image.Draw(pDc->m_hDC, rectPicture);                //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	imageCtrl->ReleaseDC(pDc);
}


CString _ShowFileDialog()
{
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0,
		_T("image Files(*.jpg)|*.JPG|All Files (*.*) |*.*"), NULL);
	fileDlg.DoModal();
	return fileDlg.GetPathName();
}

void CPicture1::OnPaint()
{
	CPaintDC dc(this);

	_ShowCtrlImage(&m_Image, m_image_path, CString(".jpg"));

}

void CPicture1::OnBnClickedAddPerface()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_image_path = _ShowFileDialog();

	m_Image_String = m_image_path;


	UpdateData(FALSE);

	Invalidate(TRUE);
}


void CPicture1::OnBnClickedDelePerface()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_image_path = "";
	m_Image_String = m_image_path;

	UpdateData(FALSE);

	Invalidate(TRUE);
}


void CPicture1::OnBnClickedCannel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CPicture1::OnBnClickedIdok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	MessageBox(m_Name.GetBuffer(0), NULL, MB_OK);
}
