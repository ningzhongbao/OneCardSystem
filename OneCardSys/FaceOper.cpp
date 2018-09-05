// FaceOper.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "FaceOper.h"
#include "afxdialogex.h"


// CFaceOper 对话框

IMPLEMENT_DYNAMIC(CFaceOper, CDialogEx)

CFaceOper::CFaceOper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAUPFACEPICTURE, pParent)
	, m_Name_ID(_T(""))
{
	InitLoginParams(); //初始化各项参数
	
	m_pfaceGroupArray = NULL;
	LogIn();//登录	

	m_person_county = _T("中国");
	m_person_sex = _T("male");
	m_person_certificate_type = _T("身份证");
	m_person_county = _T("中国");
	m_person_birth = _T("2037-12-31");
	m_person_city = _T("武汉市");
	m_person_certificate_id = _T("00000000000000");
	m_person_province = _T("湖北省");

}

CFaceOper::~CFaceOper()
{
	LogOut();
}

void CFaceOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_face_group);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT_ID, m_Name_ID);
}


BEGIN_MESSAGE_MAP(CFaceOper, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_FACE_GROUP, &CFaceOper::OnBnClickedBtnAddFaceGroup)
	ON_BN_CLICKED(IDC_BTN_REFRESH_FACE_GROUP, &CFaceOper::OnBnClickedBtnRefreshFaceGroup)
	ON_BN_CLICKED(IDC_BTN_DELETE_FACE_GROUP, &CFaceOper::OnBnClickedBtnDeleteFaceGroup)
	ON_BN_CLICKED(IDC_BTN_PERSON_ADD, &CFaceOper::OnBnClickedBtnPersonAdd)
	ON_BN_CLICKED(IDC_Btn_UP, &CFaceOper::OnBnClickedBtnUp)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////
static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
{
	// TODO: 
	CFaceOper* pDlg = (CFaceOper*)dwUser;
	pDlg->m_lLoginID = 0;
}

BOOL CFaceOper::InitLoginParams()
{
	m_lLoginID = 0;
	m_Str_Ip = "192.168.7.2";
	m_int_port = 3000;
	m_Str_User = "admin";
	m_Str_Pwd = "admin123";
	
	Net_Init(disconnect_callback, (LDWORD)(void*)this); //初始化sdk库

	return TRUE;
}

BOOL CFaceOper::LogIn()
{
	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
		m_Str_User.GetBuffer(), m_Str_Pwd.GetBuffer(), NULL, &m_nError); //登陆

	if (0 >= m_lLoginID)
	{
		MessageBox(_T("人脸识别功能登录失败，重启软件"), _T("登录提示..."), MB_ICONHAND);

		return FALSE;
	}

	return TRUE;
}

BOOL CFaceOper::LogOut()
{
	if (m_lLoginID)
	{
		if (Net_LogoutDevice(m_lLoginID))
		{
			m_lLoginID = 0;
			// 清理网络库资源
			Net_Exit();

			return TRUE;
		}
	}

	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////

// CFaceOper 消息处理程序


void CFaceOper::OnBnClickedBtnAddFaceGroup()
{
	// TODO: 在此添加控件通知处理程序代码	
	CFaceGroupAdd dlgFGAdd;
	if (IDOK != dlgFGAdd.DoModal())
		return;
	// 将新组添加到列表
	CString strAlias = dlgFGAdd.GetAliasString();
	BOOL bEnable = dlgFGAdd.GetFaceGroupEnable();
	float fSearchThreshold = dlgFGAdd.GetSearchThreshold();
	UINT nTopRank = dlgFGAdd.GetTopRank();

	if (TRUE != AddFaceGroup(strAlias, bEnable, fSearchThreshold, nTopRank))
	{
		MessageBox("添加人脸库失败.");
		return;
	}
	else
	{
		MessageBox(_T("添加成功"));
	}
}


BOOL CFaceOper::AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank)
{
	STU_FACE_GROUP_CREATE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_CREATE_OUT_PARAM stOutParam = { 0 };

	stInParam.bEnable = bEnable;
	sprintf(stInParam.szAlias, "%s", strAlias.GetBuffer(0));
	strAlias.ReleaseBuffer();
	stInParam.fSearchThreshold = fSearchThreshold;
	stInParam.nTopRank = nTopRank;

	if (TRUE != Net_CreateFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox(_T("错误，创建人脸库错误.\n"));

		return FALSE;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////
// 人脸库 & 人脸操作
void CFaceOper::DeleteFaceGroupArray()
{
	if (NULL != m_pfaceGroupArray) {
		delete m_pfaceGroupArray;
		m_pfaceGroupArray = NULL;
	}
}


BOOL CFaceOper::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("还未登录！"), "", MB_OK);
	return FALSE;
}

