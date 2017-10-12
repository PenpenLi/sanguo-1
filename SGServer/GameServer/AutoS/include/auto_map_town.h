#ifndef __MAPTOWN_AUTO_H
#define __MAPTOWN_AUTO_H
#include "define.h"

struct _map_town {
//--Automatically generated
				int townid;	//����id
				char nation;	//����
				char name[22];	//�޸ĺ������
				int protect_sec;	//����ʱ��
				short produce_num;	//���մ���
				int produce_sec;	//����ʱ��
				int own_actorid;	//������ɫid
				int own_sec;	//�������ڵ���ʱ
				int join_actorid[128];	//��ս��Ա
				int ask_actorid[128];	//������Ա
				int monster[16];	//����
				int soldier[16];	//����Ѫ���浵
				char soldier_update;	//����Ѫ���浵����
				short pre_townid[8];	//��һ��townid�б�
				int ask_city_index[128];	//��ѡ�߳ǳ�����
				int underfire_groupindex[4];	//��������
				int own_city_index;	//��������
				int unit_index;	//��ʾ����
};
typedef struct _map_town MapTown;

typedef MapTown * (*LPCB_GETMAPTOWN)( int townid );
typedef int (*LPCB_LOADMAPTOWN)( int townid );
int map_town_load_auto( LPCB_GETMAPTOWN pCB_GetMapTown, LPCB_LOADMAPTOWN pCB_LoadMapTown, const char *pTab );
int map_town_save_auto( MapTown *pMapTown, const char *pTab, FILE *fp );
int map_town_batch_save_auto( MapTown *pMapTown, int maxcount,  const char *pTab, FILE *fp );

#endif
