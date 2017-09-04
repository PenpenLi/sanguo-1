#ifndef __MAPEVENT_AUTO_H
#define __MAPEVENT_AUTO_H
#include "define.h"

struct _map_event {
//--Automatically generated
				int index;	//�¼�����
				short posx;	//λ��
				short posy;	//λ��
				short kind;	//����
				int waitsec;	//����ʱ
				int actorid;	//���ڽ�ɫ
				char state;	//״̬
				int unit_index;	//��ʾ����
};
typedef struct _map_event MapEvent;

typedef MapEvent * (*LPCB_GETMAPEVENT)( int index );
typedef int (*LPCB_LOADMAPEVENT)( int index );
int map_event_load_auto( LPCB_GETMAPEVENT pCB_GetMapEvent, LPCB_LOADMAPEVENT pCB_LoadMapEvent, const char *pTab );
int map_event_save_auto( MapEvent *pMapEvent, const char *pTab, FILE *fp );
int map_event_batch_save_auto( MapEvent *pMapEvent, int maxcount,  const char *pTab, FILE *fp );

#endif
