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
extern int g_army_maxindex;
extern Fight g_fight;

extern KingwarTownInfo *g_kingwar_towninfo;
extern int g_kingwar_towninfo_maxnum;

extern MapTownInfo *g_towninfo;
extern int g_towninfo_maxnum;

extern MapTown *g_map_town;
extern int g_map_town_maxcount;

extern KingWarConfig *g_kingwar_config;
extern int g_kingwar_config_maxnum;

KingwarTown *g_kingwar_town = NULL;
int g_kingwar_town_maxcount = 0;

int g_kingwar_lost_totalhp = 0; // ����ʧ����
int g_kingwar_activity_beginstamp = 0; // ���ʼʱ���
int g_kingwar_activity_endstamp = 0; // �����ʱ���
int g_kingwar_activity_duration = 0; // �����ʱ��
char g_kingwar_activity_open = 0; // ��Ƿ�����
char g_kingwar_town_update = 0;

// ������ϵĻص�
int kingwar_town_loadcb( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	return 0;
}

int kingwar_town_load()
{
	kingwar_activity_load();
	g_kingwar_town_maxcount = g_kingwar_towninfo_maxnum;
	g_kingwar_town = (KingwarTown*)malloc( sizeof( KingwarTown ) * g_kingwar_town_maxcount );
	memset( g_kingwar_town, 0, sizeof( KingwarTown ) * g_kingwar_town_maxcount );
	printf_msg( "KingWarTown  maxcount=%d  memory=%0.2fMB(memory=%0.2fKB)\n", g_kingwar_town_maxcount, (sizeof( KingwarTown )*g_kingwar_town_maxcount) / 1024.0 / 1024.0, sizeof( KingwarTown ) / 1024.0 );
	for ( int id = 1; id < g_kingwar_town_maxcount; id++ )
	{
		if ( g_kingwar_towninfo[id].id <= 0 )
			continue;
		g_kingwar_town[id].id = id;
		g_kingwar_town[id].nation = (char)g_kingwar_towninfo[id].base_nation;
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
	kingwar_activity_save( fp );
	return 0;
}

char kingwar_town_attack_or_defense( int id, int army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	if ( g_kingwar_town[id].nation == army_getnation( army_index ) )
	{
		return 2;
	}
	return 1;
}

int kingwar_town_queueadd( int id, char attack, int army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{ // ��ӵ�������
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			if ( g_kingwar_town[id].attack_queue[tmpi] < 0 )
			{
				g_kingwar_town[id].attack_queue[tmpi] = army_index;
				g_kingwar_town[id].attack_total += g_army[army_index].totals;
				g_army[army_index].to_id = id;
				g_army[army_index].to_index = id;
				g_army[army_index].state = ARMY_STATE_KINGWAR_FIGHT;
				g_army[army_index].move_total_distance = tmpi;
				break;
			}
		}
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{ // ��ӵ�������
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			if ( g_kingwar_town[id].defense_queue[tmpi] < 0 )
			{
				g_kingwar_town[id].defense_queue[tmpi] = army_index;
				g_kingwar_town[id].defense_total += g_army[army_index].totals;
				g_army[army_index].to_id = id;
				g_army[army_index].to_index = id;
				g_army[army_index].state = ARMY_STATE_KINGWAR_FIGHT;
				g_army[army_index].move_total_distance = tmpi;
				break;
			}
		}
	}
	return 0;
}

