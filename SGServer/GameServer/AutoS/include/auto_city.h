#ifndef __CITY_AUTO_H
#define __CITY_AUTO_H
#include "define.h"

struct _city {
//--Automatically generated
				int actorid;	//��ɫID
				int index;	//����
				char name[22];	//����
				char type;	//�ǳ�����
				char shape;	//��������(ѡȡ)
				int headid;	//����ͷ��(�Զ���)
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
				int exp;	//��Ҿ���
				char viplevel;	//VIP�ȼ�
				int vipexp;	//VIP����
				char nation;	//����(κ����)
				char official;	//��ְ
				char place;	//��λ
				char zone;	//����
				int battlepower;	//ս��
				char mokilllv;	//��ɱҰ����߼���
				short body;	//����
				short bodysec;	//�����ָ�ʱ��(ÿ��-1)
				int silver;	//����
				int wood;	//ľ��
				int food;	//����
				int iron;	//����
				unsigned char levynum;	//��ǰ���մ���
				short levysec;	//�´�����ʱ��(ÿ��-1)
				int people;	//�˿�
				int prestige;	//����ֵ
				int friendship;	//�������
				int function;	//�����Ƿ���
				Hero hero[4];	//����Ӣ��
				Building building[8];	//��ͨ����
				BuildingBarracks building_barracks[4];	//��Ӫ����
				BuildingRes building_res[64];	//��Դ����
				char worker_op;	//������в���
				int worker_sec;	//����ʣ��ʱ��(ÿ��-1)
				char worker_kind;	//��ǰ������������
				char worker_offset;	//��ǰ������������
				char worker_op_ex;	//������в���(����)
				int worker_sec_ex;	//����ʣ��ʱ��(ÿ��-1)(����)
				char worker_kind_ex;	//��ǰ������������(����)
				char worker_offset_ex;	//��ǰ������������(����)
				int worker_expire_ex;	//���ý�����е���ʱ��
				int actor_index;	//��ɫ����
				int unit_index;	//��ʾ����
				int army_index[5];	//����
};
typedef struct _city City;

typedef City * (*LPCB_GETCITY)( int index );
typedef int (*LPCB_LOADCITY)( int index );
int city_load_auto( LPCB_GETCITY pCB_GetCity, LPCB_LOADCITY pCB_LoadCity, char *pTab );
int city_save_auto( City *pCity, char *pTab, FILE *fp );

#endif
