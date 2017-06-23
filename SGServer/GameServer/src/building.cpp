#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include "db.h"
#include "global.h"
#include "actor.h"
#include "city.h"
#include "building.h"
#include "mapunit.h"
#include "map.h"
#include "server_netsend_auto.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern MapUnit *g_mapunit;
extern int g_mapunit_maxcount;
extern Map g_map;

extern Actor *g_actors;
extern int g_maxactornum;

extern int g_city_maxindex;
extern City *g_city;
extern int g_city_maxcount;

extern BuildingUpgrade *g_building_upgrade;
extern int g_building_upgrade_maxnum;

// ��ȡ����ָ��
Building* building_getptr( int city_index, int offset )
{
	if ( city_index < 0 || city_index >= g_city_maxcount )
		return NULL;
	if ( offset < 0 || offset >= BUILDING_MAXNUM )
		return NULL;
	return &g_city[city_index].building[offset];
}

BuildingBarracks* buildingbarracks_getptr( int city_index, int offset )
{
	if ( city_index < 0 || city_index >= g_city_maxcount )
		return NULL;
	if ( offset < 0 || offset >= BUILDING_BARRACKS_MAXNUM )
		return NULL;
	return &g_city[city_index].building_barracks[offset];
}

BuildingRes* buildingres_getptr( int city_index, int offset )
{
	if ( city_index < 0 || city_index >= g_city_maxcount )
		return NULL;
	if ( offset < 0 || offset >= BUILDING_RES_MAXNUM )
		return NULL;
	return &g_city[city_index].building_res[offset];
}

// ��ȡ������������Ϣ
BuildingUpgradeConfig* building_getconfig( int kind, int level )
{
	if ( kind < 0 || kind >= g_building_upgrade_maxnum )
		return NULL;
	if ( level < 0 || level >= g_building_upgrade[kind].maxnum )
		return NULL;
	return &g_building_upgrade[kind].config[level];
}

int building_getindex( int city_index, int kind )
 {
	CITY_CHECK_INDEX( city_index );
	int index = -1;
	if ( kind < BUILDING_Infantry )
	{ // ��ͨ����
		for ( int tmpi = 0; tmpi < BUILDING_MAXNUM; tmpi++ )
		{
			if ( g_city[city_index].building[tmpi].kind == kind )
			{
				index = tmpi;
				break;
			}
		}
	}
	else if ( kind < BUILDING_Silver )
	{ // ��Ӫ����
		for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
		{
			if ( g_city[city_index].building_barracks[tmpi].kind == kind )
			{
				index = tmpi;
				break;
			}
		}
	}
	return index;
}

// ��ȡ�����ȼ�
int building_getlevel( int city_index, int kind )
{
	CITY_CHECK_INDEX( city_index );
	if ( kind < BUILDING_Infantry )
	{ // ��ͨ����
		for ( int tmpi = 0; tmpi < BUILDING_MAXNUM; tmpi++ )
		{
			if ( g_city[city_index].building[tmpi].kind == kind )
			{
				return g_city[city_index].building[tmpi].level;
			}
		}
	}
	else if ( kind < BUILDING_Silver )
	{ // ��Ӫ����
		for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
		{
			if ( g_city[city_index].building_barracks[tmpi].kind == kind )
			{
				return g_city[city_index].building_barracks[tmpi].level;
			}
		}
	}
	return 0;
}