// ɾ��һ����ս����
int kingwar_town_queuedel( int id, char attack, int army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	char isdelete = 0;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			if ( g_kingwar_town[id].attack_queue[tmpi] == army_index )
			{
				g_kingwar_town[id].attack_queue[tmpi] = -1;
				if ( tmpi < KINGWAR_TOWN_QUEUE_MAX - 1 )
				{
					memmove( &g_kingwar_town[id].attack_queue[tmpi], &g_kingwar_town[id].attack_queue[tmpi + 1], sizeof(int) *(KINGWAR_TOWN_QUEUE_MAX - 1 - tmpi) );
					g_kingwar_town[id].attack_queue[KINGWAR_TOWN_QUEUE_MAX - 1] = -1;
				}
				isdelete = 1;
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
				if ( tmpi < KINGWAR_TOWN_QUEUE_MAX - 1 )
				{
					memmove( &g_kingwar_town[id].defense_queue[tmpi], &g_kingwar_town[id].defense_queue[tmpi + 1], sizeof( int ) *(KINGWAR_TOWN_QUEUE_MAX - 1 - tmpi) );
					g_kingwar_town[id].defense_queue[KINGWAR_TOWN_QUEUE_MAX - 1] = -1;
				}
				isdelete = 1;
				break;
			}
		}
	}
	// ��ȫ���� 
	if ( isdelete == 0 )
	{
		if ( attack == KINGWAR_TOWN_ATTACK )
		{
			for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
			{
				if ( g_kingwar_town[id].defense_queue[tmpi] == army_index )
				{
					g_kingwar_town[id].defense_queue[tmpi] = -1;
					if ( tmpi < KINGWAR_TOWN_QUEUE_MAX - 1 )
					{
						memmove( &g_kingwar_town[id].defense_queue[tmpi], &g_kingwar_town[id].defense_queue[tmpi + 1], sizeof( int ) *(KINGWAR_TOWN_QUEUE_MAX - 1 - tmpi) );
						g_kingwar_town[id].defense_queue[KINGWAR_TOWN_QUEUE_MAX - 1] = -1;
					}
					break;
				}
			}
		}
		else if( attack == KINGWAR_TOWN_DEFENSE )
		{
			for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
			{
				if ( g_kingwar_town[id].attack_queue[tmpi] == army_index )
				{
					g_kingwar_town[id].attack_queue[tmpi] = -1;
					if ( tmpi < KINGWAR_TOWN_QUEUE_MAX - 1 )
					{
						memmove( &g_kingwar_town[id].attack_queue[tmpi], &g_kingwar_town[id].attack_queue[tmpi + 1], sizeof( int ) *(KINGWAR_TOWN_QUEUE_MAX - 1 - tmpi) );
						g_kingwar_town[id].attack_queue[KINGWAR_TOWN_QUEUE_MAX - 1] = -1;
					}
					break;
				}
			}
		}
	}
	kingwar_town_totalcalc( id, attack );
	return 0;
}

// ��ȡ����ͷ����
int kingwar_town_queueget( int id, char attack )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	int army_index = -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{
		army_index = g_kingwar_town[id].attack_queue[0];
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{
		// �Ӷ�����ȡ��һ��
		army_index = g_kingwar_town[id].defense_queue[0];
	}
	return army_index;
}

// ���¼������
int kingwar_town_totalcalc( int id, char attack )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( attack == KINGWAR_TOWN_ATTACK )
	{ // ������
		g_kingwar_town[id].attack_total = 0;
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			int army_index = g_kingwar_town[id].attack_queue[tmpi];
			if ( army_index < 0 || army_index >= g_army_maxcount )
				break;
			g_kingwar_town[id].attack_total += g_army[army_index].totals;
		}
	}
	else if ( attack == KINGWAR_TOWN_DEFENSE )
	{ // ������
		g_kingwar_town[id].defense_total = 0;
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			int army_index = g_kingwar_town[id].defense_queue[tmpi];
			if ( army_index < 0 || army_index >= g_army_maxcount )
				break;
			g_kingwar_town[id].defense_total += g_army[army_index].totals;
		}
	}
	return 0;
}

