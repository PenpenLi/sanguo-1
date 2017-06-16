#ifndef __CITY_AUTO_H
#define __CITY_AUTO_H
#include "define.h"

struct _city {
//--Automatically generated
				int cityid;	//�ǳ�ID
				int actorid;	//��ɫID
				char name[22];	//����
				char type;	//�ǳ�����
				char shape;	//��������
				int headid;	//����ͷ��
				short country;	//ѡ��Ĺ���(��ʵ)
				char ipcountry[3];	//IP��ַ���ڹ���
				char language;	//ѡ������
				char os;	//ϵͳ1ios 2android 3win
				char platid;	//ƽ̨
				int createtime;	//����ʱ��
				int lastlogin;	//�ϴε�½ʱ��
				int lastlogout;	//�ϴεǳ�ʱ��
				char state;	//�ǳص�ǰ״̬
				short posx;	//λ��
				short posy;	//λ��
				int sflag;	//��־λ
				short level;	//��ҵȼ�
				char viplevel;	//VIP�ȼ�
				int vipexp;	//VIP����
				char nation;	//����(κ����)
				char official;	//��ְ
				char place;	//��λ
				char domain;	//����
				int battlepower;	//ս��
				char mokilllv;	//��ɱҰ����߼���
				short body;	//����
				int silver;	//����
				int wood;	//ľ��
				int food;	//����
				int iron;	//����
				int people;	//�˿�
				Building building[8];	//��ͨ����
				BuildingBarracks building_barracks[4];	//��Ӫ����
				BuildingRes building_res[64];	//��Դ����
				int city_index;	//�ǳ�����
				int actor_index;	//��ɫ����
				int unit_index;	//��ʾ����
				int army_index[5];	//����
};
typedef struct _city City;

typedef City * (*LPCB_GETCITY)( int actorid );
typedef int (*LPCB_LOADCITY)( int actorid );
int city_load_auto( LPCB_GETCITY pCB_GetCity, LPCB_LOADCITY pCB_LoadCity, char *pTab );
int city_save_auto( City *pCity, char *pTab, FILE *fp );
int city_batch_save_auto( City *pCity, int maxcount,  char *pTab, FILE *fp );

#endif
