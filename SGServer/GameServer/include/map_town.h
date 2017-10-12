#ifndef _MAP_TOWN_H_
#define _MAP_TOWN_H_
#include "define.h"

#define MAP_TOWN_JOIN_MAX	128	// ��ս��Ա
#define MAP_TOWN_MONSTER_MAX	16	// ��������

int map_town_load();
int map_town_save( FILE *fp );
MapTown *map_town_getptr( int townid );

// ��ʾ��Ԫ����
void map_town_makeunit( int index, SLK_NetS_AddMapUnit *pAttr );

// λ��
void map_town_getpos( int index, short *posx, short *posy );

// �����ؾ�
void map_town_monster_reset( int townid );

// ���г���ÿ���߼�
void map_town_alllogic();

// �������
int map_town_ask_owner( int actor_index, int townid );

// �������
int map_town_alloc_owner( int townid );

// ��������
int map_town_owner_leave( int actor_index, int townid );

// ����
int map_town_soldiers_repair( int actor_index, int townid );

// ��������
int map_town_levy( int actor_index, int townid );

// ��ȡ������
int map_town_sendaward( int actor_index, int townid );

// ��ȡ������Ϣ
int map_town_sendinfo( int actor_index, int townid );

// �����б�
int map_town_ask_owner_sendlist( int actor_index, int townid );
#endif