// �ı����
int kingwar_town_change_nation( int id, int nation, int attack_army_index )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_kingwar_town[id].nation == nation )
		return -1;
	if ( g_kingwar_town[id].defense_queue[0] >= 0 )
		return -1;
	char oldnation = g_kingwar_town[id].nation;
	g_kingwar_town[id].nation = nation;
	g_kingwar_town[id].attack_total = 0;
	g_kingwar_town[id].defense_total = 0;

	int temp[KINGWAR_TOWN_QUEUE_MAX];
	int temp_total = 0;
	int temp_index = 0;
	for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
	{
		temp[tmpi] = -1;
	}

	// �ѹ�������������������ҵ�������,�ŵ�����������
	int index = 0;
	for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
	{
		int army_index = g_kingwar_town[id].attack_queue[tmpi];
		if ( army_index < 0 || army_index >= g_army_maxcount )
			continue;
		if ( army_getnation( army_index ) == nation )
		{
			g_kingwar_town[id].defense_queue[index] = army_index;
			g_kingwar_town[id].defense_total += g_army[army_index].totals;
			index += 1;
		}
		else
		{
			temp[temp_index] = army_index;
			temp_total += g_army[army_index].totals;
			temp_index += 1;
		}
		g_kingwar_town[id].attack_queue[tmpi] = -1;
	}


	memcpy( g_kingwar_town[id].attack_queue, temp, sizeof( int )*KINGWAR_TOWN_QUEUE_MAX );
	g_kingwar_town[id].attack_total = temp_total;

	// �ݵ㷢���������ôʧ�ܷ��ľ�Ԯ�佫��Ҫ�ƶ��������ȴ���Ԯ
	for ( int army_index = 0; army_index < g_army_maxindex/*ע�⣺ʹ������λ�ã�Ϊ��Ч��*/; army_index++ )
	{
		if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS && g_army[army_index].to_id == id )
		{
			char army_nation = army_getnation( army_index );
			if ( army_nation != nation )
			{
				g_army[army_index].to_id = army_nation;
				g_army[army_index].to_index = army_nation;
				city_battlequeue_sendupdate( army_index );
			}
		}
	}

	if ( id == 7 )
	{ // �����������棬����ʱ��
		if ( g_kingwar_activity_duration < global.kingwar_activity_duration_max )
		{
			g_kingwar_activity_duration += global.kingwar_activity_duration;
			g_kingwar_activity_endstamp += global.kingwar_activity_duration;
		}
	}
	// {0}�ڻʳ�Ѫս�з��µ��ȣ�����ʿ�䣬�ղ�����������{1}{2}�ݵ�
	if ( attack_army_index >= 0 && attack_army_index < g_army_maxcount )
	{
		char v1[32] = { 0 };
		char v2[32] = { 0 };
		char v3[32] = { 0 };
		City *pCity = army_getcityptr( attack_army_index );
		if ( pCity )
			sprintf( v1, "%s", pCity->name );
		sprintf( v2, "%s%d", TAG_NATION, oldnation );
		sprintf( v3, "%s%d", TAG_KINGWAR, id );
		system_talkjson_world( 6010, v1, v2, v3, NULL, NULL, NULL, 1 );
	}
	g_kingwar_town_update = 1;
	return 0;
}

void kingwar_town_fight( int id )
{
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return;
	int attack_army_index = -1;
	int defense_army_index = -1;

	// ��ȡ������
	attack_army_index = kingwar_town_queueget( id, KINGWAR_TOWN_ATTACK );
	if ( attack_army_index < 0 )
		return;

	// ��ȡ������
	defense_army_index = kingwar_town_queueget( id, KINGWAR_TOWN_DEFENSE );
	if ( defense_army_index < 0 )
	{
		// ������û���ˣ���ɹ�������
		kingwar_town_change_nation( id, army_getnation( attack_army_index ), attack_army_index );
		return;
	}

	// ˫�������ˣ�ս��
	if ( fight_start( attack_army_index, MAPUNIT_TYPE_KINGWAR_TOWN, defense_army_index ) < 0 )
	{
		return;
	}

	// ս������
	fight_lost_calc();

	// ����ʧ����
	g_kingwar_lost_totalhp += g_fight.attack_total_damage;
	g_kingwar_lost_totalhp += g_fight.defense_total_damage;

	if ( g_fight.result == FIGHT_WIN )
	{ // ������ʤ��
		kingwar_town_totalcalc( id, KINGWAR_TOWN_ATTACK );
		// ɾ��һ�����ط�����
		kingwar_town_queuedel( id, KINGWAR_TOWN_DEFENSE, defense_army_index );
		g_army[defense_army_index].state = ARMY_STATE_KINGWAR_WAITSOS;
		g_army[defense_army_index].statetime = 0;
		g_army[defense_army_index].stateduration = global.kingwar_dead_cd;
	}
	else
	{ // ������ʤ��
		kingwar_town_totalcalc( id, KINGWAR_TOWN_DEFENSE );
		// ɾ��һ������������
		kingwar_town_queuedel( id, KINGWAR_TOWN_ATTACK, attack_army_index );
		g_army[attack_army_index].state = ARMY_STATE_KINGWAR_WAITSOS;
		g_army[attack_army_index].statetime = 0;
		g_army[attack_army_index].stateduration = global.kingwar_dead_cd;
	}
	city_battlequeue_sendupdate( attack_army_index );
	city_battlequeue_sendupdate( defense_army_index );
	g_kingwar_town_update = 1;

	// ս��֪ͨ
	SLK_NetS_KingWarNotify pValue = { 0 }; 
	pValue.m_id = id;
	pValue.m_result = g_fight.result;

	pValue.m_a_losthp = g_fight.defense_total_damage;
	pValue.m_d_losthp = g_fight.attack_total_damage;

	pValue.m_a_nation = army_getnation( attack_army_index );
	pValue.m_d_nation = army_getnation( defense_army_index );

	pValue.m_a_heroid = g_army[attack_army_index].herokind[0];
	pValue.m_d_heroid = g_army[defense_army_index].herokind[0];

	City *pACity = army_getcityptr( attack_army_index );
	if ( pACity )
	{
		pValue.m_a_color = hero_getcolor( pACity, pValue.m_a_heroid );
		strncpy( pValue.m_a_name, pACity->name, NAME_SIZE );
		pValue.m_a_name_len = strlen( pValue.m_a_name );
	}

	City *pDCity = army_getcityptr( defense_army_index );
	if ( pDCity )
	{
		pValue.m_d_heroid = hero_getcolor( pDCity, pValue.m_d_heroid );
		strncpy( pValue.m_d_name, pDCity->name, NAME_SIZE );
		pValue.m_d_name_len = strlen( pValue.m_d_name );
	}
	
	netsend_kingwarnotify_S( SUBSCRIBE_CMD_KINGWARDLG, SENDTYPE_SUBSCRIBE_NATION + pValue.m_a_nation, &pValue );
	netsend_kingwarnotify_S( SUBSCRIBE_CMD_KINGWARDLG, SENDTYPE_SUBSCRIBE_NATION + pValue.m_d_nation, &pValue );
}