// ��������
int building_create( int city_index, int kind, int offset )
{
	CITY_CHECK_INDEX( city_index );
	if ( kind < BUILDING_Infantry )
	{ // ��ͨ����
		int level = building_getlevel( city_index, kind );
		if ( level > 0 )
			return -1;

		Building *pBuilding = building_getptr( city_index, offset );
		if ( pBuilding )
		{ // ָ����λ��
			pBuilding->kind = kind;
			pBuilding->level = 1;
		}
		else
		{ // û��ָ����һ����λ
			for ( int tmpi = 0; tmpi < BUILDING_MAXNUM; tmpi++ )
			{
				if ( g_city[city_index].building[tmpi].kind <= 0 )
				{
					g_city[city_index].building[tmpi].kind = kind;
					g_city[city_index].building[tmpi].level = 1;
					break;
				}
			}
		}
	}
	else if ( kind < BUILDING_Silver )
	{ // ��Ӫ����
		int level = building_getlevel( city_index, kind );
		if ( level > 0 )
			return -1;

		BuildingBarracks *pBuilding = buildingbarracks_getptr( city_index, offset );
		if ( pBuilding )
		{ // ָ����λ��
			pBuilding->kind = kind;
			pBuilding->level = 1;
		}
		else
		{ // û��ָ����һ����λ
			for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
			{
				if ( g_city[city_index].building_barracks[tmpi].kind <= 0 )
				{
					g_city[city_index].building_barracks[tmpi].kind = kind;
					g_city[city_index].building_barracks[tmpi].level = 1;
					break;
				}
			}
		}
	}
	else if ( kind < BUILDING_Smithy )
	{ // ��Դ����
		BuildingRes *pBuilding = buildingres_getptr( city_index, offset );
		if ( pBuilding )
		{ // ָ����λ��
			pBuilding->kind = kind;
			pBuilding->level = 1;
		}
		else
		{ // û��ָ����һ����λ
			for ( int tmpi = 0; tmpi < BUILDING_RES_MAXNUM; tmpi++ )
			{
				if ( g_city[city_index].building_res[tmpi].kind <= 0 )
				{
					g_city[city_index].building_res[tmpi].kind = kind;
					g_city[city_index].building_res[tmpi].level = 1;
					break;
				}
			}
		}
	}
	else
	{ // ��ڹ���
		if ( kind == BUILDING_Smithy )
			city_function_open( &g_city[city_index], CITY_FUNCTION_SMITHY );
		else if ( kind == BUILDING_Wash )
			city_function_open( &g_city[city_index], CITY_FUNCTION_WASH );
		else if ( kind == BUILDING_Fangshi )
			city_function_open( &g_city[city_index], CITY_FUNCTION_FANGSHI );
		else if ( kind == BUILDING_Shop )
			city_function_open( &g_city[city_index], CITY_FUNCTION_SHOP );
		else if ( kind == BUILDING_Hero )
			city_function_open( &g_city[city_index], CITY_FUNCTION_HERO );
		else if ( kind == BUILDING_Wishing )
			city_function_open( &g_city[city_index], CITY_FUNCTION_WISHING );
	}
	return 0;
}

// ��������
int building_upgrade( int city_index, int kind, int offset )
{
	CITY_CHECK_INDEX( city_index );
	int level = 0;
	if ( kind < BUILDING_Infantry )
	{ // ��ͨ����
		Building *pBuilding = building_getptr( city_index, offset );
		if ( !pBuilding )
			return -1;
		if ( pBuilding->sec > 0 )
			return -1;
		level = pBuilding->level;
	}
	else if ( kind < BUILDING_Silver )
	{ // ��Ӫ����
		BuildingBarracks *pBuilding = buildingbarracks_getptr( city_index, offset );
		if ( !pBuilding )
			return -1;
		if ( pBuilding->trainsec > 0 )
			return -1;
		level = pBuilding->level;
	}
	else if ( kind < BUILDING_Smithy )
	{ // ��Դ����
		BuildingRes *pBuilding = buildingres_getptr( city_index, offset );
		if ( !pBuilding )
			return -1;
		level = pBuilding->level;
	}
	else
	{
		return -1;
	}

	BuildingUpgradeConfig *config = building_getconfig( kind, level );
	if ( !config )
		return -1;

	// �ٸ��ȼ��Ƿ�����
	if ( city_mainlevel( city_index ) < config->citylevel )
		return -1;

	// ��ɫ�ȼ��Ƿ�����
	if ( g_city[city_index].level < config->actorlevel )
		return -1;

	// ��Դ�Ƿ�����
	if ( g_city[city_index].silver < config->silver )
		return -1;
	if ( g_city[city_index].wood < config->wood )
		return -1;
	if ( g_city[city_index].food < config->food )
		return -1;
	if ( g_city[city_index].iron < config->iron )
		return -1;

	char ok = 0;
	if ( g_city[city_index].worker_sec <= 0 )
	{ // ��ͨ�������
		g_city[city_index].worker_op = BUILDING_OP_UPGRADE;
		g_city[city_index].worker_sec = config->sec;
		g_city[city_index].worker_kind = kind;
		g_city[city_index].worker_offset = offset;
		ok = 1;
	}
	else if ( g_city[city_index].worker_expire_ex > 0 && g_city[city_index].worker_sec_ex <= 0 )
	{ // ���ý������
		g_city[city_index].worker_op_ex = BUILDING_OP_UPGRADE;
		g_city[city_index].worker_sec_ex = config->sec;
		g_city[city_index].worker_kind_ex = kind;
		g_city[city_index].worker_offset_ex = offset;
		ok = 1;
	}
	else
	{ // ������з�æ
		return -1;
	}

	if ( ok )
	{
		// �ۼ���Դ
		city_changesilver( city_index, -config->silver, PATH_BUILDING_UPGRADE );
		city_changewood( city_index, -config->wood, PATH_BUILDING_UPGRADE );
		city_changefood( city_index, -config->food, PATH_BUILDING_UPGRADE );
		city_changeiron( city_index, -config->iron, PATH_BUILDING_UPGRADE );

		// ֪ͨ��������״̬
	}
	return 0;
}

