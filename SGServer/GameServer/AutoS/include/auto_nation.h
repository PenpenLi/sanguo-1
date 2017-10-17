#ifndef __NATION_AUTO_H
#define __NATION_AUTO_H
#include "define.h"

struct _nation {
//--Automatically generated
				char nation;	//����
				char level;	//�ȼ�
				int exp;	//����
				char notice[512];	//���ҹ���
				int official_actorid[16];	//��Աid������0�ǹ���
				int people;	//�������˿�
				int people_famous;	//�����˿�
				int people_capital;	//�����˿�
				short capital_townid;	//����id
				int town_war_index[256];	//����ս��
				int city_war_index[1024];	//�ǳ�ս��
				int official_city_index[16];	//��Ա����������0�ǹ���
};
typedef struct _nation Nation;

typedef Nation * (*LPCB_GETNATION)( int nation );
typedef int (*LPCB_LOADNATION)( int nation );
int nation_load_auto( LPCB_GETNATION pCB_GetNation, LPCB_LOADNATION pCB_LoadNation, const char *pTab );
int nation_save_auto( Nation *pNation, const char *pTab, FILE *fp );

#endif