void kingwar_town_logic()
{
	for ( int id = 4; id < g_kingwar_town_maxcount; id++ )
	{
		kingwar_town_fight( id );
	}
}

// ���Ϣ
int kingwar_activity_load()
{
	MYSQL_RES		*res;
	MYSQL_ROW		row;
	char	szSQL[1024];
	sprintf( szSQL, "select open, beginstamp, endstamp, duration, lost_totalhp from kingwar_activity;" );
	if ( mysql_query( myGame, szSQL ) )
	{
		printf_msg( "Query failed (%s)\n", mysql_error( myGame ) );
		write_gamelog( "%s", szSQL );
		return -1;
	}
	res = mysql_store_result( myGame );
	while ( (row = mysql_fetch_row( res )) )
	{
		g_kingwar_activity_open = atoi( row[0] );
		g_kingwar_activity_beginstamp = atoi( row[1] );
		g_kingwar_activity_endstamp = atoi( row[2] );
		g_kingwar_activity_duration = atoi( row[3] );
		g_kingwar_lost_totalhp = atoi( row[4] );
	}
	mysql_free_result( res );
	return 0;
}
int kingwar_activity_save( FILE *fp )
{
	char szSQL[1024];
	char bigint[21];
	sprintf( szSQL, "replace into kingwar_activity ( open,beginstamp,endstamp,duration,lost_totalhp ) values('%d','%d','%d','%d','%d');",
		g_kingwar_activity_open, g_kingwar_activity_beginstamp, g_kingwar_activity_endstamp, g_kingwar_activity_duration, g_kingwar_lost_totalhp );
	if ( fp )
	{
		fprintf( fp, "%s;\n", szSQL );
	}
	else if ( mysql_query( myGame, szSQL ) )
	{
		printf_msg( "Query failed (%s)\n", mysql_error( myGame ) );
		write_gamelog( "%s", szSQL );
		if ( mysql_ping( myGame ) != 0 )
			db_reconnect_game();
		return -1;
	}
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
		// �����߼�
		kingwar_town_logic();
		// ÿ�뷢��һ��
		if ( g_kingwar_town_update == 1 )
		{
			kingwar_town_sendall();
			g_kingwar_town_update = 0;
		}
	}
}

