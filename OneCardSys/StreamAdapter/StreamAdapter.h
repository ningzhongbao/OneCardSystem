#ifndef _SA_STREAM_ADAPTER_1_H
#define _SA_STREAM_ADAPTER_1_H

#define IN  
#define OUT 

#if (defined(WIN32) || defined(WIN64))
#ifdef SA_API_EXPORTS
	#define SA_API __declspec(dllexport)
#elif defined(SA_API_IMPORTS)
	#define SA_API __declspec(dllimport)
#else
	#define SA_API 
#endif
	#define CALLMETHOD __stdcall
#else 
	#define SA_API
	#define CALLMETHOD
#endif

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

// �ӿڷ���ֵ
enum SA_RESULT
{
    SA_SUCCESS = 0,                     // �ɹ�
    SA_ERROR_INVALID_HANDLE,            // ��Ч���
    SA_ERROR_FILE_TYPE_NOSUPPORT,       // �ļ����Ͳ�֧��
    SA_ERROR_STREAM_NOSUPPORT,          // �����Ͳ�֧��
    SA_ERROR_THREAD_CREATE_FAILED,      // �̴߳���ʧ��
    SA_ERROR_THREAD_CLOSE_FAILED,       // �̹߳ر�ʧ��
    SA_ERROR_PARAMETER,                 // ��������
    SA_ERROR_INDEX_OUTOFRANGE,	        // ����������Χ
    SA_ERROR_FILE_SIZE_ZERO,			// �ļ���СΪ0
    SA_ERROR_BAD_FORMATTED,     	    // �ļ���ʽ����
    SA_ERROR_FILE_READ,	                // ��ȡ�ļ�ʧ��
    SA_ERROR_FILE_OPEN,                 // ���ļ�ʧ��
    SA_ERROR_BUFFER_OVERFLOW,           // �ڲ����������
    SA_ERROR_SYSTEM_OUT_OF_MEMORY,      // ϵͳ�ڴ治��
    SA_ERROR_LIST_EMPTY,                // �б�Ϊ��
	SA_ERROR_UNGET_STREAM_TYPE,			// δ��ȡ����������
	SA_ERROR_EMPTY_PTR,					// ��ָ��
};

// ֡����
enum
{
	SA_FRAME_TYPE_UNKNOWN = 0,			// ֡���Ͳ���֪
	SA_FRAME_TYPE_VIDEO,				// ֡��������Ƶ֡
	SA_FRAME_TYPE_AUDIO,				// ֡��������Ƶ֡
	SA_FRAME_TYPE_DATA					// ֡����������֡
};

// ֡������
enum
{
	SA_FRAME_SUB_TYPE_DATA_INVALID = -1,			// ������Ч

	SA_FRAME_SUB_TYPE_VIDEO_I_FRAME = 0,			// I֡
	SA_FRAME_SUB_TYPE_VIDEO_P_FRAME,				// P֡
	SA_FRAME_SUB_TYPE_VIDEO_B_FRAME,				// B֡
	SA_FRAME_SUB_TYPE_VIDEO_S_FRAME,				// S֡

	SA_FRAME_SUB_TYPE_WATERMARK_TEXT,				// ˮӡ����ΪTEXT����
	SA_FRAME_SUB_TYPE_WATERMARK_JPEG,				// ˮӡ����ΪJPEG����
	SA_FRAME_SUB_TYPE_WATERMARK_BMP,				// ˮӡ����ΪBMP����

	SA_FRAME_SUB_TYPE_DATA_INTL,					// ���ܷ���֡
	SA_FRAME_SUB_TYPE_VIDEO_JPEG_FRAME,             // JPEG ֡
	SA_FRAME_SUB_TYPE_DATA_ITS,				        // ITS��Ϣ֡
	SA_FRAME_SUB_TYPE_DATA_GPS,					    // GPS
	SA_FRAME_SUB_TYPE_DATA_INTLEX,                  // ��չ���ܷ���֡
	SA_FRAME_SUB_TYPE_DATA_MOTION_FULL,				// ȫ������
	SA_FRAME_SUB_TYPE_DATA_MOTION_CARD,				// ȫ������(�忨)
	SA_FRAME_SUB_TYPE_DATA_LIGHT,					// ����
	SA_FRAME_SUB_TYPE_DATA_RAW,						// ԭʼ����
	SA_FRAME_SUB_TYPE_DATA_CHAR,					// �ַ�������Ϣ֡
	SA_FRAME_SUB_TYPE_DATA_PASSWORD,				// ������Ϣ֡
	