BOOL CFaceOper::ReCreateFaceGroupArray()
{
	DeleteFaceGroupArray();
	m_pfaceGroupArray = new STU_FACE_GROUP_ARRAY_INFO;
	if (NULL == m_pfaceGroupArray)
	{
		return FALSE;
	}
	memset(m_pfaceGroupArray, 0x00, sizeof(STU_FACE_GROUP_ARRAY_INFO));
	return TRUE;
}

BOOL CFaceOper::RefreshFaceGroup()
{
	if (TRUE != ReCreateFaceGroupArray()) 
	{
		MessageBox(_T("ReCreateFaceGroupArray人脸库错误"), NULL, MB_OK);		
		return FALSE;
	}

	if (TRUE != Net_GetAllFaceGroups(m_lLoginID, m_pfaceGroupArray))
	{
		MessageBox(_T("获取人脸库错误"), NULL, MB_OK);
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////

void CFaceOper::OnBnClickedBtnRefreshFaceGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if (TRUE != CheckLoginOk())
		return;

	if (TRUE != RefreshFaceGroup())
		return;

	UI_RefreshFaceGroup();
	//UI_RefreshCurFaceInfo(NULL);
	//UI_RefreshCurPerson(NULL);
}


////////////////////////////////////////////////////////////////////////////////////////////
// 界面操作
BOOL CFaceOper::UI_RefreshFaceGroup()
{
	m_list_face_group.ResetContent();
	for (int i = 0; i < m_pfaceGroupArray->nFaceGroupNum; i++)
	{
		CString strGroupInfo = "";
		strGroupInfo.Format("%d-%u-%s", i, m_pfaceGroupArray->stFaceGroupArr[i].nGroupID,
			m_pfaceGroupArray->stFaceGroupArr[i].szGroupName);
		m_list_face_group.AddString(strGroupInfo.GetBuffer(0));
		strGroupInfo.ReleaseBuffer();
	}
	m_list_face_group.SetCurSel(-1);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo)
{
	if (NULL == pCurFaceInfo)
	{
		m_edit_uint_group_id = 0;
		m_edit_string_group_name = "";
		m_edit_string_group_alias = "";
		m_edit_string_create_time = "";
		m_edit_int_group_enable = 0;
		m_edit_int_group_top_rank = 0;
		m_edit_string_group_guid = "";
	}
	else
	{
		m_edit_uint_group_id = pCurFaceInfo->nGroupID;
		m_edit_string_group_name.Format("%s", pCurFaceInfo->szGroupName);
		m_edit_string_group_alias.Format("%s", pCurFaceInfo->szAlias);
		m_edit_string_create_time.Format("%04d-%02d-%02d %02d:%02d:%02d",
			pCurFaceInfo->stCreateTime.dwYear, pCurFaceInfo->stCreateTime.dwMonth, pCurFaceInfo->stCreateTime.dwDay,
			pCurFaceInfo->stCreateTime.dwHour, pCurFaceInfo->stCreateTime.dwMinute, pCurFaceInfo->stCreateTime.dwSecond);
		m_edit_int_group_enable = pCurFaceInfo->bEnable;
		m_edit_string_group_search_threshold.Format("%0.2f", pCurFaceInfo->fSearchThreshold);
		m_edit_int_group_top_rank = pCurFaceInfo->nTopRank;
		m_edit_string_group_guid.Format("%s", pCurFaceInfo->szGUID);
	}

	UpdateData(FALSE);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson)
{
	/*if (!m_person_face_image_1.IsEmpty())
		DeleteFile(m_person_face_image_1.GetBuffer(0));
	if (!m_person_face_image_2.IsEmpty())
		DeleteFile(m_person_face_image_2.GetBuffer(0));
	if (!m_person_face_image_3.IsEmpty())
		DeleteFile(m_person_face_image_3.GetBuffer(0));
*/
	if (NULL == pCurPerson)
	{
		m_edit_uint_person_id = 0;
		m_edit_string_person_name = "";
		m_edit_string_person_birth = "";
		m_edit_string_person_sex = "";
		m_edit_string_person_certificate_type = "";
		m_edit_string_person_certificate_id = "";
		m_edit_string_person_country = "";
		m_edit_string_person_province = "";
		m_edit_string_person_city = "";

	}
	else
	{
		m_edit_uint_person_id = pCurPerson->stPersonInfo.nPersonID;
		m_edit_string_person_name.Format("%s", pCurPerson->stPersonInfo.szName);
		m_edit_string_person_birth.Format("%04d-%02d-%02d",
			pCurPerson->stPersonInfo.stBirthday.dwYear, pCurPerson->stPersonInfo.stBirthday.dwMonth, pCurPerson->stPersonInfo.stBirthday.dwDay);
		m_edit_string_person_sex = pCurPerson->stPersonInfo.emSexType == SEX_TYPE_MALE ? "male" :
			pCurPerson->stPersonInfo.emSexType == SEX_TYPE_FEMALE ? "female" : "unknown";
		m_edit_string_person_certificate_type.Format("%s", pCurPerson->stPersonInfo.szCertificateType);
		m_edit_string_person_certificate_id.Format("%s", pCurPerson->stPersonInfo.szID);
		m_edit_string_person_country.Format("%s", pCurPerson->stPersonInfo.szCountry);
		m_edit_string_person_province.Format("%s", pCurPerson->stPersonInfo.szProvince);
		m_edit_string_person_city.Format("%s", pCurPerson->stPersonInfo.szCity);

		m_edit_string_person_1_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[0].szFaceToken);
		m_edit_string_person_2_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[1].szFaceToken);
		m_edit_string_person_3_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[2].szFaceToken);

		// 下载图片到本地

		/*for (int i = 0; i < pCurPerson->nFaceImageCount; i++)
		{
			CString strPath = "";
			strPath.Format("C:\\Tmp\\face_image_tmp_%d.jpg", i + 1);
			if (TRUE == GetFaceImage(i, strPath))
			{
				if (0 == i)
					m_person_face_image_1 = strPath;
				else if (1 == i)
					m_person_face_image_2 = strPath;
				else if (2 == i)
					m_person_face_image_3 = strPath;
			}
		}*/
	}

	UpdateData(FALSE);
	Invalidate(TRUE);
	return TRUE;
}

