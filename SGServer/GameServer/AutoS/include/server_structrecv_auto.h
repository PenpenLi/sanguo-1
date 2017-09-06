#ifndef __STRUCTRECV0_AUTO_H
#define __STRUCTRECV0_AUTO_H
#include "server_struct_auto.h"

struct _slk_NetC_Login {
	short m_username_length;	//�ͻ�������-�û�������
	char m_username[51];	//�ͻ�������-�û���
	short m_password_length;	//�ͻ�������-���볤��
	char m_password[256];	//�ͻ�������-����
	short m_deviceid_length;	//�ͻ�������-�豸��ʾ����
	char m_deviceid[65];	//�ͻ�������-�豸��ʾ
	short m_isnew;	//�ͻ�������-�Ƿ����û�
	short m_ipcountry_length;	//�ͻ�������-IP��ַ���ڹ���
	char m_ipcountry[16];	//�ͻ�������-IP��ַ���ڹ���
};
typedef struct _slk_NetC_Login SLK_NetC_Login;	//�ͻ��������¼

struct _slk_NetC_Create {
	char m_nation;	//�ͻ�������-�����Ľ�ɫ����
	short m_name_length;	//�ͻ�������-�����Ľ�ɫ���Ƴ���
	char m_name[22];	//�ͻ�������-�����Ľ�ɫ����
};
typedef struct _slk_NetC_Create SLK_NetC_Create;	//�ͻ������󴴽���ɫ

struct _slk_NetC_Heart {
	int m_value[2];	//����-��ֵ
};
typedef struct _slk_NetC_Heart SLK_NetC_Heart;	//����

struct _slk_NetC_Gmcmd {
	short m_cmd;	//�ͻ��˷���-GMָ��
	int m_value[4];	//�ͻ��˷���-GMָ����ֵ����
	short m_msg_length;	//�ͻ��˷���-GMָ���ַ�������
	char m_msg[1024];	//�ͻ��˷���-GMָ���ַ�������
};
typedef struct _slk_NetC_Gmcmd SLK_NetC_Gmcmd;	//GMָ��

struct _slk_NetC_AskInfo {
	short m_msgid;	//�ͻ��˷���-������ID
	short m_valuenum;	//�ͻ��˷���-�������������
	int m_value[10];	//�ͻ��˷���-���������
	short m_msg_length;	//�ͻ��˷���-�������ַ�������
	char m_msg[256];	//�ͻ��˷���-�������ַ���
};
typedef struct _slk_NetC_AskInfo SLK_NetC_AskInfo;	//�ͻ��˷��Ͷ�����

struct _slk_NetC_EnterCity {
	char m_value;	//�ͻ��˷���-���ѳ�ʼ���ã������������Ϣ��
};
typedef struct _slk_NetC_EnterCity SLK_NetC_EnterCity;	//�������ǳ�������Ϣ

struct _slk_NetC_Chat {
	short m_msglen;	//�ͻ��˷�������-��Ϣ
	char m_msg[127];	//�ͻ��˷�������-��Ϣ
	char m_channel;	//�ͻ��˷�������-ѡ������
};
typedef struct _slk_NetC_Chat SLK_NetC_Chat;	//����

struct _slk_NetC_StoryBattle {
	int m_storyid;	//����id
	short m_herokind[4];	//������ս��Ӣ��
};
typedef struct _slk_NetC_StoryBattle SLK_NetC_StoryBattle;	//����ս��

struct _slk_NetC_WorldMapAsk {
	short m_to_posx;	//����ǰ�������ͼ
	short m_to_posy;	//����ǰ�������ͼ
};
typedef struct _slk_NetC_WorldMapAsk SLK_NetC_WorldMapAsk;	//����ǰ�������ͼ

struct _slk_NetC_WorldMapAreaIndex {
	int m_areaindex;	//�߼���������
	short m_posx;	//�߼���������
	short m_posy;	//�߼���������
};
typedef struct _slk_NetC_WorldMapAreaIndex SLK_NetC_WorldMapAreaIndex;	//�����ͼ�߼���������

struct _slk_NetC_MapBattle {
	char m_to_unit_type;	//����Ŀ��
	int m_to_unit_index;	//����Ŀ��
	int m_id;	//����Ŀ��
	short m_herokind[4];	//����Ӣ��
	short m_to_posx;	//����Ŀ�ĵ�
	short m_to_posy;	//����Ŀ�ĵ�
	int m_appdata;	//������������
	char m_action;	//������Ϊ
};
typedef struct _slk_NetC_MapBattle SLK_NetC_MapBattle;	//����

struct _slk_NetC_MailAsk {
	unsigned int m_minid;	//�ʼ�-������С��id
	unsigned int m_maxid;	//�ʼ�-��������id
	short m_op;	//�ʼ�-����
};
typedef struct _slk_NetC_MailAsk SLK_NetC_MailAsk;	//��������ʼ�

int struct_NetC_Login_recv( char **pptr, int *psize, SLK_NetC_Login *pValue );
int struct_NetC_Create_recv( char **pptr, int *psize, SLK_NetC_Create *pValue );
int struct_NetC_Heart_recv( char **pptr, int *psize, SLK_NetC_Heart *pValue );
int struct_NetC_Gmcmd_recv( char **pptr, int *psize, SLK_NetC_Gmcmd *pValue );
int struct_NetC_AskInfo_recv( char **pptr, int *psize, SLK_NetC_AskInfo *pValue );
int struct_NetC_EnterCity_recv( char **pptr, int *psize, SLK_NetC_EnterCity *pValue );
int struct_NetC_Chat_recv( char **pptr, int *psize, SLK_NetC_Chat *pValue );
int struct_NetC_StoryBattle_recv( char **pptr, int *psize, SLK_NetC_StoryBattle *pValue );
int struct_NetC_WorldMapAsk_recv( char **pptr, int *psize, SLK_NetC_WorldMapAsk *pValue );
int struct_NetC_WorldMapAreaIndex_recv( char **pptr, int *psize, SLK_NetC_WorldMapAreaIndex *pValue );
int struct_NetC_MapBattle_recv( char **pptr, int *psize, SLK_NetC_MapBattle *pValue );
int struct_NetC_MailAsk_recv( char **pptr, int *psize, SLK_NetC_MailAsk *pValue );

#endif