// �����
int kingwar_activity_onopen()
{
	g_kingwar_activity_open = 1;
	g_kingwar_lost_totalhp = 0; // ����ʧ����
	g_kingwar_activity_beginstamp = (int)time( NULL ); // ��տ�ʼʱ���
	g_kingwar_activity_endstamp = g_kingwar_activity_beginstamp + global.kingwar_activity_duration; // �����ʱ���
	g_kingwar_activity_duration = global.kingwar_activity_duration; // �����ʱ��

	for ( int id = 1; id < g_kingwar_town_maxcount; id++ )
	{
		if ( g_kingwar_towninfo[id].id <= 0 )
			continue;
		if ( id == 7 )
		{
			g_kingwar_town[id].nation = (char)map_town_getnation( MAPUNIT_KING_TOWNID );
		}
		else
		{
			g_kingwar_town[id].nation = (char)g_kingwar_towninfo[id].base_nation;
		}
		for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
		{
			g_kingwar_town[id].attack_queue[tmpi] = -1;
			g_kingwar_town[id].defense_queue[tmpi] = -1;
		}
	}
	kingwar_activity_sendinfo( -1 );
	system_talkjson_world( 6008, NULL, NULL, NULL, NULL, NULL, NULL, 1 );
	return 0;
}

// �����
int kingwar_activity_onclose()
{
	g_kingwar_activity_open = 0;
	kingwar_activity_sendinfo( -1 );

	// ���л���ӽ�ɢ
	for ( int army_index = 0; army_index < g_army_maxindex/*ע�⣺ʹ������λ�ã�Ϊ��Ч��*/; army_index++ )
	{
		if ( g_army[army_index].action == ARMY_ACTION_KINGWAR )
		{
			g_army[army_index].state = ARMY_STATE_KINGWAR_READY;
			army_delete( army_index );
		}
	}

	g_map_town[MAPUNIT_KING_TOWNID].nation = g_kingwar_town[7].nation;
	// �������Ȧ����
	map_tile_setnation( g_towninfo[MAPUNIT_KING_TOWNID].posx, g_towninfo[MAPUNIT_KING_TOWNID].posy, g_towninfo[MAPUNIT_KING_TOWNID].range, MAPUNIT_KING_TOWNID, g_map_town[MAPUNIT_KING_TOWNID].nation );
	// ���Ľ���������������
	map_zone_setnation( map_zone_getid( g_towninfo[MAPUNIT_KING_TOWNID].posx, g_towninfo[MAPUNIT_KING_TOWNID].posy ), g_map_town[MAPUNIT_KING_TOWNID].nation );
	// �����ʳ����򶼳Ǻ����Ǹ���
	map_zone_center_townchange( MAPUNIT_KING_TOWNID );

	// {0}��Ѫս�ʳ��л�ʤ���ɹ�ռ����������
	char v1[32] = { 0 };
	sprintf( v1, "%s%d", TAG_NATION, g_map_town[MAPUNIT_KING_TOWNID].nation );
	system_talkjson_world( 6009, NULL, NULL, NULL, NULL, NULL, NULL, 1 );
	return 0;
}