STU_FACE_GROUP_INFO* CFaceOper::GetCurFaceGroupInfo(int nIndex)
{
	if (0 > nIndex || MAX_FACE_GROUP_NUM <= nIndex)
		return NULL;
	if (NULL == m_pfaceGroupArray || 0 == m_pfaceGroupArray->nFaceGroupNum)
		return NULL;
	return &m_pfaceGroupArray->stFaceGroupArr[nIndex];
}

BOOL CFaceOper::DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace)
{
	STU_FACE_GROUP_DELETE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_DELETE_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	stInParam.bDelBindFace = bDelBindFace;

	if (TRUE != Net_DeleteFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		CString str;
		str.Format("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n",
			nGroupID, bDelBindFace);

		MessageBox(str, NULL, MB_OK);
		str.ReleaseBuffer(0);
		/*_OutputDebugString("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n",
			nGroupID, bDelBindFace);*/

		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////

void CFaceOper::OnBnClickedBtnDeleteFaceGroup()
{
	// TODO: 在此添加控件通知处理程序代码
	if (TRUE != CheckLoginOk())
		return;

	// 是否选中组
	int nIndex = m_list_face_group.GetCurSel();
	if (nIndex < 0) {
		MessageBox(_T("未选中人脸组！"), "", MB_OK);
		return;
	}

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox("获取人脸库信息失败！");
		return;
	}

	BOOL bDelBindFace = FALSE;
	if (IDYES == MessageBox(_T("是否删除人脸库绑定的所有人脸图片？") , "", MB_YESNO))
	{
		bDelBindFace = TRUE;
	}

	if (TRUE != DeleteFaceGroup(pCurFaceGroup->nGroupID, bDelBindFace))
	{
		MessageBox(_T("删除人脸库失败，请刷新人脸库！"));
	}

	// 都刷新一下
	RefreshFaceGroup();
	UI_RefreshFaceGroup();
	UI_RefreshCurFaceInfo(NULL);
}


//清空数据
void CFaceOper::ClearData()
{
	if (!m_FileList.empty())
	{
		m_FileList.clear();
		vector<CString>().swap(m_FileList);
	}	
}


void CFaceOper::OnBnClickedBtnPersonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (TRUE != CheckLoginOk())
		return;
	
	ClearData();  //情况vector

	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);

	//获取文件名
	GetFileFromDir(csDirParth);

	if (m_FileList.empty())
	{
		return;
	}
	
	CString strTmp = m_FileList.front();
	int posEnd = strTmp.ReverseFind('.');
	m_Name_ID = strTmp.Left(posEnd);	

	CString strPath;
	strPath = csDirParth + "\\" + m_FileList.front();
	Ui_Show(strPath);

	UpdateData(FALSE);
}