	SA_FRAME_SUB_TYPE_DATA_VIDEO_SYNOPSIS,			// ��ƵŨ����Ϣ
	SA_FRAME_SUB_TYPE_DATA_SDP,						// SDP��Ϣ

	SA_FRAME_SUB_TYPE_VIDEO_SMART_I_FRAME,			// smartH264 I֡
	SA_FRAME_SUB_TYPE_VIDEO_SMART_P_FRAME,			// smartH264 P֡ ֻ�ο�smart I֡
	SA_FRAME_SUB_TYPE_VIDEO_SMART_I_NORENDER,		// smartH264 I֡,ֻ���벻��ʾ������seek�͵��Ź���

	SA_FRAME_SUB_TYPE_DATA_I_INDEX = 128,           // I֡����֡
	SA_FRAME_SUB_TYPE_DATA_MOTION,                  // ��������֡
	SA_FRAME_SUB_TYPE_DATA_LABEL,                   // ��ǩ֡
	SA_FRAME_SUB_TYPE_DATA_SCREEN_CAPTION,          // ��Ļ
	SA_FRAME_SUB_TYPE_DATA_EVENT,                   // �¼�֡

	SA_FRAME_SUB_TYPE_DATA_FILEHEAD = 255,          // �ļ�ͷ֡
	SA_FRAME_SUB_TYPE_DATA_UNKOWN,                  // δ֪����
};

// ��������
enum SA_ENCODE_VIDEO_TYPE
{
	SA_ENCODE_VIDEO_UNKNOWN = 0,		// ��Ƶ�����ʽ����֪
	SA_ENCODE_VIDEO_MPEG4 ,			    // ��Ƶ�����ʽ��MPEG4
	SA_ENCODE_VIDEO_HI_H264,			// ��Ƶ�����ʽ�Ǻ�˼H264
	SA_ENCODE_VIDEO_JPEG,				// ��Ƶ�����ʽ�Ǳ�׼JPEG
	SA_ENCODE_VIDEO_DH_H264,			// ��Ƶ�����ʽ�Ǵ�����H264
	SA_ENCODE_VIDEO_JPEG2000 = 6,		// ��Ƶ�����ʽ�Ǳ�׼JPEG2000
	SA_ENCODE_VIDEO_AVS = 7,			// ��Ƶ�����ʽ�Ǳ�׼AVS
	SA_ENCODE_VIDEO_STD_H264 = 8,		// ��Ƶ�����ʽ�Ǳ�׼H264
	SA_ENCODE_VIDEO_MPEG2 = 9,          // ��Ƶ�����ʽ��MPEG2
	SA_ENCODE_VIDEO_VNC = 10,         	// ��Ƶ�����ʽ��VNC
	SA_ENCODE_VIDEO_SVAC = 11,          // ��Ƶ�����ʽ��SVAC
	SA_ENCODE_VIDEO_DH_H265 = 12,		// ��Ƶ�����ʽ��H265
	SA_ENCODE_VIDEO_RY_H264,			// ��Ƶ�����ʽ��RY����H264
	SA_ENCODE_VIDEO_RY_H265,			// ��Ƶ�����ʽ��RY����H265

	//��Ƶ����������չ����
	SA_ENCODE_VIDEO_H263 = 35,			// ��Ƶ�����ʽ��H263
	SA_ENCODE_VIDEO_PACKET,				// ��Ƶ��
	SA_ENCODE_VIDEO_MSMPEG4V1,			// ��Ƶ�����ʽ��MS MPEG4 V1
	SA_ENCODE_VIDEO_MSMPEG4V2,			// ��Ƶ�����ʽ��MS MPEG4 V2
	SA_ENCODE_VIDEO_MSMPEG4V3,			// ��Ƶ�����ʽ��MS MPEG4 V3
	SA_ENCODE_VIDEO_WMV1,				// ��Ƶ�����ʽ��MS MPEG4 V4
	SA_ENCODE_VIDEO_WMV2,				// ��Ƶ�����ʽ��MS MPEG4 V5
	SA_ENCODE_VIDEO_RV10,				// ��Ƶ�����ʽ��RV10
	SA_ENCODE_VIDEO_RV20,				// ��Ƶ�����ʽ��RV20
	SA_ENCODE_VIDEO_RV30,				// ��Ƶ�����ʽ��RV30
	SA_ENCODE_VIDEO_RV40,				// ��Ƶ�����ʽ��RV40
	SA_ENCODE_VIDEO_FLV1,				// ��Ƶ�����ʽ��FLV1
	SA_ENCODE_VIDEO_FLASHSV,			// ��Ƶ�����ʽ��FLASHSV
	SA_ENCODE_VIDEO_FLASHSV2,			// ��Ƶ�����ʽ��FLASHSV2
	SA_ENCODE_VIDEO_VP6,				// ��Ƶ�����ʽ��VP6
	SA_ENCODE_VIDEO_VP6A,				// ��Ƶ�����ʽ��VP6A
	SA_ENCODE_VIDEO_VP6F,				// ��Ƶ�����ʽ��VP6F
	
