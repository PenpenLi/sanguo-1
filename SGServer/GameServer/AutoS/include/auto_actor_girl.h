#ifndef __GIRL_AUTO_H
#define __GIRL_AUTO_H
#include "define.h"

struct _actor_girl {
//--Automatically generated
				int actorid;	//��ɫ
				char kind;	//����
				char love_level;	//���ܵȼ�
				char love_num;	//�������ܴ���
				char color;	//��ɫ
				short soul;	//��Ƭ
				short love_exp;	//���ܶ�
				int love_fday;	//����ʱ��
};
typedef struct _actor_girl Girl;

typedef Girl * (*LPCB_GETGIRL)( int actorid, int kind );
int actor_girl_load_auto( int actorid, int city_index, LPCB_GETGIRL pCB_GetGirl, const char *pTab );
int actor_girl_save_auto( int actorid, int offset, Girl *pGirl, const char *pTab, FILE *fp );
int actor_girl_batch_save_auto( int actorid, Girl *pGirl, int maxcount, const char *pTab, FILE *fp );

#endif