// �ڻ��
int kingwar_activity_inttime()
{
	time_t t;
	time( &t );
	struct tm *nowtime = localtime( &t );
	if ( nowtime->tm_wday == global.kingwar_activity_week )
	{
		int nowstamp = (int)time( NULL );
		if ( nowstamp >= g_kingwar_activity_beginstamp && nowstamp <= g_kingwar_activity_endstamp )
		{
			return 1;
		}
	}
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

int kingwar_town_sendinfo( int id )
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

int kingwar_town_sendall()
{
	SLK_NetS_KingwarTownList pValue = { 0 };
	for ( int id = 4; id < g_kingwar_town_maxcount; id++ )
	{
		pValue.m_list[pValue.m_count].m_id = id;
		pValue.m_list[pValue.m_count].m_nation = g_kingwar_town[id].nation;
		pValue.m_list[pValue.m_count].m_attack_total = g_kingwar_town[id].attack_total;
		pValue.m_list[pValue.m_count].m_defense_total = g_kingwar_town[id].defense_total;
		pValue.m_count += 1;
	}
	pValue.m_leftstamp = g_kingwar_activity_endstamp - (int)time( NULL );
	pValue.m_losthp = g_kingwar_lost_totalhp;
	netsend_kingwartownlist_S( SUBSCRIBE_CMD_KINGWARDLG, SENDTYPE_SUBSCRIBE, &pValue );
	return 0;
}

int kingwar_town_sendlist( int actor_index )
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
	pValue.m_leftstamp = g_kingwar_activity_endstamp - (int)time( NULL );
	pValue.m_losthp = g_kingwar_lost_totalhp;
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

// ǰ��
int kingwar_army_goto( int actor_index, int army_index, int id )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( army_myself( actor_index, army_index ) < 0 )
		return -1;
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	int oldid = g_army[army_index].to_id;
	if ( oldid >= 4 && oldid < g_kingwar_town_maxcount )
	{ // ���Ӣ���ھݵ��ϣ����ҵ�ǰս��״̬����ô������ʹ��ǰ����ֻ��ʹ�ûط�
		if ( g_kingwar_town[oldid].attack_queue[0] >= 0 && g_kingwar_town[oldid].defense_queue[0] >= 0 )
		{
			char v1[32] = { 0 };
			sprintf( v1, "%d", global.kingwar_token_def );
			actor_notify_msgbox_v( actor_index, MSGBOX_CALLBACK_KINGWAR_DEFENSE, army_index, id, 1410, v1, NULL );
			return -1;
		}
	}
	else
	{ // Ӣ���ڼ�����ϣ�ֻ��ǰ����Ӧ·�ߵľݵ�
		if ( pCity->nation == 1 )
		{
			if ( id != 4 )
			{
				return -1;
			}
		}
		else if ( pCity->nation == 2 )
		{
			if ( id != 5 )
			{
				return -1;
			}
		}
		else if ( pCity->nation == 3 )
		{
			if ( id != 6 )
			{
				return -1;
			}
		}
	}

	if ( g_kingwar_town[id].nation == pCity->nation )
	{ // ���ҹ�ռ�죬���������
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_DEFENSE, army_index ) < 0 )
			return -1;
	}
	else if ( g_kingwar_town[id].nation == 0 && g_kingwar_town[id].defense_queue[0] < 0 )
	{ // ��Ⱥ��ռ�죬����û�˷��أ���Ϊ��ʼ״̬��ֱ�Ӽ��������
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_DEFENSE, army_index ) < 0 )
			return -1;
		g_kingwar_town[id].nation = pCity->nation;
	}
	else
	{ // ���빥����
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_ATTACK, army_index ) < 0 )
			return -1;
	}
	city_battlequeue_sendupdate( army_index );
	g_kingwar_town_update = 1;
	return 0;
}

// ����
int kingwar_army_attack( int actor_index, int army_index, int id )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( army_myself( actor_index, army_index ) < 0 )
		return -1;
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}

	int oldid = g_army[army_index].to_id;
	if ( oldid >= 4 && oldid < g_kingwar_town_maxcount )
	{ // ���Ӣ���ھݵ��ϣ����ҵ�ǰս��״̬����ô������ʹ�ý�����ֻ��ʹ��͵Ϯ
		if ( g_kingwar_town[oldid].attack_queue[0] >= 0 && g_kingwar_town[oldid].defense_queue[0] >= 0 )
		{
			char v1[32] = { 0 };
			sprintf( v1, "%d", global.kingwar_token_sneak );
			actor_notify_msgbox_v( actor_index, MSGBOX_CALLBACK_KINGWAR_SNEAK, army_index, id, 1411, v1, NULL );
			return -1;
		}
	}

	if ( g_kingwar_town[id].nation == pCity->nation )
	{ // ���ҹ�ռ�죬���������
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_DEFENSE, army_index ) < 0 )
			return -1;
	}
	else if ( g_kingwar_town[id].nation == 0 && g_kingwar_town[id].defense_queue[0] < 0 )
	{ // ��Ⱥ��ռ�죬����û�˷��أ���Ϊ��ʼ״̬��ֱ�Ӽ��������
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_DEFENSE, army_index ) < 0 )
			return -1;
		g_kingwar_town[id].nation = pCity->nation;
	}
	else
	{ // ���빥����
		kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
		if ( kingwar_town_queueadd( id, KINGWAR_TOWN_ATTACK, army_index ) < 0 )
			return -1;
	}
	city_battlequeue_sendupdate( army_index );
	g_kingwar_town_update = 1;
	return 0;
}