	// ˽�б����ʽ
	SA_ENCODE_VIDEO_HIK_H264 = 0x81,	// ����˽��H264����
	SA_ENCODE_VIDEO_HIK_HKH4 = 0x82,	// ����˽������
};

enum SA_AUDIO_ENCODED_TYPE
{
	SA_AUDIO_ENCODED_PCM = 0,			// ��Ƶ�����ʽ��PCM8
	SA_AUDIO_ENCODED_ADPCM,				// ��Ƶ�����ʽ��ADPCM
	SA_AUDIO_ENCODED_G711A,				// ��Ƶ�����ʽ��G711A
	SA_AUDIO_ENCODED_G711Mu,			// ��Ƶ�����ʽ��G711Mu
	SA_AUDIO_ENCODED_G726,				// ��Ƶ�����ʽ��G726
	SA_AUDIO_ENCODED_MPEGLayer1,		// ��Ƶ�����ʽ��MPEGLayer1
	SA_AUDIO_ENCODED_AMR,				// ��Ƶ�����ʽ��AMR
	SA_AUDIO_ENCODED_AAC,				// ��Ƶ�����ʽ��AAC
	SA_AUDIO_ENCODED_MPEGLayer2,		// ��Ƶ�����ʽ��MPEGLayer2
	SA_AUDIO_ENCODED_OggVorbis,			// ��Ƶ�����ʽ��OggVorbis
	SA_AUDIO_ENCODED_Mp3,				// ��Ƶ�����ʽ��Mp3
	SA_AUDIO_ENCODED_G722_1,			// ��Ƶ�����ʽ��G722_1
	SA_AUDIO_ENCODED_G729,				// ��Ƶ�����ʽ��G729
	SA_AUDIO_ENCODED_OPUS,				// ��Ƶ�����ʽ��OPUS
	SA_AUDIO_ENCODED_G723S,				// ��Ƶ�����ʽ��G723S
};

enum SA_ENCODE_AUDIO_TYPE
{
	SA_ENCODE_AUDIO_UNKNOWN = 0,
	SA_ENCODE_AUDIO_PCM = 7,			// ��Ƶ�����ʽ��PCM8
	SA_ENCODE_AUDIO_G729,				// ��Ƶ�����ʽ��G729
	SA_ENCODE_AUDIO_IMA,				// ��Ƶ�����ʽ��IMA
	SA_ENCODE_PCM_MULAW,				// ��Ƶ�����ʽ��PCM MULAW
	SA_ENCODE_AUDIO_G721,				// ��Ƶ�����ʽ��G721
	SA_ENCODE_PCM8_VWIS,				// ��Ƶ�����ʽ��PCM8_VWIS
	SA_ENCODE_MS_ADPCM,				    // ��Ƶ�����ʽ��MS_ADPCM
	SA_ENCODE_AUDIO_G711A,				// ��Ƶ�����ʽ��G711A
	SA_ENCODE_AUDIO_AMR,				// ��Ƶ�����ʽ��AMR-NB խ��
	SA_ENCODE_AUDIO_PCM16,				// ��Ƶ�����ʽ��PCM16
	SA_ENCODE_AUDIO_G711U = 22,		    // ��Ƶ�����ʽ��G711U
	SA_ENCODE_AUDIO_G723 = 25,			// ��Ƶ�����ʽ��G723
	SA_ENCODE_AUDIO_AAC,			    // ��Ƶ�����ʽ��AAC Low Delay
	SA_ENCODE_AUDIO_G726_40,            // 40kbps,����32/24/16
	SA_ENCODE_AUDIO_G726_32,            // �ֱ��ʾ�����ʵĲ�ͬ
	SA_ENCODE_AUDIO_G726_24,            // �����8k�����ʵ�
	SA_ENCODE_AUDIO_G726_16,            // �����
	SA_ENCODE_AUDIO_MP2,				// ��Ƶ�����ʽ��mp2
	SA_ENCODE_AUDIO_OGG,				// ��Ƶ�����ʽ��ogg vorbis
	SA_ENCODE_AUDIO_MP3,				// ��Ƶ�����ʽ��mp3
	SA_ENCODE_AUDIO_G722_1,				// ��Ƶ�����ʽ��G722.1

