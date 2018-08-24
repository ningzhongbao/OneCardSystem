
// EJZ_TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EJZ_Test.h"
#include "EJZ_TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEJZ_TestDlg 对话框



CEJZ_TestDlg::CEJZ_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EJZ_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEJZ_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEJZ_TestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CEJZ_TestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CEJZ_TestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CEJZ_TestDlg 消息处理程序

BOOL CEJZ_TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEJZ_TestDlg::OnPaint()
{
	InvalidateRect(NULL, FALSE);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEJZ_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEJZ_TestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog FileDlg(TRUE, _T("BMP"), NULL,        //定义文件对话框
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("位图文件(*.BMP)|*.BMP||"));
	
	//CFileDialog FileDlg(TRUE, _T("JPG"), NULL,        //定义文件对话框
	//	OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("位图文件(*.JPG)|*.JPG||"));

	if (FileDlg.DoModal() != IDOK)            //打开文件对话框
		return;
	CString pathname = FileDlg.GetPathName();//获取选中文件的路径
	CFile file;                        //定义一个文件变量
	if (!file.Open(pathname, CFile::modeRead | CFile::typeBinary))//以制度的方式打开文件
		return;
	m_nFileLen = file.GetLength();//获取文件的长度
	m_pBMPBuffer = new char[m_nFileLen + 1];//开辟符数组
	if (!m_pBMPBuffer)            //如果控件不够大
		return;
	if (file.Read(m_pBMPBuffer, m_nFileLen) != m_nFileLen)//读取文件保存在字符数组中
		return;
	char            *pBuf = m_pBMPBuffer;

	SAFEARRAYBOUND    rgsabound[1];
	if (pBuf)
	{
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = m_nFileLen;
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for (long i = 0; i < (long)m_nFileLen; i++)
			SafeArrayPutElement(psa, &i, pBuf++);
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
	}
}


void CEJZ_TestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_hPhotoBitmap)
	{
		DeleteObject(m_hPhotoBitmap);
		m_hPhotoBitmap = NULL;
	}
	if (m_pBMPBuffer)
	{
		delete m_pBMPBuffer;
		m_pBMPBuffer = NULL;
	}
	//上面代码是为了清除以前的图像

	char *pBuff = NULL;//用于存放位图的内存空间
	_variant_t TheValue;//存储读出来的数据
	TheValue = varBLOB;


	if (varBLOB.vt == (VT_ARRAY | VT_UI1))
	{
		pBuff = new char[m_nFileLen + 1];
		if (pBuff)
		{
			char *buff = NULL;
			SafeArrayAccessData(TheValue.parray, (void**)&buff);//把位图数据放到buff中去
			memcpy(pBuff, buff, m_nFileLen);//把位图数据放到pBuff中

			SafeArrayUnaccessData(TheValue.parray);//释放

			m_pBMPBuffer = new char[m_nFileLen + 1];//开辟符数组
			memcpy(m_pBMPBuffer, pBuff, m_nFileLen);

			//CImage image;
			//image.Load(m_pBMPBuffer);
			//	//然后找到显示的地方 比如一个pic控件，ID为ID_PIC 则

			//	CStatic idc = CStatic)GetDlgItem(IDC_PIC);
			//CRect m_picRect1;
			//this->GetClientRect(&m_picRect1);
			//CDC* cd = this->GetWindowDC();
			//int width = image.GetWidth();
			//int height = image.GetHeight();
			//SetStretchBltMode(cd->m_hDC, HALFTONE);
			//image.Draw(cd->m_hDC, m_picRect1);
			//ReleaseDC(cd);

			//将位图内存数据PBuff转为HBITMAP
			HBITMAP hBitmap = NULL;//定义一个HBITMAP对象，用于显示位图用
			LPSTR                hDIB, lpBuffer = m_pBMPBuffer;
			LPVOID               lpDIBBits;
			BITMAPFILEHEADER     bmfHeader;
			DWORD                bmfHeaderLen;

			//获得位图的头信息
			bmfHeaderLen = sizeof(bmfHeader);
			//strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);
			memcpy(&bmfHeader, lpBuffer, bmfHeaderLen);
			//根据获得的信息头判断是否是位图
			if (bmfHeader.bfType != (*(WORD*)"BM"))
			{
				AfxMessageBox(_T("this is not bitmap!"));
				return;
			}
			//获取位图数据
			hDIB = lpBuffer + bmfHeaderLen;//将指针移动到文件头的后面
			BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB;
			BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB;
			lpDIBBits = (lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;  //偏移字节数

																			   //创建位图
			CClientDC dc(this);
			hBitmap = CreateDIBitmap(dc.m_hDC, &bmiHeader,
				CBM_INIT, lpDIBBits, &bmInfo, DIB_RGB_COLORS);

			//显示位图
			CBitmap bmp;                            //定义位图变量
			bmp.Attach(hBitmap);
			BITMAP bm;                                //定义一个位图结构
			bmp.GetBitmap(&bm);
			CDC dcMem;
			dcMem.CreateCompatibleDC(GetDC());        //创建一个兼容的DC
			CBitmap *poldBitmap = (CBitmap*)dcMem.SelectObject(bmp); //将位图选入设备环境类
			CRect lRect;                            //定义一个区域
			CStatic *pstatic = (CStatic*)GetDlgItem(IDC_Picture);
			pstatic->GetClientRect(&lRect);            //获取控件的客户区域
			lRect.NormalizeRect();

			pstatic->GetDC()->StretchBlt(lRect.left, lRect.top, lRect.Width(), lRect.Height(),
				&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); //显示位图
			dcMem.SelectObject(&poldBitmap); //将原有的句柄选入设备环境
			bmp.DeleteObject();



		}
	}

}