// ͵Ϯ
int kingwar_army_sneak( int actor_index, int army_index, int id )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( army_myself( actor_index, army_index ) < 0 )
		return -1;
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	if ( g_army[army_index].state != ARMY_STATE_KINGWAR_FIGHT )
		return -1;
	int oldid = g_army[army_index].to_id;
	if ( army_index == g_kingwar_town[oldid].attack_queue[0] || army_index == g_kingwar_town[oldid].defense_queue[0] )
	{ // ���佫�Ѿ������޷�����͵Ϯ
		actor_notify_alert( actor_index, 1404 );
		return -1;
	}
	if ( oldid >= 4 && oldid < g_kingwar_town_maxcount )
	{ // ���Ӣ���ھݵ��ϣ����ҵ�ǰ��ս��״̬�ˣ�ֱ��ת��Ϊ��������������ʯ
		if ( g_kingwar_town[oldid].attack_queue[0] < 0 )
		{
			kingwar_army_attack( actor_index, army_index, id );
			return -1;
		}
	}

	if ( g_kingwar_town[id].nation == pCity->nation )
	{ // ���������ף�͵Ϯ���ڻط�
		kingwar_army_defense( actor_index, army_index, id );
		return -1;
	}

	if ( g_actors[actor_index].token < global.kingwar_token_sneak )
	{
		actor_notify_alert( actor_index, 645 );
		return -1;
	}
	
	// ɾ��֮ǰ����
	kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
	if ( kingwar_town_queueadd( id, KINGWAR_TOWN_ATTACK, army_index ) < 0 )
		return -1;
	actor_change_token( actor_index, -global.kingwar_token_sneak, PATH_KINGWAR_SNEAK, 0 );
	city_battlequeue_sendupdate( army_index );
	g_kingwar_town_update = 1;
	return 0;
}

// �ط�
int kingwar_army_defense( int actor_index, int army_index, int id )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( army_myself( actor_index, army_index ) < 0 )
		return -1;
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	if ( g_army[army_index].state != ARMY_STATE_KINGWAR_FIGHT )
		return -1;

	int oldid = g_army[army_index].to_id;
	if ( army_index == g_kingwar_town[oldid].attack_queue[0] || army_index == g_kingwar_town[oldid].defense_queue[0] )
	{ // ���佫�Ѿ������޷����лط�
		actor_notify_alert( actor_index, 1405 );
		return -1;
	}
	if ( oldid >= 4 && oldid < g_kingwar_town_maxcount )
	{ // ���Ӣ���ھݵ��ϣ����ҵ�ǰ��ս��״̬�ˣ�ֱ��ת��Ϊǰ������������ʯ
		if ( g_kingwar_town[oldid].attack_queue[0] < 0 )
		{
			kingwar_army_goto( actor_index, army_index, id );
			return -1;
		}
	}

	if ( g_kingwar_town[id].nation != pCity->nation )
	{ // �þݵ��Ѿ����ݣ��޷��ط�
		actor_notify_alert( actor_index, 1409 );
		return -1;
	}

	if ( g_actors[actor_index].token < global.kingwar_token_def )
	{
		actor_notify_alert( actor_index, 645 );
		return -1;
	}

	// ɾ��֮ǰ����
	kingwar_town_queuedel( oldid, kingwar_town_attack_or_defense( oldid, army_index ), army_index );
	if ( kingwar_town_queueadd( id, KINGWAR_TOWN_DEFENSE, army_index ) < 0 )
		return -1;
	actor_change_token( actor_index, -global.kingwar_token_def, PATH_KINGWAR_DEFENSE, 0 );
	city_battlequeue_sendupdate( army_index );
	g_kingwar_town_update = 1;
	return 0;
}