	SA_ENCODE_AUDIO_TALK = 0x30,		// ��Ƶ�����ʽ�ǶԽ�
	SA_ENCODE_AUDIO_AC3,				// ��Ƶ�����ʽ��AC3
};

// ������װ��ʽ
enum
{
	SA_STREAM_TYPE_UNKNOWN = 0,			// δ֪����
	SA_STREAM_TYPE_MPEG4,				// MPEG4
	SA_STREAM_TYPE_DHPT =3,				// ����������DHPT
	SA_STREAM_TYPE_NEW,					// ����������NEW
	SA_STREAM_TYPE_HB,					// ����������HB
	SA_STREAM_TYPE_AUDIO,				// ��Ƶ��
	SA_STREAM_TYPE_PS,					// MPEG-2��PS
	SA_STREAM_TYPE_DHSTD,				// �����µı�׼����
	SA_STREAM_TYPE_ASF,					// ASF
	SA_STREAM_TYPE_3GPP,				// 3GP
	SA_STREAM_TYPE_RAW,					// ����������������
	SA_STREAM_TYPE_TS,					// MPEG-2��TS
	SA_STREAM_TYPE_SVC,					// svc
	SA_STREAM_TYPE_AVI,					// AVI
	SA_STREAM_TYPE_MP4,					// MP4
	SA_STREAM_TYPE_CGI,					// CGI
	SA_STREAM_TYPE_WAV,					// WAV��Ƶ
	SA_STREAM_TYPE_FLV,					// FLV
	SA_STREAM_TYPE_RYMS,				// RY����

	SA_STREAM_TYPE_MKV,					// MKV
	SA_STREAM_TYPE_RTP,					// RTP
	SA_STREAM_TYPE_RAW_MPEG4,			// MPEG4������
	SA_STREAM_TYPE_RAW_H264,			// H264������
	SA_STREAM_TYPE_RAW_H265,			// H265������
	SA_STREAM_TYPE_WMV,					// WMV
	SA_STREAM_TYPE_RAW_MPEG2,			// MPEG2������
	SA_STREAM_TYPE_RAW_SVAC,			// SVAC������
	SA_STREAM_TYPE_MOV,					// MOV
	SA_STREAM_TYPE_VOB,					// VOB
	SA_STREAM_TYPE_RAW_H263,			// H263
	SA_STREAM_TYPE_RM,					// RM
	SA_STREAM_TYPE_DHPS,				// MPEG-2��PS
	SA_STREAM_TYPE_MIDI,				// MIDI

	// ��������������
	SA_STREAM_TYPE_HENGYI = 0x81,		//HENGYI
	SA_STREAM_TYPE_HUANGHE,				//HUANGHE
	SA_STREAM_TYPE_LANGCHI,				//LANGCHI
	SA_STREAM_TYPE_TDWY,				//TDWY
	SA_STREAM_TYPE_DALI,				//DALI
	SA_STREAM_TYPE_LVFF,				//LVFF
	SA_STREAM_TYPE_H3C,					//H3C
	SA_STREAM_TYPE_FENGDA,				//FENGDA
	SA_STREAM_TYPE_MDVRX,				//MDVRX
	SA_STREAM_TYPE_PU8000,				//PU8000
	SA_STREAM_TYPE_DVR,					//DVR
	SA_STREAM_TYPE_IFV,					//IFV
	SA_STREAM_TYPE_264DV,				//264DV
	SA_STREAM_TYPE_ZWSJ,				//ZWSJ
	SA_STREAM_TYPE_SANLI,				//SANLI
	SA_STREAM_TYPE_HIK_PRIVATE,			//HIK_PRIVATE
	SA_STREAM_TYPE_HIK_PS,				//HIK_PS
	SA_STREAM_TYPE_STAR,				//STAR
	SA_STREAM_TYPE_LIYUAN,				//LIYUAN
};

enum
{
	SA_PARSE_TYPE_NOT_SUPPORT = 0,
	SA_PARSE_TYPE_ONLY_STREAM = 1,
	SA_PARSE_TYPE_ONLY_FILE = 2,
	SA_PARSE_TYPE_SUPPORT_ALL = 3,
};