// �������
int building_delete( int city_index, int kind, int offset )
{
	CITY_CHECK_INDEX( city_index );
	if ( kind == BUILDING_Militiaman_Infantry || kind == BUILDING_Militiaman_Cavalry || kind == BUILDING_Militiaman_Archer )
	{ // ���Ӫ
		BuildingBarracks *pBuilding = buildingbarracks_getptr( city_index, offset );
		if ( !pBuilding )
			return -1;
		if ( pBuilding->trainsec > 0 )
			return -1;
	}
	else if ( kind == BUILDING_Silver || kind == BUILDING_Wood || kind == BUILDING_Food || kind == BUILDING_Iron )
	{ // ũ��
	}
	else
	{
		return -1;
	}

	char ok = 0;
	if ( g_city[city_index].worker_sec <= 0 )
	{ // ��ͨ�������
		g_city[city_index].worker_op = BUILDING_OP_DELETE;
		g_city[city_index].worker_sec = global.building_delete_cd;
		g_city[city_index].worker_kind = kind;
		g_city[city_index].worker_offset = offset;
		ok = 1;
	}
	else if ( g_city[city_index].worker_expire_ex > 0 && g_city[city_index].worker_sec_ex <= 0 )
	{ // ���ý������
		g_city[city_index].worker_op_ex = BUILDING_OP_DELETE;
		g_city[city_index].worker_sec_ex = global.building_delete_cd;
		g_city[city_index].worker_kind_ex = kind;
		g_city[city_index].worker_offset_ex = offset;
		ok = 1;
	}
	else
	{ // ������з�æ
		return -1;
	}

	if ( ok )
	{

	}
	return 0;
}

// �������������������
int building_finish( int city_index, int op, int kind, int offset )
{
	CITY_CHECK_INDEX( city_index );
	int level = 0;
	if ( op == BUILDING_OP_BUILD )
	{
		building_create( city_index, kind, offset );
	}
	else if ( op == BUILDING_OP_UPGRADE )
	{
		if ( kind < BUILDING_Infantry )
		{ // ��ͨ����
			Building *pBuilding = building_getptr( city_index, offset );
			if ( !pBuilding )
				return -1;
			level = pBuilding->level;
			pBuilding->level += 1;
		}
		else if ( kind < BUILDING_Silver )
		{ // ��Ӫ����
			BuildingBarracks *pBuilding = buildingbarracks_getptr( city_index, offset );
			if ( !pBuilding )
				return -1;
			level = pBuilding->level;
			pBuilding->level += 1;
		}
		else if ( kind < BUILDING_Smithy )
		{ // ��Դ����
			BuildingRes *pBuilding = buildingres_getptr( city_index, offset );
			if ( !pBuilding )
				return -1;
			level = pBuilding->level;
			pBuilding->level += 1;
		}

		BuildingUpgradeConfig *config = building_getconfig( kind, level );
		if ( config )
		{ // ������
			city_actorexp( city_index, config->exp, PATH_BUILDING_UPGRADE );
		}

		// ֪ͨ�ͻ��˸���״̬
	}
	else if ( op == BUILDING_OP_DELETE )
	{
		if ( kind == BUILDING_Militiaman_Infantry || kind == BUILDING_Militiaman_Cavalry || kind == BUILDING_Militiaman_Archer )
		{ // ���Ӫ����
			BuildingBarracks *pBuilding = buildingbarracks_getptr( city_index, offset );
			if ( !pBuilding )
				return -1;
			pBuilding->level = 0;
		}
		else if ( kind == BUILDING_Silver || kind == BUILDING_Wood || kind == BUILDING_Food || kind == BUILDING_Iron )
		{ // ��Դ����
			BuildingRes *pBuilding = buildingres_getptr( city_index, offset );
			if ( !pBuilding )
				return -1;
			pBuilding->level = 0;
		}

		// ֪ͨ�ͻ��˸���״̬
	}
	return 0;
}

