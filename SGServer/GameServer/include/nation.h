#ifndef _NATION_H_
#define _NATION_H_
#include "define.h"

#define NATION_MAX			4		// ��Ⱥ��4������
#define NATION_NOTICE_MAX	512		// ����
#define NATION_OFFICIAL_MAX	16		// ��Ա����
#define NATION_TOWN_WAR_MAX	256		// ��ս����
#define NATION_CITY_WAR_MAX	1024	// ��ս����

int nation_load();
int nation_save( FILE *fp );
Nation *nation_getptr( int nation );

// ���ù��Ҷ���
int nation_capital_townid( int nation, int townid );
int nation_capital_townid_get( int nation );

// �����˿�
int nation_people_calc( int nation );
int nation_people_get( int nation );
int nation_people_famous_calc( int nation );
int nation_people_capital_calc( int nation );
int nation_people_capital_set( int nation, int people );

// �ù���ָ�����ͳǳ�����
int nation_town_num( int nation, int towntype );

// ��ս������Ϣ
int nation_city_war_add( int nation, int group_index );
int nation_city_war_del( int nation, int group_index );

// ��ս������Ϣ
int nation_town_war_add( int nation, int group_index );
int nation_town_war_del( int nation, int group_index );


#endif