// �����־λ
enum
{
	SA_ERROR_FLAGS_NOERROR = 0,		    // ����У������
	SA_ERROR_FLAGS_TIMESTAND,			// ʱ�������
	SA_ERROR_FLAGS_LENGTH,				// ���ȳ���
	SA_ERROR_FLAGS_HEAD_VERIFY,		    // ֡ͷ�ڲ�����У��
	SA_ERROR_FLAGS_DATA_VERIFY,		    // ����У��ʧ��
	SA_ERROR_FLAGS_LOST_HEADER,		    // ���ݶ�ʧ֡ͷ
	SA_ERROR_FLAGS_UNKNOWN,			    // ����֪����
	SA_ERROR_FLAGS_LOSTFRAME,           // ��֡
	SA_ERROR_FLAGS_WATERMARK,           // ˮӡУ�����
	SA_ERROR_FLAGS_CONTEXT,             // �����Ĵ���
	SA_ERROR_FLAGS_NOSUPPORT,           // ��֧�ֵ�����
    SA_ERROR_FLAGS_FRAME_HALF_BAKED,    // ֡������
	SA_ERROR_FLAGS_SUBTYPE_UNKNOWN		// δ֪֡����
};

// �⽻���־
enum
{
	SA_DEINTERLACE_PAIR = 0 ,			// ���������
	SA_DEINTERLACE_SINGLE,				// ��������
	SA_DEINTERLACE_NONE					// �޽⽻��
};

// �������ͱ�־λ
enum
{
	SA_INDEX_BIT_FLAG_VIDEO_I = 1,			// ��ƵI֡
	SA_INDEX_BIT_FLAG_VIDEO_P = 2,			// ��ƵP֡
	SA_INDEX_BIT_FLAG_VIDEO_B = 4,			// ��ƵB֡
	SA_INDEX_BIT_FLAG_AUDIO = 8,			// ��Ƶ֡
	SA_INDEX_BIT_FLAG_DATA = 16,			// ����֡
	SA_INDEX_BIT_FLAG_ALL = 0xffffffff		// ����֡
};

// ʱ����Ϣ
typedef struct
{
	int nYear;					// ��
	int nMonth;					// ��
	int nDay;					// ��
	int nHour;					// Сʱ
	int nMinute;				// ����
	int nSecond;				// ��
	int nMilliSecond;			// ����
} SA_TIME;

// ͸�����
typedef struct
{
    int bIsExist;				// �Ƿ���ڴ˽ṹ 0:������ 1:����
    int nMode;					// ͸��ģʽ 1:�ر� 2:�Զ� 3:�ֶ� ����:����
    int nIntension;				// ͸��ǿ��0-2
    int nAirLightMode;			// ������ģʽ1:�Զ� 2: �ֶ� ����:����
    int nAirLightIntesion;		// ������ǿ��0-15
}SA_FOG_THROUGH;

// ��������
enum 
{
    SA_COMPANY_TYPE_HIK = 1,                    // ��������
    SA_COMPANY_TYPE_HANBANG,                    // ��������
    SA_COMPANY_TYPE_YUSHI,                      // ��������
    SA_COMPANY_TYPE_INTERNATIONAL_DEVICE_PS,    // �����豸PS����
    SA_COMPANY_TYPE_XINCHAN,                    // �Ų�����
    SA_COMPANY_TYPE_LIYUAN,                     // ��Ԫ����
    SA_COMPANY_TYPE_BIT,                        // ��������
    SA_COMPANY_TYPE_OLD_DH,                     // �ϴ�����
    SA_COMPANY_TYPE_STD_TS,                     // ��׼ts��
    SA_COMPANY_TYPE_TDYG,                       // �������
    SA_COMPANY_TYPE_ANXUNSHI,                   // ��Ѹʿ
    SA_COMPANY_TYPE_DFWL,                       // ��������
    SA_COMPANY_TYPE_JUFENG,                     // �޷�
    SA_COMPANY_TYPE_KEDA,                       // �ƴ�
    SA_COMPANY_TYPE_LG,                         // LG
    SA_COMPANY_TYPE_MAISHI,                     // ����
    SA_COMPANY_TYPE_TONGZUN,                    // ͬ��
    SA_COMPANY_TYPE_VIVO,                       // vivo
    SA_COMPANY_TYPE_WEIHAO,                     // ΰ�
    SA_COMPANY_TYPE_XINGWANG,                   // ����
    SA_COMPANY_TYPE_BJWS,                       // ��������
    SA_COMPANY_TYPE_XJSX,                       // �Ƚ���Ѷ
    SA_COMPANY_TYPE_SZXY,                       // ��������
    SA_COMPANY_TYPE_ZSYH,                       // ��ʢ�滪
    SA_COMPANY_TYPE_ZXLW,                       // ������ά
    SA_COMPANY_TYPE_ZXTX,                       // ����ͨѶ
	SA_COMPANY_TYPE_HIK_NOHEAD	= 57,			// �������� ��40�ֽ�ͷ
};