// ����
int kingwar_army_pk( int actor_index, int army_index, int id )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( army_myself( actor_index, army_index ) < 0 )
		return -1;
	if ( id <= 0 || id >= g_kingwar_town_maxcount )
		return -1;
	if ( g_army[army_index].state == ARMY_STATE_KINGWAR_WAITSOS || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	if ( g_army[army_index].state != ARMY_STATE_KINGWAR_FIGHT )
		return -1;

	if ( army_index == g_kingwar_town[id].attack_queue[0] || army_index == g_kingwar_town[id].defense_queue[0] )
	{ // ���佫�Ѿ������޷����е���
		actor_notify_alert( actor_index, 1406 );
		return -1;
	}

	// ���ǹ��������Ƿ�����
	char attack = kingwar_town_attack_or_defense( id, army_index );
	char target;
	if ( attack == KINGWAR_TOWN_ATTACK )
		target = KINGWAR_TOWN_DEFENSE;
	else
		target = KINGWAR_TOWN_ATTACK;

	if ( kingwar_town_queueget( id, target ) < 0 )
	{ // �Է��޿ɵ�������
		actor_notify_alert( actor_index, 1407 );
		return -1;
	}

	for ( int tmpi = 0; tmpi < KINGWAR_TOWN_QUEUE_MAX; tmpi++ )
	{
		int target_army_index = kingwar_town_queueget( id, attack );
		if ( target_army_index < 0 || target_army_index >= g_army_maxcount )
		{ // û���˶�����
			break;
		}

		// ˫�������ˣ�ս��
		if ( fight_start( army_index, MAPUNIT_TYPE_KINGWAR_TOWN, target_army_index ) < 0 )
		{
			break;
		}

		// ս������
		fight_lost_calc();

		// ����ʧ����
		g_kingwar_lost_totalhp += g_fight.attack_total_damage;
		g_kingwar_lost_totalhp += g_fight.defense_total_damage;

		if ( g_fight.result == FIGHT_WIN )
		{ // ����һ��ʤ��
			kingwar_town_totalcalc( id, attack );
			// ɾ��һ�����ط�����
			kingwar_town_queuedel( id, target, target_army_index );
			g_army[target_army_index].state = ARMY_STATE_KINGWAR_WAITSOS;
			g_army[target_army_index].statetime = 0;
			g_army[target_army_index].stateduration = global.kingwar_dead_cd;
			city_battlequeue_sendupdate( target_army_index );
		}
		else
		{ // ʧ��
			kingwar_town_totalcalc( id, target );
			// ɾ��һ������������
			kingwar_town_queuedel( id, attack, target_army_index );
			g_army[target_army_index].state = ARMY_STATE_KINGWAR_WAITSOS;
			g_army[target_army_index].statetime = 0;
			g_army[target_army_index].stateduration = global.kingwar_dead_cd;
			city_battlequeue_sendupdate( target_army_index );
			break;
		}
	}

	city_battlequeue_sendupdate( army_index );

	// ���Ŀ���Ƿ�����
	if ( kingwar_town_queueget( id, target ) < 0 )
		return -1;

	//// ��ȡ������
	//defense_army_index = kingwar_town_queueget( id, KINGWAR_TOWN_DEFENSE );
	//if ( defense_army_index < 0 )
	//{
	//	// ������û���ˣ���ɹ�������
	//	kingwar_town_change_nation( id, army_getnation( attack_army_index ), attack_army_index );
	//	return;
	//}

	
	g_kingwar_town_update = 1;
	return 0;
}

// ��Ԯ
int kingwar_army_rebirth( int actor_index, int army_index )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( g_army[army_index].state == 0 || g_army[army_index].state == ARMY_STATE_KINGWAR_DEAD )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	if ( army_myself( actor_index, army_index ) < 0 )
	{ // ���佫�Ѿ�����
		actor_notify_alert( actor_index, 1418 );
		return -1;
	}
	if ( g_army[army_index].state != ARMY_STATE_KINGWAR_WAITSOS )
		return -1;

	int costtoken = 0;
	if ( g_army[army_index].appdata == 0 )
		costtoken = 10;
	else if ( g_army[army_index].appdata == 1 )
		costtoken = 100;
	else if ( g_army[army_index].appdata == 2 )
		costtoken = 200;
	else
		costtoken = 400;

	if ( g_actors[actor_index].token < costtoken )
		return -1;
	
	// ����ʿ��
	int soldiers = hero_addsoldiers( actor_index, g_army[army_index].herokind[0], PATH_KINGWAR_REBIRTH );
	if ( soldiers <= 0 )
	{ // ��Ӫ��治�㣬��Ԯʧ��
		actor_notify_alert( actor_index, 1408 );
		return -1;
	}

	g_army[army_index].statetime = 0;
	g_army[army_index].stateduration = 0;
	g_army[army_index].appdata += 1;
	g_army[army_index].totals = soldiers;

	if ( g_army[army_index].to_id >= 1 && g_army[army_index].to_id <= 3 )
	{ // �ڼ�����Ԯ
		g_army[army_index].state = ARMY_STATE_KINGWAR_READY;
	}
	else
	{
		g_army[army_index].state = ARMY_STATE_KINGWAR_FIGHT;
		if ( kingwar_town_queueadd( g_army[army_index].to_id, kingwar_town_attack_or_defense( g_army[army_index].to_id, army_index ), army_index ) < 0 )
			return -1;
	}

	actor_change_token( actor_index, -costtoken, PATH_KINGWAR_REBIRTH, 0 );
	city_battlequeue_sendupdate( army_index );
	g_kingwar_town_update = 1;
	return 0;
}
