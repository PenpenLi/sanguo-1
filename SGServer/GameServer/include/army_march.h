#ifndef _ARMY_MARCH_H_
#define _ARMY_MARCH_H_
#include "define.h"

// ���㲿���о�����ʱ��
int army_marchtime_calc( City *pCity, short from_posx, short from_posy, short to_posx, short to_posy );
int army_march_time( int army_index );

// �����о�
void army_march( int army_index );

// �����о�����
void army_reback( int army_index );

// ����ָ���ص�
void army_arrived( int army_index );

// ����о�·��
int army_marchroute_add( int army_index );

// ɾ���о�·��
int army_marchroute_del( int army_index );

// ���²����ٶ�
int army_marchspeed_update( int army_index );

// ��Ӳ�����Ϣ������
int army_enterinfo( int army_index, char *databuf, int *psize );
int army_leaveinfo( int army_index, char *databuf, int *psize );

// ��������
int actor_army_return( int actor_index, int army_index, int unit_index );

// �����ٻ�
int actor_army_callback( int actor_index, int army_index, int itemkind );

// �����о�����
int actor_army_march_speedup( int actor_index, int army_index, int itemkind );

// ����Ԯ�� ǲ��
int actor_helparmy_repatriate( int actor_index, int army_index );

#endif