// ��������
enum
{
    SA_ENCRYPT_UNKOWN = 0,
    SA_ENCRYPT_AES,
    SA_ENCRYPT_DES,
    SA_ENCRYPT_3DES
};

// ����ǩ��ժҪ�㷨����
enum
{
	SA_DIGEST_ALGORITHM_UNKOWN = 0,
	SA_DIGEST_ALGORITHM_SHA1
};

// ����ǩ�������㷨����
enum
{
	SA_DIGTAL_SIGNATURE_ENCRYPT_UNKOWN = 0,
	SA_DIGTAL_SIGNATURE_ENCRYPT_RSA

};

typedef struct  
{
    int nVideoEncodeType;				// ��Ƶ��������
    int nFrameRate;						// ֡��
    int nWidth;							// ��
    int nHeight;						// ��
    int nSPS_PPSLen;					// sps��pps��Ϣ��
    unsigned char* pSPS_PPSData;		// sps��pps��Ϣ
    int nAudioEncodeType;				// ��Ƶ��������
    int nSamplerPerSec;					// ��Ƶ������
    int bitsPerSample;					// ��Ƶ����λ��
}SA_SDP_INFO;

typedef struct
{
	unsigned char chType;				// 1:���ֽڣ��޷�����������������
	unsigned char chLength;				// type�й涨�Ĳ�����Ԫ����
	unsigned char chValue;				// ������
	unsigned char nReserved;			// ��������
}SA_DATA_CUSTOM_CHANGE;

#ifdef STREAM_ADAPTER_FOR_RELEASE
#pragma pack(1)
#endif

