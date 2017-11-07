#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "db.h"
#include "define.h"
#include "dserver.h"
#include "building.h"
#include "actor.h"
#include "hero.h"
#include "area.h"
#include "actor_send.h"
#include "actor_times.h"
#include "server_netsend_auto.h"
#include "mapunit.h"
#include "fight.h"
#include "actor_notify.h"
#include "item.h"
#include "award.h"
#include "global.h"
#include "quest.h"
#include "activity.h"
#include "system.h"
#include "army.h"
#include "map.h"
#include "map_zone.h"
#include "map_town.h"
#include "mail.h"
#include "city.h"
#include "nation.h"
#include "chat.h"
#include "world_quest.h"
#include "king_war.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern Actor *g_actors;
extern int g_maxactornum;

extern City * g_city;
extern int g_city_maxcount;
extern int g_city_maxindex;

extern Army *g_army;
extern int g_army_maxcount;

extern KingwarTownInfo *g_kingwar_towninfo;
extern int g_kingwar_towninfo_maxnum;

KingwarTown *g_kingwar_town = NULL;
int g_kingwar_town_maxcount = 0;

i64 g_kingwar_lost_totalhp = 0; // ����ʧ����
short g_kingwar_swap_count = 0; // ����������������
int g_kingwar_activity_beginstamp = 0; // ���ʼʱ���
int g_kingwar_activity_endstamp = 0; // �����ʱ���
int g_kingwar_activity_duration = 0; // �����ʱ��
char g_kingwar_activity_open = 0; // ��Ƿ�����

// ������ϵĻص�
int kingwar_town_loadcb( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	return 0;
}

int kingwar_town_load()
{
	g_kingwar_town_maxcount = g_kingwar_towninfo_maxnum;
	g_kingwar_town = (KingwarTown*)malloc( sizeof( KingwarTown ) * g_kingwar_town_maxcount );
	memset( g_kingwar_town, 0, sizeof( KingwarTown ) * g_kingwar_town_maxcount );
	printf_msg( "KingWarTown  maxcount=%d  memory=%0.2fMB(memory=%0.2fKB)\n", g_kingwar_town_maxcount, (sizeof( KingwarTown )*g_kingwar_town_maxcount) / 1024.0 / 1024.0, sizeof( KingwarTown ) / 1024.0 );
	for ( int id = 1; id < g_kingwar_town_maxcount; id++ )
	{
		if ( g_kingwar_towninfo[id].id <= 0 )
			continue;
		g_kingwar_town[id].id = id;
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			g_kingwar_town[id].attack_queue[tmpi] = -1;
			g_kingwar_town[id].defense_queue[tmpi] = -1;
		}
	}
	kingwar_town_load_auto( kingwar_town_getptr, kingwar_town_loadcb, "kingwar_town" );
	return 0;
}

KingwarTown *kingwar_town_getptr( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return NULL;
	return &g_kingwar_town[id];
}

KingwarTownInfo *kingwar_town_getconfig( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return NULL;
	return &g_kingwar_towninfo[id];
}

int kingwar_town_save( FILE *fp )
{
	kingwar_town_batch_save_auto( g_kingwar_town, g_kingwar_town_maxcount, "kingwar_town", fp );
	return 0;
}

int kingwar_town_queueadd( int id, char attack, int army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{ // ��ӵ�������
		int queue_tail = g_kingwar_town[id].attack_queue_tail + 1;
		if ( queue_tail < 0 || queue_tail >= KINGWAR_TOWN_QUEUE_MAX )
		{
			queue_tail = 0;
		}

		if ( g_kingwar_town[id].attack_queue_head == queue_tail )
		{// �������Ѿ�����
			return -1;
		}

		g_kingwar_town[id].attack_queue[g_kingwar_town[id].attack_queue_tail] = army_index;
		g_kingwar_town[id].attack_total += g_army[army_index].totals;

		// β������
		g_kingwar_town[id].attack_queue_tail = queue_tail;
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{ // ��ӵ�������
		int queue_tail = g_kingwar_town[id].defense_queue_tail + 1;
		if ( queue_tail < 0 || queue_tail >= KINGWAR_TOWN_QUEUE_MAX )
		{
			queue_tail = 0;
		}

		if ( g_kingwar_town[id].defense_queue_head == queue_tail )
		{// �������Ѿ�����
			return -1;
		}

		g_kingwar_town[id].defense_queue[g_kingwar_town[id].defense_queue_tail] = army_index;
		g_kingwar_town[id].defense_total += g_army[army_index].totals;

		// β������
		g_kingwar_town[id].defense_queue_tail = queue_tail;
	}
	kingwar_sendinfo( id );
	return 0;
}

// ɾ��һ����ս����
int kingwar_town_queuedel( int id, char attack, int army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			if ( g_kingwar_town[id].attack_queue[tmpi] == army_index )
			{
				g_kingwar_town[id].attack_queue[tmpi] = -1;
				g_kingwar_town[id].attack_total -= g_army[army_index].totals;
				break;
			}
		}
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			if ( g_kingwar_town[id].defense_queue[tmpi] == army_index )
			{
				g_kingwar_town[id].defense_queue[tmpi] = -1;
				g_kingwar_town[id].defense_total -= g_army[army_index].totals;
				break;
			}
		}
	}
	kingwar_sendinfo( id );
	return 0;
}

