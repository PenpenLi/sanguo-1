#ifndef __NATION_AUTO_H
#define __NATION_AUTO_H
#include "define.h"

struct _nation {
//--Automatically generated
				char nation;	//����
				char level;	//�ȼ�
				int exp;	//����
				char notice[512];	//���ҹ���
				int official_actorid[10];	//��Աid������0�ǹ���
				int tiance_point;	//��߸�ͳ�����
				char questlevel[3];	//��������
				char questkind[3];	//��������
				char missionlevel;	//������������ȼ�
				int missionvalue[4];	//���������������
				int candidate_actorid[10];	//��ѡ��id
				int candidate_ballot[10];	//��ѡ��ѡƱ
				short tiance_level;	//��߸�ͳ��ȼ�
				int people;	//�������˿�
				int people_famous;	//�����˿�
				int people_capital;	//�����˿�
				short capital_townid;	//����id
				int town_war_index[256];	//����ս��
				int city_war_index[1024];	//�ǳ�ս��
				int official_city_index[10];	//��Ա����������0�ǹ���
				int candidate_city_index[10];	//��ѡ������
				int notice_change_stamp;	//�ϴ��޸Ĺ���ʱ��
				int online_notify_king_stamp;	//�ϴι�������ʱ��
				int online_notify_r4_stamp;	//�ϴ�ة������ʱ��
				int online_notify_r5_stamp;	//�ϴξ�ʦ����ʱ��
};
typedef struct _nation Nation;

typedef Nation * (*LPCB_GETNATION)( int nation );
typedef int (*LPCB_LOADNATION)( int nation );
int nation_load_auto( LPCB_GETNATION pCB_GetNation, LPCB_LOADNATION pCB_LoadNation, const char *pTab );
int nation_save_auto( Nation *pNation, const char *pTab, FILE *fp );

#endif