// ֡��Ϣ
typedef struct
{
	// ����
	int						frameType;							// ֡����
	int						frameSubType;						// ֡������
	int						frameEncodeType;					// ֡��������
	int						streamType;							// ��������

	// ����
	unsigned char*			streamPointer;						// ָ����������,ȥ��֡ͷ,NULL��ʾ��Ч����
	int						streamLen;							// ��������(������֡ͷ��β)
	unsigned char*			framePointer;						// ָ��֡ͷ,NULL��ʾ��Ч����
	int						frameLen;							// ֡����(����֡ͷ��֡�塢֡β)

	// ʱ��
	SA_TIME					frameTime;							// ʱ����Ϣ
	int						timeStamp;							// ʱ���

	// ���
	int						frameSeq;							// ֡���
	
	// ��Ƶ���ԣ��ؼ�֡����
	int						frameRate;							// ֡��
	int						width;								// ��
	int						height;								// ��
	int						deinterlace;						// �⽻��
	int						mediaFlag;							// �����ͱ�ǣ�h264������(0������������2��HS ����)
	
	// ��Ƶ����
	int						samplesPerSec;						// ����Ƶ��
	int						bitsPerSample;						// ����λ��
	int						channels;							// ������

	/*�����־*/
	int						errorFlags;							// �������־λ

    SA_FOG_THROUGH			fogThrough;							// ͸�����

    unsigned char			allLevels;							// svc�ܲ���
    unsigned char			levelOrder;							// ��ǰ֡���ڵڼ���

    unsigned short			companyType;						// ��������
    unsigned short			tpStreamHeaderLen;					// ���������ļ�ͷ��Ϣ���ȣ�tp:third party

    /*֧��˫��Ƶ����*/
    unsigned char			totalChannels;						// ͨ����
    unsigned char			curChannel;							// ͨ����

    int						nEncryptType;						// ��������
    int						nEncryptLen;						// ���ܳ���

	SA_DATA_CUSTOM_CHANGE	customChangeInfo;					// �������ݱ������޸ĵ�����������û���������
	
	// ����֡��֧��
	unsigned short			rateValue;							// ֡�ʷ���
	unsigned short			rateDenominator;					// ֡�ʷ�ĸ

	// ����֧��
	unsigned short			n_slice;
	unsigned short			m_slice;
	unsigned short			srcPicWidth;
	unsigned short			srcPicHeight;
	unsigned short			sliceInfoOffset;					// �����framePointer*/
	unsigned short			sliceInfoLength;					// �ֿ�ͼ����Ϣ�ĳ���*/

	// ������Ϣ
	unsigned char			fishEyeGain;						// ���棬ȡֵ0-100*/
	unsigned char			fishEyeDenoiseLevel;				// ����ȼ���ȡֵ0-100*/
	unsigned char			fishInstallStyle;					// ���۰�װ��ʽ��0�������� 1����װ 2����װ 3����װ*/
																// ��������壬˵������������Ϣ
	unsigned char			fishEyeCorrectMode;					// ���۽���ģʽ
																// 1:"Original"ԭʼͼ��ģʽ
																// 2:"Config"����ģʽ
																// 3:"Panorama"ȫ��ģʽ
																// 4:"DoublePanorama"˫ȫ��ģʽ
																// 5:"OriginalPlusThreeEPtsRegion"1+3ģʽ
																// 6:"Single"������EPtsģʽ
																// 7:"FourEPtsRegion"4����ģʽ
																// 8:"Normal"Narmalģʽ

	unsigned short			fishEyeCircleX;						// ����Բ������X
	unsigned short			fishEyeCircleY;						// ����Բ������Y

	unsigned short			fishEyeRadius;						// ���۰뾶
	unsigned char			encryptOffset;						// 0x95
	unsigned char			encryptReserved;					// ��������

	int						pictrueStructure;

	// ��Ƶ��߱���0x9B
	unsigned char			ratioWidth;							// 0x9b ����ǰ��߱���
	unsigned char			ratioHeigth;
	unsigned char			ratioEncodeWidth;					// ������߱���
	unsigned char			ratioEncodeHeight;
 
	unsigned int			digtalSignatureSamplenlen;			// 0x9C

	unsigned short			digtalSignatureEncdeclen;
	unsigned char			digtalSignatureDigestType;
	unsigned char			digtalSignatureEncryptType;

	unsigned char*			digtalSignatureEncdecDataPtr;
	
	unsigned char			rotationAngle;						// ������ת�Ƕ�

	unsigned char			svacEncryptKeyLen;
	unsigned short			svacEncryptDataLen;

	unsigned char*			svacEncryptKeyData;

	// ��Ƶ����
	unsigned int			audioBitrate;						// ��Ƶ������

	unsigned char*			extDataPtr;							// ��չ����
	unsigned int			extDataLen;							// ��չ���ݳ���

	unsigned char			bFrameNum;							// ����P֮֡���B֡��

	unsigned char			nFsMcfRow;							// FS MCF ����
	unsigned char			nFsMcfCol;							// FS MCF ����

	unsigned char			reserved[41];						// �����ֽ�
} SA_FRAME_INFO;
#ifdef STREAM_ADAPTER_FOR_RELEASE
#pragma pack()
#endif

#if (defined(WIN32) || defined(WIN64))
typedef __int64 SPint64;
#else // linux
typedef long long SPint64;
#endif

/*�ļ���ʽ��֡��Ϣ*/
typedef	struct
{
	SPint64 streamOffset;			// ���������ݵ�ƫ����(ȥ��֡ͷ)
	SPint64 frameOffset;			// ֡ͷ��ƫ����
	unsigned char	reserved[64];	// �����ֽ�
}SA_INDEX_INFO;

typedef	struct
{
	unsigned char*	modulePath;		// ��ǰģ��·��
	void*			moduleHandle;	// ģ����
	unsigned char	reserved[56];	// �����ֽ�
}SA_INIT_INFO;

// �ṹ��128�ֽ�
typedef	struct
{
	unsigned int filesize;			// �ļ��ܳ���
	unsigned int 	createtime;		// ����ʱ�� utcʱ��
	unsigned int 	duration;		// ��ʱ��(��λs)

	unsigned int 	framenum;		// ��֡��
	unsigned int videonum;			// ��Ƶ��֡��
	unsigned int audionum;			// ��Ƶ��֡��

	unsigned int keyframenum;		// �ؼ�֡��
	unsigned int maxframesize;		// ���֡����, Ԥ��ֵ

	unsigned char	reserved[96];	// �����ֽ�
}SA_FILE_INFO;

// �ļ������ص�����
typedef int (CALLMETHOD *fFileIndexCallBack)(IN void* handle,				
									 IN SA_FRAME_INFO* frameInfo,  
									 IN SA_INDEX_INFO* indexInfo,	
									 IN int process,				
									 IN void* userData);			

