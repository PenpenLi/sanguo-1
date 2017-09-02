#ifndef __MAPRES_AUTO_H
#define __MAPRES_AUTO_H
#include "define.h"

struct _map_res {
//--Automatically generated
				int index;	//����
				short posx;	//λ��
				short posy;	//λ��
				short kind;	//��Դ����
				int num;	//�Ѿ��ɼ���Դ��
				int idlesec;	//����ʱ��
				int army_index;	//���ڲɼ��Ĳ���
				int unit_index;	//��ʾ����
};
typedef struct _map_res MapRes;

typedef MapRes * (*LPCB_GETMAPRES)( int index );
typedef int (*LPCB_LOADMAPRES)( int index );
int map_res_load_auto( LPCB_GETMAPRES pCB_GetMapRes, LPCB_LOADMAPRES pCB_LoadMapRes, const char *pTab );
int map_res_save_auto( MapRes *pMapRes, const char *pTab, FILE *fp );
int map_res_batch_save_auto( MapRes *pMapRes, int maxcount,  const char *pTab, FILE *fp );

#endif
