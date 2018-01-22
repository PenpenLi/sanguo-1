#ifndef __MAPCALL_AUTO_H
#define __MAPCALL_AUTO_H
#include "define.h"

struct _map_call {
//--Automatically generated
				char index;	//�ٻ��¼�����
				int actorid;	//�������
				short limitlevel;	//等级限制
				int endtimestamp;	//����ʱ��
				char num;	//��ǰ�ٻ�����
				char maxnum;	//�ٻ���������
				char city_index;	//�������
				int notifycd;	//���빫��cd
};
typedef struct _map_call MapCall;

typedef MapCall * (*LPCB_GETMAPCALL)( int index );
typedef int (*LPCB_LOADMAPCALL)( int index );
int map_call_load_auto( LPCB_GETMAPCALL pCB_GetMapCall, LPCB_LOADMAPCALL pCB_LoadMapCall, const char *pTab );
int map_call_save_auto( MapCall *pMapCall, const char *pTab, FILE *fp );
int map_call_batch_save_auto( MapCall *pMapCall, int maxcount,  const char *pTab, FILE *fp );

#endif
