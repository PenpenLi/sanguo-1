#ifndef _GIRL_H_
#define _GIRL_H_
#include "define.h"
#define ACTOR_GIRL_MAX	80

// ��offsetת���ɶ�Ӧ�����Խṹ
Girl *girl_getptr( int city_index, int kind );
GirlInfoConfig *girl_getconfig( int kind, int color );
void girl_makestruct( City *pCity, Girl *pGirl, SLK_NetS_Girl *pValue );
int girl_getgirl( City *pCity, int kind, char path ); // ��һ��Ů��
int girl_getsoul( City *pCity, int kind, int soul, char path ); // ��һ��Ů����Ƭ
int girl_info( City *pCity, Girl *pGirl ); // Ů����Ϣ
int girl_list( int actor_index ); // Ů���б�
void girl_gm_getall( City *pCity );
#endif