// �ļ���Ϣ�ص�����
typedef int (CALLMETHOD *fFileInfoCallBack)(IN void* handle,				
									IN SA_FILE_INFO* fileInfo,  		
									IN void* userData);	

// ��ʼ����Դ
SA_API SA_RESULT CALLMETHOD SA_LoadLibrary(SA_INIT_INFO* initInfo = NULL);

// �ͷ����ӿ���Դ
SA_API SA_RESULT CALLMETHOD SA_ReleaseLibrary(void);

// ������������
SA_API void* CALLMETHOD SA_CreateStreamParser(IN int nBufferSize);

// ��ȡ�������ͣ���SA_ParseData�ɹ������
SA_API SA_RESULT CALLMETHOD SA_GetStreamType(IN void* handle, OUT int* streamType);

// ����������,��ͬ�����з���
SA_API SA_RESULT CALLMETHOD SA_ParseData(IN void* handle, IN unsigned char* stream, IN int length);

// ͬ����ȡһ֡��Ϣ,��������ֱ��ʧ��
SA_API SA_RESULT CALLMETHOD SA_GetOneFrame(IN void* handle, IN SA_FRAME_INFO* frameInfo);

#ifndef STREAM_ADAPTER_FOR_RELEASE

// ��ȡ�������ͣ���SA_ParseData�ɹ������
SA_API SA_RESULT CALLMETHOD SA_GetParseType(IN int streamType, OUT int* parseType);

// ��ȡ�����������в�������
SA_API SA_RESULT CALLMETHOD SA_GetRemainData(IN void* handle, OUT unsigned char** dataPointer, OUT int* sizePointer);

// ��������������ڲ��Ļ���
SA_API SA_RESULT CALLMETHOD SA_ClearBuffer(IN void* handle);

// �����ļ�������
SA_API void* CALLMETHOD SA_CreateFileParser(IN char* file, IN fFileIndexCallBack fileIndex, IN void* userData);

// �����ļ�������
SA_API void* CALLMETHOD SA_CreateFileParserEx1(IN int nType, IN char* file, IN fFileIndexCallBack fileIndex, IN fFileInfoCallBack fileInfo, IN void* userData);

// �����ļ�Ƭ�η�����
SA_API void* CALLMETHOD SA_CreateSliceParser(IN char* file, IN fFileIndexCallBack fileIndex, IN void* userData, SPint64 sliceoffset, SPint64 slicesize);

// ��ȡ�ļ�������Ϣ������Ϣ
SA_API SA_RESULT CALLMETHOD SA_GetProcess(IN void* handle, OUT int* process);

// �õ�ָ��λ�õ�֡��Ϣ��֡ƫ����Ϣ
SA_API SA_RESULT CALLMETHOD SA_GetOneIndex(IN void* handle, IN int index, OUT SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo);

// �����ļ�����������flags: �������ͱ��ر�־λ���μ�SA_INDEX_BIT_FLAG_xxx
SA_API SA_RESULT CALLMETHOD SA_GetIndexCount(IN void* handle, IN int flags, OUT int* indexCount);

// һ�λ�ȡ����������Ϣ
SA_API SA_RESULT CALLMETHOD SA_GetAllIndex(IN void* handle, IN int flags, OUT SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo, IN int structCount, OUT int* indexCount);

// ͨ�������õ�SA_FRAME_INFO�ṹ����Ϣ��
SA_API SA_RESULT CALLMETHOD SA_GetFrameByIndex(IN void* handle, IN SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo);

// ����ʵʱ��������Կ  type : ��Կ���ͣ���SA_ENCRYPT_AES��key����Կ���ݣ�keylen����Կ����
SA_API SA_RESULT CALLMETHOD SA_StreamEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

// �����ļ�������Կ type : ��Կ���ͣ���SA_ENCRYPT_AES��key����Կ���ݣ�keylen����Կ����
SA_API SA_RESULT CALLMETHOD SA_FileEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

#endif

//  ��������������
SA_API SA_RESULT CALLMETHOD SA_Destroy(IN void* handle);

// ������������������
SA_API SA_RESULT CALLMETHOD SA_GetLastError(IN void* handle);

#ifndef STREAM_ADAPTER_FOR_RELEASE
// ��������ת��Ϊ�ַ���
SA_API SA_RESULT CALLMETHOD SA_ErrorToString(IN int error, OUT char** text);
#endif

#ifdef __cplusplus
}
#endif

#endif