///////////////////////Ui_Show_Begin//////////////////////////////////////////////////////
void CFaceOper::Ui_Show(CString g_strPictureShow)
{
	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
	{
		AfxMessageBox(_T("不是jpg文件")); 
		return;
	}		

	CImage image;
	image.Load(g_strPictureShow);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_Picture)->GetClientRect(rectControl);

	CDC *pDc = (&m_Picture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_Picture)->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	(&m_Picture)->ReleaseDC(pDc);

	UpdateData(FALSE);
}

void CFaceOper::GetFileFromDir(CString csDirPath)
{
	csDirPath += "\\*.jpg";

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];

	//获取第一个文件名
	file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	m_FileList.push_back(fileData.cFileName);

	//根据第一个文件名，向下获取
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		m_FileList.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}
//////////////////////////ui_end///////////////////////////////////////////////////

//////////////////////////双传开始///////////////////////////////////////////////////
void CFaceOper::OnBnClickedBtnUp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (TRUE != CheckLoginOk())
		return;

	int nIndex = CurFaceGroupIndex();
	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox(_T("请选择一个人脸组！"));
		return;
	}

	for (int i = 0; i < m_FileList.size(); i++)
	{	
		//初始化
		memset(&m_stPersonInfo, 0x00, sizeof(STU_PERSON_INFO));		
		memset(m_stPersonInfo.szName, NULL, 128);
		char szNewName[128] = { 0 };
		m_Name_ID = "";

		CString m_person_name = m_FileList.at(i);
		int posEnd = m_person_name.ReverseFind('.');
		m_Name_ID = m_person_name.Left(posEnd);

		m_person_certificate_id = m_person_name.Left(posEnd);//身份证也是唯一id
		//
		memcpy(m_stPersonInfo.szName, m_Name_ID.GetBuffer(0), m_Name_ID.GetLength());		

		CString strPath;
		strPath = csDirParth + "\\" + m_FileList.at(i);
		Ui_Show(strPath);		 

			
		sscanf(m_person_birth.GetBuffer(0), "%04d-%02d-%02d",
			&m_stPersonInfo.stBirthday.dwYear, &m_stPersonInfo.stBirthday.dwMonth, &m_stPersonInfo.stBirthday.dwDay);
		m_person_birth.ReleaseBuffer();

		if (m_person_sex == "male")
			m_stPersonInfo.emSexType = SEX_TYPE_MALE;
		else if (m_person_sex == "female")
			m_stPersonInfo.emSexType = SEX_TYPE_FEMALE;
		else
			m_stPersonInfo.emSexType = SEX_TYPE_UNKNOWN;

		memcpy(m_stPersonInfo.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
		m_person_certificate_type.ReleaseBuffer();


		/*	CTime tm;
			tm = CTime::GetCurrentTime();

			m_person_certificate_id = tm.Format("111%y%m%d%H%M%S");*/
		
		memcpy(m_stPersonInfo.szID, m_person_certificate_id.GetBuffer(0), m_person_certificate_id.GetLength());
		m_person_certificate_id.ReleaseBuffer();


		memcpy(m_stPersonInfo.szCountry, m_person_county.GetBuffer(0), m_person_county.GetLength());
		m_person_county.ReleaseBuffer();


		memcpy(m_stPersonInfo.szProvince, m_person_province.GetBuffer(0), m_person_province.GetLength());
		m_person_province.ReleaseBuffer();

		memcpy(m_stPersonInfo.szCity, m_person_city.GetBuffer(0), m_person_city.GetLength());
		m_person_city.ReleaseBuffer();


		//// 添加人员之前需要校验会否重名
		if (TRUE != CheckNameSuffix(m_stPersonInfo.szName, szNewName, 128))
		{
			MessageBox("重名校验失败！");
			return;
		}
		// 赋值名字
		memcpy(m_stPersonInfo.szName, szNewName, strlen(szNewName));

		std::vector<CString> vecImages;
		if (!strPath.IsEmpty())
			vecImages.push_back(strPath);

		if (TRUE != AddPersonInfo(pCurFaceGroup->nGroupID, &m_stPersonInfo, vecImages))
		{
			//MessageBox("添加人员信息失败！");
			continue;
		}
		else
		{
			AfxMessageBox("success.\n");
		}

		Sleep(100);
		UpdateData(FALSE);
		m_Name_ID.ReleaseBuffer();
		InvalidateRect(NULL, FALSE);
	}	
	
}


