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
#include "map_town.h"
#include "mail.h"
#include "city.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern Actor *g_actors;
extern int g_maxactornum;

extern City * g_city;
extern int g_city_maxcount;
extern int g_city_maxindex;

extern MonsterInfo *g_monster;
extern int g_monster_maxnum;

extern MapTownInfo *g_towninfo;
extern int g_towninfo_maxnum;

MapTown *g_map_town = NULL;
int g_map_town_maxcount = 0;
extern int g_map_town_maxindex;

// 读档完毕的回调
int map_town_loadcb( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;

	// 重置守军
	map_town_monster_reset( townid );

	// 城主
	if ( g_map_town[townid].own_actorid > 0 )
	{
		g_map_town[townid].own_city_index = city_getindex_withactorid( g_map_town[townid].own_actorid );
	}
	else
	{ // 竞选者
		for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
		{
			if ( g_map_town[townid].ask_actorid[tmpi] <= 0 )
				continue;
			g_map_town[townid].ask_city_index[tmpi] = city_getindex_withactorid( g_map_town[townid].ask_actorid[tmpi] );
		}
	}
	return 0;
}

int map_town_load()
{
	g_map_town_maxcount = g_towninfo_maxnum;
	g_map_town = (MapTown*)malloc( sizeof( MapTown ) * g_map_town_maxcount );
	memset( g_map_town, 0, sizeof( MapTown ) * g_map_town_maxcount );
	printf_msg( "MapTown  maxcount=%d  memory=%0.2fMB(memory=%0.2fKB)\n", g_map_town_maxcount, (sizeof( MapTown )*g_map_town_maxcount) / 1024.0 / 1024.0, sizeof( MapTown ) / 1024.0 );
	for ( int townid = 1; townid < g_map_town_maxcount; townid++ )
	{
		if ( g_towninfo[townid].id <= 0 )
			continue;
		g_map_town[townid].townid = townid;
		g_map_town[townid].own_city_index = -1;
		for ( int tmpi = 0; tmpi < 3; tmpi++ )
		{
			g_map_town[townid].underfire_groupindex[tmpi] = -1;
		}

		for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
		{
			g_map_town[townid].ask_city_index[tmpi] = -1;
		}

		// 上一级townid列表
		char **pptable = NULL;
		int groupcount = 0;
		pptable = u_strcut_ex( g_towninfo[townid].preid, ',', &groupcount );
		for ( int tmpi = 0; tmpi < groupcount; tmpi++ )
		{
			if ( groupcount >= 8 )
				break;
			g_map_town[townid].pre_townid[tmpi] = atoi( pptable[tmpi] );
		}
		u_free_vec( pptable );

		// 添加到地图显示单元
		g_map_town[townid].unit_index = mapunit_add( MAPUNIT_TYPE_TOWN, townid );

		// 占地块信息添加到世界地图
		map_addobject( MAPUNIT_TYPE_TOWN, townid, g_towninfo[townid].posx, g_towninfo[townid].posy );

		// 重置守军
		map_town_monster_reset( townid );
	}
	map_town_load_auto( map_town_getptr, map_town_loadcb, "map_town" );
	return 0;
}

MapTown *map_town_getptr( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return NULL;
	return &g_map_town[townid];
}

MapTownInfo *map_town_getconfig( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return NULL;
	return &g_towninfo[townid];
}

int map_town_save( FILE *fp )
{
	map_town_batch_save_auto( g_map_town, g_map_town_maxcount, "map_town", fp );
	return 0;
}

// 显示单元属性
void map_town_makeunit( int index, SLK_NetS_AddMapUnit *pAttr )
{
	if ( index <= 0 || index >= g_map_town_maxcount )
		return;
	if ( g_map_town[index].name[0] != 0 )
	{
		strncpy( pAttr->m_name, g_map_town[index].name, NAME_SIZE );
		pAttr->m_namelen = strlen( pAttr->m_name );
	}
	pAttr->m_posx = g_towninfo[index].posx;
	pAttr->m_posy = g_towninfo[index].posy;
	pAttr->m_char_value[0] = g_map_town[index].nation;
	pAttr->m_char_value_count = 1;

	pAttr->m_short_value[0] = (short)g_towninfo[index].id;
	pAttr->m_short_value[1] = g_map_town[index].produce_num;
	pAttr->m_short_value_count = 2;

	pAttr->m_int_value[0] = g_map_town[index].protect_sec;
	pAttr->m_int_value[1] = g_map_town[index].produce_sec;
	pAttr->m_int_value_count = 2;
}