// ��ȡʿ������
int building_soldiers_total( int city_index, char kind )
{
	CITY_CHECK_INDEX( city_index );
	int total = 0;
	for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
	{
		if ( g_city[city_index].building_barracks[tmpi].kind == kind || 
			g_city[city_index].building_barracks[tmpi].kind == kind + 3 )
		{
			total += g_city[city_index].building_barracks[tmpi].soldiers;
		}
	}
	return total;
}

int building_sendlist( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	SLK_NetS_BuildingList pValue = { 0 };

	// ��ͨ����
	for ( int tmpi = 0; tmpi < BUILDING_MAXNUM; tmpi++ )
	{
		if ( pCity->building[tmpi].kind <= 0 )
			continue;
		pValue.m_building[pValue.m_building_count].m_kind = pCity->building[tmpi].kind;
		pValue.m_building[pValue.m_building_count].m_offset = tmpi;
		pValue.m_building[pValue.m_building_count].m_level = pCity->building[tmpi].level;
		pValue.m_building[pValue.m_building_count].m_sec = pCity->building[tmpi].sec;
		if ( pCity->building[tmpi].quicksec > 0 )
			pValue.m_building[pValue.m_building_count].m_quick = 1;
		pValue.m_building_count += 1;
	}

	// ��Ӫ����
	for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
	{
		if ( pCity->building_barracks[tmpi].kind <= 0 || pCity->building_barracks[tmpi].level <= 0 )
			continue;
		pValue.m_barracks[pValue.m_barracks_count].m_kind = pCity->building_barracks[tmpi].kind;
		pValue.m_barracks[pValue.m_barracks_count].m_offset = tmpi;
		pValue.m_barracks[pValue.m_barracks_count].m_level = pCity->building_barracks[tmpi].level;
		pValue.m_barracks[pValue.m_barracks_count].m_sec = pCity->building_barracks[tmpi].trainsec;
		if ( pCity->building_barracks[tmpi].quicksec > 0 )
			pValue.m_barracks[pValue.m_barracks_count].m_quick = 1;
		pValue.m_barracks_count += 1;
	}

	// ��Դ����
	for ( int tmpi = 0; tmpi < BUILDING_BARRACKS_MAXNUM; tmpi++ )
	{
		if ( pCity->building_res[tmpi].kind <= 0 || pCity->building_res[tmpi].level <= 0 )
			continue;
		pValue.m_res[pValue.m_res_count].m_kind = pCity->building_res[tmpi].kind;
		pValue.m_res[pValue.m_res_count].m_offset = tmpi;
		pValue.m_res[pValue.m_res_count].m_level = pCity->building_res[tmpi].level;
		pValue.m_res_count += 1;
	}

	// �������
	pValue.m_worker_kind = pCity->worker_kind;	
	pValue.m_worker_offset = pCity->worker_offset;
	pValue.m_worker_op = pCity->worker_op;
	pValue.m_worker_sec = pCity->worker_sec;
	pValue.m_worker_kind_ex = pCity->worker_kind_ex;
	pValue.m_worker_offset_ex = pCity->worker_offset_ex;
	pValue.m_worker_op_ex = pCity->worker_op_ex;
	pValue.m_worker_sec_ex = pCity->worker_sec_ex;
	pValue.m_worker_expire_ex = pCity->worker_expire_ex;
	pValue.m_levynum = pCity->levynum;
	pValue.m_function= pCity->function;
	netsend_buildinglist_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}