BOOL CFaceOper::AddPersonInfo(unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages)
{
	if (NULL == pstPersonInfo)
		return FALSE;

	STU_FACE_ADD_IN_PARAM stInParam = { 0 };
	STU_FACE_ADD_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	
	stInParam.nImageCount = vecImages.size();
	memcpy(&stInParam.stPersonInfo, pstPersonInfo, sizeof(STU_PERSON_INFO));

	CString strImageFiles = "";
	std::vector<CString>::iterator iter = vecImages.begin();
	while (iter != vecImages.end())
	{
		strImageFiles.Append(*iter);
		strImageFiles.AppendChar('|');  // 图片路径以 “|” 分隔
		iter++;
	}
	strImageFiles = strImageFiles.TrimRight('|');

	/*stInParam.lpszImageFiles = new char[vecImages.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, vecImages.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, vecImages.GetBuffer(0), vecImages.GetLength());
*/
	stInParam.lpszImageFiles = new char[strImageFiles.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, strImageFiles.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, strImageFiles.GetBuffer(0), strImageFiles.GetLength());
	

	if (TRUE != Net_AddPersonInfo(m_lLoginID, &stInParam, &stOutParam))
	{
		//AfxMessageBox("Error | AddPersonInfo fail.\n");
		delete[] stInParam.lpszImageFiles;
		return FALSE;
	}

	delete[] stInParam.lpszImageFiles;
	return TRUE;
}

BOOL CFaceOper::CheckNameSuffix(IN const char* lpszName, OUT char* lpszNewName, int nNewNameLen)
{
	if (NULL == lpszName || NULL == lpszNewName)
	{
		AfxMessageBox("Error | Person page error.\n");
		return FALSE;
	}

	memset(lpszNewName, 0x00, nNewNameLen);

	STU_PERSON_NAME_CHECK_IN_PARAM stInParam = { 0 };
	STU_PERSON_NAME_CHECK_OUT_PARAM stOutParam = { 0 };
	memcpy(stInParam.szName, lpszName, strlen(lpszName));

	if (TRUE != Net_CheckPersonNameSuffix(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");

		return FALSE;
	}

	if (0 == stOutParam.nSuffix)
	{
		memcpy(lpszNewName, lpszName, strlen(lpszName));
	}
	else
	{
		sprintf_s(lpszNewName, nNewNameLen, "%s%d", lpszName, stOutParam.nSuffix);
	}

	return TRUE;
}




//////////////////////////上传结束///////////////////////////////////////////////////