// 位置
void map_town_getpos( int index, short *posx, short *posy )
{
	MapTownInfo *config = map_town_getconfig( index );
	if ( config )
	{
		*posx = config->posx;
		*posy = config->posy;
	}
}

// 重置守军
void map_town_monster_reset( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return;
	char **pptable = NULL;
	int groupcount = 0;

	// 先重置
	for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
	{
		g_map_town[townid].monster[tmpi] = 0;
	}

	// 将字符串形式的组合数据拆解成整数数组
	if ( g_map_town[townid].nation == 0 )
	{
		pptable = u_strcut_ex( g_towninfo[townid].monster, ',', &groupcount );
	}
	else
	{
		pptable = u_strcut_ex( g_towninfo[townid].monster_guard, ',', &groupcount );
	}
	for ( int tmpi = 0; tmpi < groupcount; tmpi++ )
	{
		if ( groupcount >= MAP_TOWN_MONSTER_MAX )
			break;
		g_map_town[townid].monster[tmpi] = atoi( pptable[tmpi] );

		int monsterid = g_map_town[townid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;

		// 群雄守卫，血量不存
		if ( g_map_town[townid].nation == 0 )
		{
			g_map_town[townid].soldier[tmpi] = g_monster[monsterid].troops;
		}
	}

	// 容错
	for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
	{
		int monsterid = g_map_town[townid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
		{
			g_map_town[townid].soldier[tmpi] = 0;
			continue;
		}

		if ( g_map_town[townid].soldier[tmpi] > g_monster[monsterid].troops )
		{
			g_map_town[townid].soldier[tmpi] = g_monster[monsterid].troops;
		}
	}

	// 释放内存空间
	u_free_vec( pptable );
}

// 单个城镇每秒逻辑
void map_town_logic( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return;

	if ( g_map_town[townid].protect_sec > 0 )
	{ // 保护时间内
		g_map_town[townid].protect_sec -= 1;
		if ( g_map_town[townid].protect_sec <= 0 )
		{ // 保护时间到，执行选城主逻辑
			map_town_alloc_owner( townid );
			mapunit_update( MAPUNIT_TYPE_TOWN, townid, g_map_town[townid].unit_index );
		}
	}
	else if ( g_map_town[townid].own_actorid > 0 )
	{ // 有城主，减少任期
		g_map_town[townid].own_sec -= 1;
		if ( g_map_town[townid].own_sec <= 0 )
		{ // 任期到
			// 发送邮件
			char v1[64] = { 0 };
			char v2[64] = { 0 };
			sprintf( v1, "%s%d", TAG_TOWNID, townid );
			sprintf( v2, "%d,%d", g_towninfo[townid].posx, g_towninfo[townid].posy );
			mail_system( -1, g_map_town[townid].own_actorid, 5024, 5522, v1, v2, NULL, "" );

			// 重置
			g_map_town[townid].own_actorid = 0;
			g_map_town[townid].own_city_index = -1;
			mapunit_update( MAPUNIT_TYPE_TOWN, townid, g_map_town[townid].unit_index );
		}
	}

	// 征收次数
	if ( g_map_town[townid].nation > 0 && g_map_town[townid].produce_num < g_towninfo[townid].produce_maxnum )
	{
		if ( g_map_town[townid].produce_sec > 0 )
		{
			g_map_town[townid].produce_sec -= 1;
			if ( g_map_town[townid].produce_sec <= 0 )
			{
				g_map_town[townid].produce_num += 1;
				g_map_town[townid].produce_sec = g_towninfo[townid].produce_maxsec;
				mapunit_update( MAPUNIT_TYPE_TOWN, townid, g_map_town[townid].unit_index );
			}
		}
	}
	
}

// 所有城镇每秒逻辑
void map_town_alllogic()
{
	for ( int townid = 1; townid < g_map_town_maxcount; townid++ )
	{
		if ( g_towninfo[townid].id <= 0 )
			continue;
		map_town_logic( townid );
	}
}

// 检查是否是参战人员
int map_town_check_join( int townid, int actorid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;

	// 检查是否是参战人员
	int tmpi = 0;
	for ( tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
	{
		if ( g_map_town[townid].join_actorid[tmpi] == actorid )
		{
			break;
		}
	}
	if ( tmpi >= MAP_TOWN_JOIN_MAX )
	{ // 不是参战人员
		return -1;
	}

	return 0;
}

// 检查是否是已经申请人员
int map_town_check_ask( int townid, int actorid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;

	// 检查是否是参战人员
	int tmpi = 0;
	for ( tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
	{
		if ( g_map_town[townid].ask_actorid[tmpi] == actorid )
		{
			break;
		}
	}
	if ( tmpi >= MAP_TOWN_JOIN_MAX )
	{ // 没有申请
		return -1;
	}

	return 0;
}

// 申请城主
int map_town_ask_owner( int actor_index, int townid )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;

	int type = 0;
	int free_index = -1;
	// 如果已经过了保护期
	if ( g_map_town[townid].protect_sec <= 0 )
	{
		if ( g_map_town[townid].own_actorid > 0 )
		{ // 已经有城主了
			return -1;
		}
		// 不能跨区域申请城主
		if ( map_zone_checksame( g_towninfo[townid].posx, g_towninfo[townid].posy, pCity->posx, pCity->posy ) == 0 )
		{
			actor_notify_alert( actor_index, 1271 );
			return -1;
		}
		type = 0;
	}
	else
	{
		type = 1;
		// 检查是否是参战人员
		if ( map_town_check_join( townid, g_actors[actor_index].actorid ) < 0 )
		{
			actor_notify_alert( actor_index, 1311 );
			return -1;
		}

		// 检查是否已经申请过
		if ( map_town_check_ask( townid, g_actors[actor_index].actorid ) == 0 )
			return -1;

		// 找到一个位置
		for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
		{
			if ( g_map_town[townid].ask_actorid[tmpi] <= 0 )
			{
				free_index = tmpi;
				break;
			}

			City *pAsk = city_indexptr( g_map_town[townid].ask_city_index[tmpi] );
			if ( pAsk )
			{
				if ( pCity->place > pAsk->place )
				{
					free_index = tmpi;
					break;
				}
				else if ( pCity->place == pAsk->place && pCity->battlepower > pAsk->battlepower )
				{
					free_index = tmpi;
					break;
				}
			}
		}
	}


	// 检查申请资源
	if ( g_towninfo[townid].ask_silver > 0 )
	{
		if ( pCity->silver < g_towninfo[townid].ask_silver )
		{
			return -1;
		}
	}
	if ( g_towninfo[townid].ask_wood > 0 )
	{
		if ( pCity->wood < g_towninfo[townid].ask_wood )
		{
			return -1;
		}
	}
	if ( g_towninfo[townid].ask_food > 0 )
	{
		if ( pCity->food < g_towninfo[townid].ask_food )
		{
			return -1;
		}
	}
	if ( g_towninfo[townid].ask_iron > 0 )
	{
		if ( pCity->iron < g_towninfo[townid].ask_iron )
		{
			return -1;
		}
	}

	// 扣除申请资源
	if ( g_towninfo[townid].ask_silver > 0 )
	{
		city_changesilver( pCity->index, -g_towninfo[townid].ask_silver, PATH_TOWNASK );
	}
	if ( g_towninfo[townid].ask_wood > 0 )
	{
		city_changewood( pCity->index, -g_towninfo[townid].ask_wood, PATH_TOWNASK );
	}
	if ( g_towninfo[townid].ask_food > 0 )
	{
		city_changefood( pCity->index, -g_towninfo[townid].ask_food, PATH_TOWNASK );
	}
	if ( g_towninfo[townid].ask_iron > 0 )
	{
		city_changeiron( pCity->index, -g_towninfo[townid].ask_iron, PATH_TOWNASK );
	}


	if ( type == 0 )
	{ // 直接成为城主
		g_map_town[townid].own_actorid = pCity->actorid;
		g_map_town[townid].own_city_index = pCity->index;
		g_map_town[townid].own_sec = g_towninfo[townid].own_maxsec;

		// 您成为了{ 0 }<url = { 1 }>[{1}]< / url>的城主。任期{ 2 }天
		char v1[64] = { 0 };
		char v2[64] = { 0 };
		char v3[64] = { 0 };
		sprintf( v1, "%s%d", TAG_TOWNID, townid );
		sprintf( v2, "%d,%d", g_towninfo[townid].posx, g_towninfo[townid].posy );
		sprintf( v3, "%s%d", TAG_TIMEDAY, g_towninfo[townid].own_maxsec );
		mail_system( pCity->actor_index, pCity->actorid, 5025, 5524, v1, v2, v3, "" );
		actor_notify_alert_v( actor_index, 1307, v1, NULL );
	}
	else
	{
		if ( free_index < 0 || free_index >= MAP_TOWN_JOIN_MAX )
		{ // 没有申请位置了
			return -1;
		}
		// 位置后移，我插入
		if ( free_index < MAP_TOWN_JOIN_MAX - 1 )
		{
			memmove( &g_map_town[townid].ask_actorid[free_index+1], &g_map_town[townid].ask_actorid[free_index], sizeof( int )*(MAP_TOWN_JOIN_MAX - 1 - free_index) );
			memmove( &g_map_town[townid].ask_city_index[free_index+1], &g_map_town[townid].ask_city_index[free_index], sizeof( int )*(MAP_TOWN_JOIN_MAX - 1 - free_index) );
		}
		g_map_town[townid].ask_actorid[free_index] = pCity->actorid;
		g_map_town[townid].ask_city_index[free_index] = pCity->index;
		map_town_ask_owner_sendlist( actor_index, townid );
	}

	return 0;
}

// 分配城主
int map_town_alloc_owner( int townid )
{
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;

	City *pCity = NULL;
	int place = 0;
	int battlepower = 0;
	for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
	{
		if ( g_map_town[townid].ask_actorid[tmpi] <= 0 )
			continue;
		City *pAsk = city_indexptr( g_map_town[townid].ask_city_index[tmpi] );
		if ( !pAsk )
			continue;

		if ( (!pCity) || (pAsk->place > place) || (pAsk->place == place && pAsk->battlepower > battlepower) )
		{
			pCity = pAsk;
			place = pAsk->place;
			battlepower = pAsk->battlepower;
		}
	}

	if ( !pCity )
		return -1;

	// 成为城主
	g_map_town[townid].own_actorid = pCity->actorid;
	g_map_town[townid].own_city_index = pCity->index;
	g_map_town[townid].own_sec = g_towninfo[townid].own_maxsec;

	// 您成为了{ 0 }<url = { 1 }>[{1}]< / url>的城主。任期{ 2 }天
	char v1[64] = { 0 };
	char v2[64] = { 0 };
	char v3[64] = { 0 };
	sprintf( v1, "%s%d", TAG_TOWNID, townid );
	sprintf( v2, "%d,%d", g_towninfo[townid].posx, g_towninfo[townid].posy );
	sprintf( v3, "%s%d", TAG_TIMEDAY, g_towninfo[townid].own_maxsec );
	mail_system( pCity->index, pCity->actorid, 5025, 5524, v1, v2, v3, "" );

	// 给其它竞选者发送失败邮件, 并返还资源
	// 很遗憾，{0}在众多候选人中爵位最高，成为了{1}<url={2}>[{2}]</url>的城主
	sprintf( v1, "%s", pCity->name );
	sprintf( v2, "%s%d", TAG_TOWNID, townid );
	sprintf( v3, "%d,%d", g_towninfo[townid].posx, g_towninfo[townid].posy );
	char attach[256] = { 0 };
	char tmpStr[64] = { 0 };
	if ( g_towninfo[townid].ask_silver > 0 )
	{
		sprintf( tmpStr, "%d,%d@", AWARDKIND_SILVER, g_towninfo[townid].ask_silver );
		strcat( attach, tmpStr );
	}
	if ( g_towninfo[townid].ask_wood > 0 )
	{
		sprintf( tmpStr, "%d,%d@", AWARDKIND_WOOD, g_towninfo[townid].ask_wood );
		strcat( attach, tmpStr );
	}
	if ( g_towninfo[townid].ask_food > 0 )
	{
		sprintf( tmpStr, "%d,%d@", AWARDKIND_FOOD, g_towninfo[townid].ask_food );
		strcat( attach, tmpStr );
	}
	if ( g_towninfo[townid].ask_iron > 0 )
	{
		sprintf( tmpStr, "%d,%d@", AWARDKIND_IRON, g_towninfo[townid].ask_iron );
		strcat( attach, tmpStr );
	}
	
	for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
	{
		if ( g_map_town[townid].ask_actorid[tmpi] <= 0 )
			continue;
		if ( g_map_town[townid].ask_actorid[tmpi] == pCity->actorid )
			continue;
		City *pAsk = city_indexptr( g_map_town[townid].ask_city_index[tmpi] );
		if ( !pAsk )
			continue;
		mail_system( pAsk->index, pAsk->actorid, 5026, 5525, v1, v2, v3, attach );
		g_map_town[townid].ask_actorid[tmpi] = 0;
		g_map_town[townid].ask_city_index[tmpi] = -1;
	}
	return 0;
}

// 放弃城主
int map_town_owner_leave( int actor_index, int townid )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( g_map_town[townid].own_actorid != pCity->actorid )
		return -1;

	g_map_town[townid].own_actorid = 0;
	g_map_town[townid].own_city_index = -1;
	g_map_town[townid].own_sec = 0;
	return 0;
}

// 补兵
int map_town_soldiers_repair( int actor_index, int townid )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( g_map_town[townid].own_actorid != pCity->actorid )
		return -1;

	int maxhp = 0;
	int hp = 0;
	for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
	{
		int monsterid = g_map_town[townid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;
		maxhp += g_monster[monsterid].troops;
		hp += g_map_town[townid].soldier[tmpi];
	}

	int repairhp = min( maxhp - hp, maxhp / 20 );
	int cost_silver = (int)ceil( repairhp / (float)maxhp * g_towninfo[townid].ask_silver );
	int cost_wood = (int)ceil( repairhp / (float)maxhp * g_towninfo[townid].ask_wood );

	if ( pCity->silver < cost_silver )
		return -1;
	if ( pCity->wood < cost_wood )
		return -1;
	city_changesilver( pCity->index, -cost_silver, PATH_TOWNREPAIR );
	city_changesilver( pCity->index, -cost_wood, PATH_TOWNREPAIR );

	// 一个一个补
	for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
	{
		if ( repairhp <= 0 )
			break;

		int monsterid = g_map_town[townid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;

		int add = g_monster[monsterid].troops - g_map_town[townid].soldier[tmpi];
		if ( add <= 0 )
			continue;

		if ( add >= repairhp )
		{
			add = repairhp;
			repairhp = 0;
		}
		else
		{
			repairhp -= add;
		}

		g_map_town[townid].soldier[tmpi] += add;
		if ( g_map_town[townid].soldier[tmpi] > g_monster[monsterid].troops )
			g_map_town[townid].soldier[tmpi] = g_monster[monsterid].troops;
	}

	map_town_sendinfo( actor_index, townid );
	return 0;
}

// 城镇征收
int map_town_levy( int actor_index, int townid )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( g_map_town[townid].nation != pCity->nation )
		return -1;
	if ( g_map_town[townid].produce_num <= 0 )
		return -1;

	// 消耗威望
	int dd = 0;
	int prestige = g_towninfo[townid].levy_prestige;
	if ( item_getitemnum( actor_index, g_towninfo[townid].levy_item ) > 0 )
	{
		prestige *= 2;
		dd = 1;
	}

	if ( pCity->prestige < prestige )
	{
		return -1;
	}

	// 扣威望
	city_changeprestige( pCity->index, -prestige, PATH_TOWNLEVY );
	// 扣强征令
	if ( dd == 1 )
		item_lost( actor_index, g_towninfo[townid].levy_item, 1, PATH_TOWNLEVY );

	// 总征收次数-1
	g_map_town[townid].produce_num -= 1;

	// 检查上一级营地是否被攻破
	char occupy = 0;
	for ( int tmpi = 0; tmpi < 8; tmpi++ )
	{
		int pre_townid = g_map_town[townid].pre_townid[tmpi];
		if ( pre_townid <= 0 || pre_townid >= g_map_town_maxcount )
			continue;
		if ( g_map_town[pre_townid].nation > 0 )
		{
			occupy = 1;
			break;
		}
	}

	if ( occupy == 0 )
	{
		awardgroup_withindex( actor_index, g_towninfo[townid].base_award, 0, PATH_TOWNLEVY, NULL );
	}
	else
	{
		awardgroup_withindex( actor_index, g_towninfo[townid].other_award, 0, PATH_TOWNLEVY, NULL );
	}
	return 0;
}

// 获取野怪奖励
int map_town_sendaward( int actor_index, int townid )
{
	ACTOR_CHECK_INDEX( actor_index );
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	// 检查上一级营地是否被攻破
	char occupy = 0;
	for ( int tmpi = 0; tmpi < 8; tmpi++ )
	{
		int pre_townid = g_map_town[townid].pre_townid[tmpi];
		if ( pre_townid <= 0 || pre_townid >= g_map_town_maxcount )
			continue;
		if ( g_map_town[pre_townid].nation > 0 )
		{
			occupy = 1;
			break;
		}
	}

	if ( occupy == 0 )
	{
		awardgroup_sendinfo( actor_index, g_towninfo[townid].base_award, 2, townid, 16 );
	}
	else
	{
		awardgroup_sendinfo( actor_index, g_towninfo[townid].other_award, 2, townid, 16 );
	}
	return 0;
}

// 获取城镇信息
int map_town_sendinfo( int actor_index, int townid )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	SLK_NetS_MapTownInfo pValue = { 0 };
	pValue.m_protect_sec = g_map_town[townid].protect_sec;
	pValue.m_produce_sec = g_map_town[townid].produce_sec;
	pValue.m_own_actorid = g_map_town[townid].own_actorid;
	if ( g_map_town[townid].own_actorid > 0 )
	{ // 已经有城主
		int city_index = g_map_town[townid].own_city_index;
		if ( city_index < 0 || city_index >= g_city_maxcount )
		{
			city_index = city_getindex_withactorid( g_map_town[townid].own_actorid );
			g_map_town[townid].own_city_index = city_index;
		}
		if ( city_index >= 0 && city_index < g_city_maxcount )
		{
			strncpy( pValue.m_own_name, g_city[city_index].name, NAME_SIZE );
			pValue.m_own_namelen = strlen( pValue.m_own_name );
			pValue.m_own_sec = g_map_town[townid].own_sec;
		}
	}
	else
	{ // 没城主
		if ( g_map_town[townid].protect_sec > 0 )
		{ // 检查我是否在申请列表里
			for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
			{
				if ( g_map_town[townid].ask_actorid[tmpi] <= 0 )
					continue;
				if ( g_map_town[townid].ask_actorid[tmpi] == pCity->actorid )
				{
					pValue.m_myask = 1;
					break;
				}
			}
		}
	}

	for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
	{
		int monsterid = g_map_town[townid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;
		pValue.m_maxhp += g_monster[monsterid].troops;
		pValue.m_hp += g_map_town[townid].soldier[tmpi];
	}

	netsend_maptowninfo_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

// 申请列表
int map_town_ask_owner_sendlist( int actor_index, int townid )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( townid <= 0 || townid >= g_map_town_maxcount )
		return -1;
	SLK_NetS_TownOwnerAskList pValue = { 0 };
	pValue.m_sec = g_map_town[townid].protect_sec;

	for ( int tmpi = 0; tmpi < MAP_TOWN_JOIN_MAX; tmpi++ )
	{
		int city_index = g_map_town[townid].ask_city_index[tmpi];
		if ( city_index < 0 || city_index >= g_city_maxcount )
			continue;
		strncpy( pValue.m_list[pValue.m_count].m_name, g_city[city_index].name, NAME_SIZE );
		pValue.m_list[pValue.m_count].m_name_len = strlen( pValue.m_list[pValue.m_count].m_name );
		pValue.m_list[pValue.m_count].m_place = g_city[city_index].place;
		pValue.m_count += 1;
		if ( pValue.m_count >= 5 )
		{
			break;
		}
	}

	netsend_townowneraskList_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}