// �Ƴ�����ͷ
int kingwar_town_queuefetch( int id, char attack )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -2;
	int army_index = -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{
		if ( g_kingwar_town[id].attack_queue_tail == g_kingwar_town[id].attack_queue_head )
			return -2;
		
		if ( g_kingwar_town[id].attack_queue_head < 0 || g_kingwar_town[id].attack_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
			return -2;
		
		// �Ӷ�����ȡ��һ��
		army_index = g_kingwar_town[id].attack_queue[g_kingwar_town[id].attack_queue_head];
		if ( army_index >= 0 && army_index < g_army_maxcount )
		{
			g_kingwar_town[id].attack_total -= g_army[army_index].totals;
			kingwar_sendinfo( id );
		}

		// ͷ������
		g_kingwar_town[id].attack_queue_head++;
		if ( g_kingwar_town[id].attack_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
		{
			g_kingwar_town[id].attack_queue_head = 0;
		}
	}
	else if( attack == KINGWAR_TOWN_DEFENSE )
	{
		if ( g_kingwar_town[id].defense_queue_tail == g_kingwar_town[id].defense_queue_head )
			return -2;

		if ( g_kingwar_town[id].defense_queue_head < 0 || g_kingwar_town[id].defense_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
			return -2;

		// �Ӷ�����ȡ��һ��
		army_index = g_kingwar_town[id].defense_queue[g_kingwar_town[id].defense_queue_head];
		if ( army_index >= 0 && army_index < g_army_maxcount )
		{
			g_kingwar_town[id].defense_total -= g_army[army_index].totals;
			kingwar_sendinfo( id );
		}

		// ͷ������
		g_kingwar_town[id].defense_queue_head++;
		if ( g_kingwar_town[id].defense_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
		{
			g_kingwar_town[id].defense_queue_head = 0;
		}
	}
	
	return army_index;
}

// ��ȡ����ͷ����
int kingwar_town_queueget( int id, char attack )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	int army_index = -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{
		if ( g_kingwar_town[id].attack_queue_head < 0 || g_kingwar_town[id].attack_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
			return -1;

		// �Ӷ�����ȡ��һ��
		army_index = g_kingwar_town[id].attack_queue[g_kingwar_town[id].attack_queue_head];
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{
		if ( g_kingwar_town[id].defense_queue_head < 0 || g_kingwar_town[id].defense_queue_head >= KINGWAR_TOWN_QUEUE_MAX )
			return -1;

		// �Ӷ�����ȡ��һ��
		army_index = g_kingwar_town[id].defense_queue[g_kingwar_town[id].defense_queue_head];
	}

	return army_index;
}

// ��������
int kingwar_town_queueswap( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;

	int temp[KINGWAR_TOWN_QUEUE_MAX];
	memcpy( temp, g_kingwar_town[id].attack_queue, sizeof( int )*KINGWAR_TOWN_QUEUE_MAX );
	memcpy( g_kingwar_town[id].attack_queue, g_kingwar_town[id].defense_queue, sizeof( int )*KINGWAR_TOWN_QUEUE_MAX );
	memcpy( g_kingwar_town[id].defense_queue, temp, sizeof( int )*KINGWAR_TOWN_QUEUE_MAX );

	int temp_head = g_kingwar_town[id].attack_queue_head;
	g_kingwar_town[id].attack_queue_head = g_kingwar_town[id].defense_queue_head;
	g_kingwar_town[id].defense_queue_head = temp_head;

	int temp_tail = g_kingwar_town[id].attack_queue_tail;
	g_kingwar_town[id].attack_queue_tail = g_kingwar_town[id].defense_queue_tail;
	g_kingwar_town[id].defense_queue_tail = temp_tail;

	int temp_totals = g_kingwar_town[id].attack_total;
	g_kingwar_town[id].attack_total = g_kingwar_town[id].defense_total;
	g_kingwar_town[id].defense_total = temp_totals;
	kingwar_sendinfo( id );
	return 0;
}

// ��߼���ÿ��
void kingwar_activity_logic()
{
	if ( worldquest_check_server( WORLDQUEST_WORLDBOSS2 ) == 0 )
	{ // ��������׿
		return;
	}

	time_t t;
	time( &t );
	struct tm *nowtime = localtime( &t );
	if ( nowtime->tm_wday != global.kingwar_activity_week )
		return;

	// ���ʼ
	if ( nowtime->tm_hour == global.kingwar_activity_hour && nowtime->tm_min == global.kingwar_activity_minute && nowtime->tm_sec == 0 )
	{ 
		kingwar_activity_onopen();
		return;
	}

	// �����
	int nowstamp = (int)time( NULL );
	if ( g_kingwar_activity_open == 1 && nowstamp >= g_kingwar_activity_endstamp )
	{
		kingwar_activity_onclose();
		return;
	}

	// �ڻ��
	if ( nowstamp >= g_kingwar_activity_beginstamp && nowstamp <= g_kingwar_activity_endstamp )
	{

	}
}

// �����
int kingwar_activity_onopen()
{
	g_kingwar_activity_open = 1;
	g_kingwar_lost_totalhp = 0; // ����ʧ����
	g_kingwar_swap_count = 0; // ����������������
	g_kingwar_activity_beginstamp = (int)time( NULL ); // ��տ�ʼʱ���
	g_kingwar_activity_endstamp = g_kingwar_activity_beginstamp + global.kingwar_activity_duration; // �����ʱ���
	g_kingwar_activity_duration = global.kingwar_activity_duration; // �����ʱ��

	kingwar_activity_sendinfo( -1 );
	return 0;
}

// �����
int kingwar_activity_onclose()
{
	g_kingwar_activity_open = 0;
	kingwar_activity_sendinfo( -1 );
	return 0;
}

// ���Ϣ
int kingwar_activity_sendinfo( int actor_index )
{
	// ��������׿
	if ( worldquest_check_server( WORLDQUEST_WORLDBOSS2 ) == 0 )
		return -1;

	time_t t;
	time( &t );
	struct tm *nowtime = localtime( &t );
	if ( nowtime->tm_wday != global.kingwar_activity_week )
		return -1;

	SLK_NetS_KingWarActivity pValue = { 0 };
	time_t activity_t;
	time( &activity_t );
	struct tm *activitytime = localtime( &activity_t );
	// ���»��ʼʱ���
	struct tm BeginTm = { 0 };
	BeginTm.tm_year = nowtime->tm_year;
	BeginTm.tm_mon = nowtime->tm_mon;
	BeginTm.tm_mday = nowtime->tm_mday;
	BeginTm.tm_hour = global.kingwar_activity_hour;
	BeginTm.tm_min = global.kingwar_activity_minute;
	BeginTm.tm_sec = 0;
	int beginstamp = (int)mktime( &BeginTm );
	int nowstamp = (int)time( NULL );
	// �δ��ʼ
	if ( nowstamp < beginstamp )
	{
		pValue.m_state = 0;
		pValue.m_beginstamp = beginstamp;
		pValue.m_endstamp = 0;
	}
	// ���
	else if ( nowstamp >= g_kingwar_activity_beginstamp && nowstamp <= g_kingwar_activity_endstamp )
	{
		pValue.m_state = 1;
		pValue.m_beginstamp = g_kingwar_activity_beginstamp;
		pValue.m_endstamp = g_kingwar_activity_endstamp;
	}
	else
	{ // �����
		pValue.m_state = 2;
	}

	if ( actor_index >= 0 && actor_index < g_maxactornum )
	{
		netsend_kingwaractivity_S( actor_index, SENDTYPE_ACTOR, &pValue );
	}
	else
	{
		netsend_kingwaractivity_S( 0, SENDTYPE_WORLDMAP, &pValue );
	}
	return 0;
}

int kingwar_sendinfo( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	SLK_NetS_KingwarTown pValue = { 0 };
	pValue.m_id = id;
	pValue.m_nation = g_kingwar_town[id].nation;
	pValue.m_attack_total = g_kingwar_town[id].attack_total;
	pValue.m_defense_total = g_kingwar_town[id].defense_total;
	netsend_kingwartown_S( SUBSCRIBE_CMD_KINGWARDLG, SENDTYPE_SUBSCRIBE, &pValue );
	return 0;
}

int kingwar_sendlist( int actor_index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	SLK_NetS_KingwarTownList pValue = { 0 };
	for ( int id = 4; id < g_kingwar_town_maxcount; id++ )
	{
		pValue.m_list[pValue.m_count].m_id = id;
		pValue.m_list[pValue.m_count].m_nation = g_kingwar_town[id].nation;
		pValue.m_list[pValue.m_count].m_attack_total = g_kingwar_town[id].attack_total;
		pValue.m_list[pValue.m_count].m_defense_total = g_kingwar_town[id].defense_total;
		pValue.m_count += 1;
	}
	netsend_kingwartownlist_S( actor_index, SENDTYPE_ACTOR, &pValue );
	g_actors[actor_index].subscribe_cmd[SUBSCRIBE_CMD_KINGWARDLG] = 1;
	return 0;
}

// ȡ������
int kingwar_subscribe_cancel( int actor_index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	g_actors[actor_index].subscribe_cmd[SUBSCRIBE_CMD_KINGWARDLG] = 0;
	return 0;
}

