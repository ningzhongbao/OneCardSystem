#pragma once
#include "FaceGroupAdd.h"

#include "stdafx.h"
#include "afxwin.h"

// CFaceOper 对话框

class CFaceOper : public CDialogEx
{
	DECLARE_DYNAMIC(CFaceOper)

public:
	CFaceOper(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFaceOper();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAUPFACEPICTURE };
#endif

public:
	BOOL AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank);

public:
	BOOL InitLoginParams();//初始化登录参数
	BOOL LogIn();  //登录
	BOOL LogOut();

	/////////////////人脸库//////////////////////
	BOOL CheckLoginOk();
	BOOL RefreshFaceGroup();//刷新人脸库
	BOOL ReCreateFaceGroupArray();
	void DeleteFaceGroupArray();
	STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);
	BOOL DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace);

	//界面操作
	BOOL UI_RefreshFaceGroup();
	BOOL UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo);

	BOOL UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson);

public:
	LLONG m_lLoginID;
	int	m_nError;

	CString     m_Str_Ip; //ip
	INT 	    m_int_port; //端口
	CString 	m_Str_User; //用户名
	CString 	m_Str_Pwd; //密码
						   // 人脸库信息
	STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;

	/////////////////////////////////////////////////////////
	// 页码信息
	CString m_static_string_person_page;
	// 人脸组ID
	UINT m_edit_uint_group_id;
	// 人脸组名称
	CString m_edit_string_group_name;
	// 人脸组别名
	CString m_edit_string_group_alias;
	// 人脸库创建时间
	CString m_edit_string_create_time;
	// 人脸库使能
	int m_edit_int_group_enable;
	// 人脸库查询阈值
	CString m_edit_string_group_search_threshold;
	// 人脸库 TopRank
	unsigned int m_edit_int_group_top_rank;
	// 人脸库GUID
	CString m_edit_string_group_guid;
	// 人脸库当前人员页码
	CString m_edit_person_page;
	// 人员 ID
	UINT m_edit_uint_person_id;
	// 人员名称
	CString m_edit_string_person_name;
	// 人员生日
	CString m_edit_string_person_birth;
	// 人员性别
	CString m_edit_string_person_sex;
	// 人员证件类型
	CString m_edit_string_person_certificate_type;
	// 人员证件号 ID
	CString m_edit_string_person_certificate_id;
	// 国别
	CString m_edit_string_person_country;
	// 省籍
	CString m_edit_string_person_province;
	// 所在城市
	CString m_edit_string_person_city;
	// 人员人脸图1标识符
	CString m_edit_string_person_1_img_facetoken;
	// 人员人脸图2标识符
	CString m_edit_string_person_2_img_facetoken;
	// 人员人脸图3标识符
	CString m_edit_string_person_3_img_facetoken;
	CStatic m_static_image_1;
	CStatic m_static_image_2;
	CStatic m_static_image_3;
	/////////////////////////////////////////////////////////////
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAddFaceGroup();
	afx_msg void OnBnClickedBtnRefreshFaceGroup();
	CListBox m_list_face_group;
	afx_msg void OnBnClickedBtnDeleteFaceGroup();
};
