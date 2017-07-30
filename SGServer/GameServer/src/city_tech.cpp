#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <math.h>
#include "db.h"
#include "global.h"
#include "actor.h"
#include "city.h"
#include "city_tech.h"
#include "building.h"
#include "mapunit.h"
#include "map.h"
#include "equip.h"
#include "quest.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern MapUnit *g_mapunit;
extern int g_mapunit_maxcount;
extern Map g_map;

extern Actor *g_actors;
extern int g_maxactornum;

extern City *g_city;
extern int g_city_maxcount;

extern BuildingUpgrade *g_building_upgrade;
extern int g_building_upgrade_maxnum;

extern TechInfo *g_techinfo;
extern int g_techinfo_maxnum;

// �ǳؿƼ��о�
int city_tech_upgrade( int actor_index, short kind )
{
	ACTOR_CHECK_INDEX( actor_index );
	if ( kind <= 0 || kind >= g_techinfo_maxnum )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Building *pBuilding = building_getptr_kind( g_actors[actor_index].city_index, BUILDING_Tech );
	if ( !pBuilding )
		return -1;
	if ( pBuilding->sec > 0 )
		return -1;
	if ( pBuilding->overvalue > 0 )
		return -1;
	int level = pCity->techlevel[kind];
	int uplevel = pCity->techlevel[kind] + 1;
	int progress = pCity->techprogress[kind];
	if ( uplevel <= 0 || uplevel >= g_techinfo[kind].maxnum )
		return -1;

	TechInfoConfig *config = &g_techinfo[kind].config[uplevel];
	if ( !config )
		return -1;

	// ̫ѧԺ�ȼ����
	if ( pBuilding->level < config->buildinglevel )
		return -1;

	// ǰ�ü��
	int prekind = config->prekind;
	int prelevel = config->prelevel;
	if ( prekind > 0 && prekind < g_techinfo_maxnum )
	{
		if ( pCity->techlevel[prekind] < prelevel )
		{
			return -1;
		}
	}

	// ��Դ���
	if ( config->silver > 0 )
	{
		if ( pCity->silver < config->silver )
			return -1;
	}
	if ( config->wood > 0 )
	{
		if ( pCity->wood < config->wood )
			return -1;
	}
	if ( config->food > 0 )
	{
		if ( pCity->food < config->food )
			return -1;
	}
	if ( config->iron > 0 )
	{
		if ( pCity->iron < config->iron )
			return -1;
	}

	if ( config->silver > 0 )
		city_changesilver( pCity->index, -config->silver, PATH_TECH_UPGRADE );
	if ( config->wood > 0 )
		city_changewood( pCity->index, -config->wood, PATH_TECH_UPGRADE );
	if ( config->food > 0 )
		city_changefood( pCity->index, -config->food, PATH_TECH_UPGRADE );
	if ( config->iron > 0 )
		city_changeiron( pCity->index, -config->iron, PATH_TECH_UPGRADE );

	pBuilding->sec = config->sec;
	pBuilding->needsec = config->sec;
	pBuilding->value = kind;
	pBuilding->overvalue = 0;
	building_sendinfo( actor_index, BUILDING_Tech );
	wlog( 0, LOGOP_TECH, PATH_TECH_UPGRADE, kind, pCity->techlevel[kind], pCity->techprogress[kind], pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

// ����
int city_tech_quick( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Building *pBuilding = building_getptr_kind( g_actors[actor_index].city_index, BUILDING_Tech );
	if ( !pBuilding )
		return -1;
	int kind = pBuilding->value;
	if ( kind <= 0 || kind >= g_techinfo_maxnum )
		return -1;
	int token = (int)ceil(pBuilding->sec / global.techquick_token);
	if ( actor_change_token( actor_index, -token, PATH_TECH_QUICK, 0 ) < 0 )
		return -1;

	wlog( 0, LOGOP_TECH, PATH_TECH_QUICK, kind, pCity->techlevel[kind], pCity->techprogress[kind], pCity->actorid, city_mainlevel( pCity->index ) );
	city_tech_finish( pCity, pBuilding );
	return 0;
}

// ��Ѽ���
int city_tech_freequick( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Building *pBuilding = building_getptr_kind( g_actors[actor_index].city_index, BUILDING_Tech );
	if ( !pBuilding )
		return -1;
	int kind = pBuilding->value;
	if ( kind <= 0 || kind >= g_techinfo_maxnum )
		return -1;

	wlog( 0, LOGOP_TECH, PATH_TECH_FREEQUICK, kind, pCity->techlevel[kind], pCity->techprogress[kind], pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

// ���
int city_tech_finish( City *pCity, Building *pBuilding )
{
	if ( !pCity || !pBuilding )
		return -1;
	int kind = pBuilding->value;
	if ( kind <= 0 || kind >= g_techinfo_maxnum )
	{
		pBuilding->sec = 0;
		pBuilding->needsec = 0;
		pBuilding->value = 0;
		pBuilding->overvalue = 0;
		wlog( 0, LOGOP_TECH, PATH_TECH_FINISH, kind, -1, -1, pCity->actorid, city_mainlevel( pCity->index ) );
		return -1;
	}
	pBuilding->sec = 0;
	pBuilding->needsec = 0;
	pBuilding->overvalue = kind;
	pBuilding->value = 0;
	building_sendinfo( pCity->actor_index, pBuilding->kind );
	wlog( 0, LOGOP_TECH, PATH_TECH_FINISH, pBuilding->overvalue, pCity->techlevel[kind], pCity->techprogress[kind], pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

// ��ȡ
int city_tech_get( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Building *pBuilding = building_getptr_kind( g_actors[actor_index].city_index, BUILDING_Tech );
	if ( !pBuilding )
		return -1;
	int kind = pBuilding->overvalue;
	pBuilding->overvalue = 0;
	if ( kind <= 0 || kind >= g_techinfo_maxnum )
		return -1;

	int level = pCity->techlevel[kind];
	int uplevel = pCity->techlevel[kind] + 1;
	if ( uplevel <= 0 || uplevel >= g_techinfo[kind].maxnum )
		return -1;

	TechInfoConfig *config = &g_techinfo[kind].config[uplevel];
	if ( !config )
		return -1;
	
	pCity->techprogress[kind] += 1;
	if ( pCity->techprogress[kind] >= config->progress )
	{
		pCity->techlevel[kind] += 1;
		pCity->techprogress[kind] = 0;
	}
	
	if ( pCity->actor_index >= 0 )
	{
		SLK_NetS_TechChange pValue = { 0 };
		pValue.m_kind = kind;
		pValue.m_level = pCity->techlevel[kind];
		pValue.m_progress = pCity->techprogress[kind];
		netsend_techchange_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );
		building_sendinfo( pCity->actor_index, pBuilding->kind );
	}

	wlog( 0, LOGOP_TECH, PATH_TECH_GET, kind, pCity->techlevel[kind], pCity->techprogress[kind], g_actors[actor_index].actorid, city_mainlevel( pCity->index ) );
	return 0;
}