#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "db.h"
#include "global.h"
#include "actor.h"
#include "gameproc.h"
#include "item.h"
#include "system.h"
#include "map.h"
#include "server_netsend_auto.h"
#include "actor_send.h"
#include "actor_notify.h"
#include "hero.h"
#include "equip.h"
#include "city.h"
#include "building.h"

extern Global global;
extern MYSQL *myData;
extern MYSQL *myGame;

extern Actor *g_actors;
extern int g_maxactornum;

extern int g_city_maxindex;
extern City *g_city;
extern int g_city_maxcount;

extern OfficialForging *g_official_forging;
extern int g_official_forging_maxnum;

extern EquipInfo *g_equipinfo;
extern int g_equipinfo_maxnum;
i64 g_maxequipid;

// ��ұ�����δ����Ӣ�۵�װ��
Equip *actor_equip_getptr( int actor_index, int offset )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return NULL;
	if ( offset >= 0 && offset < MAX_ACTOR_EQUIPNUM )
	{ // װ����
		return &g_actors[actor_index].equip[offset];
	}
	else if ( offset >= EQUIP_BASEOFFSET )
	{ // δ����Ӣ�����ϵ�װ�� ����1002 kind=1 equip=2 װ��Ԥ��3λ
		int herokind = offset / EQUIP_BASEOFFSET;
		int equip_offset = offset % EQUIP_BASEOFFSET;
		int hero_index = actor_hero_getindex( actor_index, herokind );
		if ( hero_index >= 0 && hero_index < HERO_ACTOR_MAX )
		{ // ֻ����δ�����
			return &g_actors[actor_index].hero[hero_index].equip[equip_offset];
		}
	}
	return NULL;
}

// �Ѿ������Ӣ��װ��
Equip *city_equip_getptr( int city_index, int offset )
{
	if ( city_index < 0 || city_index >= g_city_maxcount )
		return NULL;
	if ( offset < EQUIP_BASEOFFSET )
		return NULL;
	int herokind = offset / EQUIP_BASEOFFSET;
	int equip_offset = offset % EQUIP_BASEOFFSET;
	int hero_index = city_hero_getindex( city_index, herokind );
	if ( hero_index >= 0 && hero_index < HERO_CITY_MAX )
	{ // ֻ����δ�����
		return &g_city[city_index].hero[hero_index].equip[equip_offset];
	}
	return NULL;
}

int equip_load( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	actor_equip_load_auto( g_actors[actor_index].actorid, actor_index, actor_equip_getptr, "actor_equip" );
	return 0;
}

int equip_save( int actor_index, FILE *fp )
{
	ACTOR_CHECK_INDEX( actor_index );
	// װ����
	int max_equipnum = MAX_DEFAULT_EQUIPNUM + g_actors[actor_index].equipext;
	if ( max_equipnum > MAX_ACTOR_EQUIPNUM )
		max_equipnum = MAX_ACTOR_EQUIPNUM;
	actor_equip_batch_save_auto( g_actors[actor_index].equip, max_equipnum, "actor_equip", fp );

	return 0;
}

int equip_maxid_init()
{
	MYSQL_RES		*res;
	MYSQL_ROW		row;
	char	szSQL[1024];

	sprintf( szSQL, "select max(id) from actor_equip" );
	if ( mysql_query( myGame, szSQL ) )
	{
		printf_msg( "Query failed (%s) [%s](%d)\n", mysql_error( myGame ), __FUNCTION__, __LINE__ );
		write_gamelog( "%s", szSQL );
		if ( mysql_ping( myGame ) != 0 )
			db_reconnect_game();
		return -1;
	}
	res = mysql_store_result( myGame );

	if ( !((row = mysql_fetch_row( res ))) )
	{
		mysql_free_result( res );
		return -1;
	}
	if ( row[0] )
		g_maxequipid = atoll( row[0] );
	else
		g_maxequipid = 1;
	g_maxequipid++;
	mysql_free_result( res );
	return 0;
}

int equip_gettype( short kind )
{
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return 0;
	return g_equipinfo[kind].type;
}

int equip_freeindex( int actor_index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Actor *pActor = &g_actors[actor_index];
	int max_equipnum = MAX_DEFAULT_EQUIPNUM + pActor->equipext;
	if ( max_equipnum > MAX_ACTOR_EQUIPNUM )
		max_equipnum = MAX_ACTOR_EQUIPNUM;

	int offset = -1;
	for ( int tmpi = 0; tmpi < max_equipnum; tmpi++ )
	{
		if ( pActor->equip[tmpi].kind <= 0 )
		{
			offset = tmpi;
			break;
		}
	}

	if ( offset < 0 || offset >= max_equipnum )
	{
		// װ��������
		return -1;
	}
	return offset;
}

 // ����װ����ʱ����ã�����մ�����װ��
int equip_insert( int actor_index, int offset )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( offset >= 0 && offset < MAX_ACTOR_EQUIPNUM )
	{
		if ( g_actors[actor_index].equip[offset].kind <= 0 )
			return -1;
		g_actors[actor_index].equip[offset].id = g_maxequipid;
		g_maxequipid++;
		g_actors[actor_index].equip[offset].actorid = g_actors[actor_index].actorid;
		g_actors[actor_index].equip[offset].offset = offset;
		actor_equip_save_auto( &g_actors[actor_index].equip[offset], "actor_equip", NULL );
	}
	return 0;
}

// ��Ҵ���װ��
int equip_create( int actor_index, short equipkind, EquipOut *pOut )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( equipkind <= 0 || equipkind >= g_equipinfo_maxnum )
		return -1;

	int offset = equip_freeindex( actor_index );
	if ( offset < 0 )
	{
		// װ��������
		return -2;
	}

	g_actors[actor_index].equip[offset].kind = equipkind;
	if ( pOut )
	{
		pOut->m_equip_kind = equipkind;
		pOut->m_equip_offset = offset;
	}

	// ����������ݵ����ݿ�
	equip_insert( actor_index, offset );
	return 0;
}

// ��һ��װ��
int equip_getequip( int actor_index, int equipkind, char path )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( equipkind <= 0 || equipkind >= g_equipinfo_maxnum )
		return -1;
	Actor *pActor = &g_actors[actor_index];

	// ��������
	EquipOut pOut;
	pOut.m_equip_kind = 0;
	pOut.m_equip_offset = -1;
	int ret = equip_create( actor_index, equipkind, &pOut );
	if ( ret < 0 )
		return -1;
	if ( pOut.m_equip_offset >= 0 && pOut.m_equip_offset < MAX_DEFAULT_EQUIPNUM )
	{
		equip_sendget( actor_index, pOut.m_equip_offset, path );
		wlog( 0, LOGOP_EQUIPGET, path, equipkind, 1, pActor->equip[pOut.m_equip_offset].id, g_actors[actor_index].actorid, city_mainlevel( g_actors[actor_index].city_index ) );
	}
	return 0;
}

// ɾ��һ��װ���ĸ���
int equip_deletebox( int actor_index, int equipoffset )
{
	char	szSQL[1024];
	char bigint[21];
	Equip *pEquip = NULL;
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;

	if ( equipoffset >= 0 && equipoffset < MAX_ACTOR_EQUIPNUM )
		pEquip = &g_actors[actor_index].equip[equipoffset];
	else
		return -1;

	if ( pEquip == NULL )
	{
		return -1;
	}
	// ���ݿ�ɾ��
	lltoa( pEquip->id, bigint, 10 );
	sprintf( szSQL, "delete from actor_equip where id='%s'", bigint );
	if ( mysql_query( myGame, szSQL ) )
	{
		printf_msg( "Query failed (%s)\n", mysql_error( myGame ) );
		write_gamelog( "%s", szSQL );
		if ( mysql_ping( myGame ) != 0 )
			db_reconnect_game();
		return -1;
	}
	// �ڴ�ɾ��
	memset( pEquip, 0, sizeof( Equip ) );
	return 0;
}

int equip_lostequip( int actor_index, int equipoffset, char path )
{
	Equip *pequip = NULL;
	int equipkind;
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( equipoffset >= 0 && equipoffset < MAX_ACTOR_EQUIPNUM )
		pequip = &g_actors[actor_index].equip[equipoffset];
	else
		return -1;

	if ( pequip->kind <= 0 )
		return -1;

	wlog( 0, LOGOP_EQUIPLOST, path, pequip->kind, 1, pequip->id, g_actors[actor_index].actorid, 0 );

	equipkind = pequip->kind;
	equip_deletebox( actor_index, equipoffset );

	// ���ͽ�ɫʧȥ��Ʒ
	equip_sendlost( actor_index, equipkind, equipoffset, path );
	return equipkind;
}

// �ֽ�
int equip_resolve( int actor_index, int equipoffset )
{
	Equip *pequip = NULL;
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( equipoffset >= 0 && equipoffset < MAX_ACTOR_EQUIPNUM )
		pequip = &g_actors[actor_index].equip[equipoffset];
	else
		return -1;

	if ( pequip->kind <= 0 || pequip->kind >= g_equipinfo_maxnum )
		return -1;

	int value = g_equipinfo[pequip->kind].prestige;
	if ( equip_lostequip( actor_index, equipoffset, PATH_RESOLVE ) > 0 )
	{
		city_changeprestige( g_actors[actor_index].city_index, value, PATH_RESOLVE );
	}
	return 0;
}

// ������չ��
int equip_buyext( int actor_index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Actor *pActor = &g_actors[actor_index];
	if ( pActor->equipext >= MAX_ACTOR_EQUIPNUM - MAX_DEFAULT_EQUIPNUM )
	{
		return -1;
	}

	if ( actor_change_token( actor_index, -global.equipext_token, PATH_EQUIPEXT, 0 ) < 0 )
	{
		return -1;
	}

	pActor->equipext += 10;
	if ( pActor->equipext > MAX_ACTOR_EQUIPNUM - MAX_DEFAULT_EQUIPNUM )
	{
		pActor->equipext = MAX_ACTOR_EQUIPNUM - MAX_DEFAULT_EQUIPNUM;
	}

	// ������
	int value[2] = { 0 };
	value[0] = 0;
	value[1] = pActor->equipext;
	actor_notify_value( actor_index, NOTIFY_EQUIP, 2, value, NULL );
	return 0;
}

//-----------------------------------------------------------------------------
// ����˵��: װ������װ�����������ǰһ��װ��ж����ǰһ��װ��
// ����    : actor_index - 
//           equip_offset- Դ����λ��
//-----------------------------------------------------------------------------
int equip_up( int actor_index, short herokind, int equip_offset )
{
	Hero *pHero = NULL;
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( equip_offset < 0 || equip_offset >= MAX_ACTOR_EQUIPNUM )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	pHero = actor_hero_getptr( actor_index, actor_hero_getindex( actor_index, herokind ) );
	if ( !pHero )
	{
		pHero = city_hero_getptr( g_actors[actor_index].city_index, HERO_BASEOFFSET + city_hero_getindex( g_actors[actor_index].city_index, herokind ) );
	}
	if ( !pHero )
	{
		return -1;
	}

	int index = equip_gettype( g_actors[actor_index].equip[equip_offset].kind ) - 1;
	if ( index < 0 || index >= EQUIP_TYPE_MAX )
		return -1;

	// �Ƿ��滻
	char replace = 0;
	// Ŀ��λ��
	Equip *pHeroEquip = &pHero->equip[index];
	int hero_equip_offset = pHero->kind * 1000 + index;
	if ( pHeroEquip->kind <= 0 )
		replace = 0;
	else
		replace = 1;

	// ����λ��
	Equip *pBagEquip = &g_actors[actor_index].equip[equip_offset];
	Equip tmpEquip;

	// ������������װ�����ĵ���
	memcpy( &tmpEquip, pBagEquip, sizeof(Equip) );
	memcpy( pBagEquip, pHeroEquip, sizeof(Equip) );
	memcpy( pHeroEquip, &tmpEquip, sizeof(Equip) );

	pBagEquip->offset = equip_offset;
	pHeroEquip->offset = hero_equip_offset;

	if ( replace == 1 )
	{
		equip_sendbag( actor_index, equip_offset );
	}
	else
	{
		equip_sendlost( actor_index, tmpEquip.kind, tmpEquip.offset, PATH_EQUIP_UP );
	}
	equip_sendhero( actor_index, pHero, index );

	// ��жװ�������ı�����Ļ�ص���Ӫ
	int oldsoldiers = pHero->soldiers;
	int troops = hero_troops( pCity, pHero );
	if ( oldsoldiers > troops )
	{
		HeroInfoConfig *config = hero_getconfig( herokind, pHero->color );
		if ( config )
		{
			pHero->soldiers -= (oldsoldiers - troops);
			city_changesoldiers( pCity->index, config->corps, (oldsoldiers - troops), PATH_HERO_SOLDIERS_EQUIP );
		}
	}
	
	// ����Ӣ����Ϣ
	hero_sendinfo( actor_index, pHero );
	return 0;
}

// ж���ϵ�װ��
int equip_down( int actor_index, short herokind, int index )
{
	Hero *pHero = NULL;
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( index < 0 || index >= EQUIP_TYPE_MAX )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;

	int max_equipnum = MAX_DEFAULT_EQUIPNUM + g_actors[actor_index].equipext;
	if ( max_equipnum > MAX_ACTOR_EQUIPNUM )
		max_equipnum = MAX_ACTOR_EQUIPNUM;

	// �ҵ�һ����λ
	int free_offset = equip_freeindex( actor_index );
	if ( free_offset < 0 || free_offset >= max_equipnum )
	{
		// װ��������
		return -2;
	}
	Equip *pFreeEquip = &g_actors[actor_index].equip[free_offset];

	// ��ȡӢ��װ��
	pHero = actor_hero_getptr( actor_index, actor_hero_getindex( actor_index, herokind ) );
	if ( !pHero )
	{
		pHero = city_hero_getptr( g_actors[actor_index].city_index, HERO_BASEOFFSET + city_hero_getindex( g_actors[actor_index].city_index, herokind ) );
	}
	if ( !pHero )
	{
		return -1;
	}
	Equip *pHeroEquip = &pHero->equip[index];
	int oldoffset = pHeroEquip->offset;

	// ж��
	memcpy( pFreeEquip, pHeroEquip, sizeof(Equip) );
	memset( pHeroEquip, 0, sizeof(Equip) );
	pFreeEquip->offset = free_offset;

	// ���ͱ��
	equip_sendget( actor_index, free_offset, PATH_EQUIP_DOWN );
	equip_sendlost( actor_index, pFreeEquip->kind, oldoffset, PATH_EQUIP_DOWN );

	// ��жװ�������ı�����Ļ�ص���Ӫ
	int oldsoldiers = pHero->soldiers;
	int troops = hero_troops( pCity, pHero );
	if ( oldsoldiers > troops )
	{
		HeroInfoConfig *config = hero_getconfig( herokind, pHero->color );
		if ( config )
		{
			pHero->soldiers -= (oldsoldiers - troops);
			city_changesoldiers( pCity->index, config->corps, (oldsoldiers - troops), PATH_HERO_SOLDIERS_EQUIP );
		}
	}

	// ����Ӣ����Ϣ
	hero_sendinfo( actor_index, pHero );
	return 0;
}

// ����װ���б�
int equip_list( int actor_index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;

	// ����װ���б�
	SLK_NetS_EquipList Value = { 0 };
	Value.m_equipext = g_actors[actor_index].equipext;
	Value.m_count = 0;
	for ( int tmpi = 0; tmpi < MAX_ACTOR_EQUIPNUM; tmpi++ )
	{
		if (  g_actors[actor_index].equip[tmpi].kind <= 0 )
			continue;
		Value.m_list[Value.m_count].m_offset = tmpi;
		Value.m_list[Value.m_count].m_kind = g_actors[actor_index].equip[tmpi].kind;
		Value.m_list[Value.m_count].m_washid[0] = g_actors[actor_index].equip[tmpi].washid[0];
		Value.m_list[Value.m_count].m_washid[1] = g_actors[actor_index].equip[tmpi].washid[1];
		Value.m_list[Value.m_count].m_washid[2] = g_actors[actor_index].equip[tmpi].washid[2];
		Value.m_list[Value.m_count].m_washid[3] = g_actors[actor_index].equip[tmpi].washid[3];
		Value.m_count++;
		if ( Value.m_count >= 100 )
		{
			netsend_equiplist_S( actor_index, SENDTYPE_ACTOR, &Value );
			Value.m_count = 0;
		}
	}

	// �Ѿ�װ����-δ�����
	for ( int heroindex = 0; heroindex < HERO_ACTOR_MAX; heroindex++ )
	{
		if ( g_actors[actor_index].hero[heroindex].kind <= 0 )
			continue;
		
		for ( int equipoffset = 0; equipoffset < 6; equipoffset++ )
		{
			if ( g_actors[actor_index].hero[heroindex].equip[equipoffset].kind <= 0 )
				continue;;
			Value.m_list[Value.m_count].m_offset = g_actors[actor_index].hero[heroindex].equip[equipoffset].offset;
			Value.m_list[Value.m_count].m_kind = g_actors[actor_index].hero[heroindex].equip[equipoffset].kind;
			Value.m_list[Value.m_count].m_washid[0] = g_actors[actor_index].hero[heroindex].equip[equipoffset].washid[0];
			Value.m_list[Value.m_count].m_washid[1] = g_actors[actor_index].hero[heroindex].equip[equipoffset].washid[1];
			Value.m_list[Value.m_count].m_washid[2] = g_actors[actor_index].hero[heroindex].equip[equipoffset].washid[2];
			Value.m_list[Value.m_count].m_washid[3] = g_actors[actor_index].hero[heroindex].equip[equipoffset].washid[3];
			Value.m_count++;
			if ( Value.m_count >= 100 )
			{
				netsend_equiplist_S( actor_index, SENDTYPE_ACTOR, &Value );
				Value.m_count = 0;
			}
		}
	}

	// �Ѿ�װ����-�����
	for ( int heroindex = 0; heroindex < HERO_CITY_MAX; heroindex++ )
	{
		if ( pCity->hero[heroindex].kind <= 0 )
			continue;

		for ( int equipoffset = 0; equipoffset < 6; equipoffset++ )
		{
			if ( pCity->hero[heroindex].equip[equipoffset].kind <= 0 )
				continue;;
			Value.m_list[Value.m_count].m_offset = pCity->hero[heroindex].equip[equipoffset].offset;
			Value.m_list[Value.m_count].m_kind = pCity->hero[heroindex].equip[equipoffset].kind;
			Value.m_list[Value.m_count].m_washid[0] = pCity->hero[heroindex].equip[equipoffset].washid[0];
			Value.m_list[Value.m_count].m_washid[1] = pCity->hero[heroindex].equip[equipoffset].washid[1];
			Value.m_list[Value.m_count].m_washid[2] = pCity->hero[heroindex].equip[equipoffset].washid[2];
			Value.m_list[Value.m_count].m_washid[3] = pCity->hero[heroindex].equip[equipoffset].washid[3];
			Value.m_count++;
			if ( Value.m_count >= 100 )
			{
				netsend_equiplist_S( actor_index, SENDTYPE_ACTOR, &Value );
				Value.m_count = 0;
			}
		}
	}

	netsend_equiplist_S( actor_index, SENDTYPE_ACTOR, &Value );
	return 0;
}

// ����Ӣ��װ���б�
int equip_heroupdate( int actor_index, Hero *pHero )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( !pHero )
		return -1;
	// ����װ���б�
	SLK_NetS_HeroEquip Value = { 0 };
	Value.m_herokind = pHero->kind;
	Value.m_count = 0;
	// �Ѿ�װ����-δ�����
	for ( int equipoffset = 0; equipoffset < 6; equipoffset++ )
	{
		Value.m_list[Value.m_count].m_offset = pHero->equip[equipoffset].offset;
		Value.m_list[Value.m_count].m_kind = pHero->equip[equipoffset].kind;
		Value.m_list[Value.m_count].m_washid[0] = pHero->equip[equipoffset].washid[0];
		Value.m_list[Value.m_count].m_washid[1] = pHero->equip[equipoffset].washid[1];
		Value.m_list[Value.m_count].m_washid[2] = pHero->equip[equipoffset].washid[2];
		Value.m_list[Value.m_count].m_washid[3] = pHero->equip[equipoffset].washid[3];
		Value.m_count++;
	}
	netsend_heroequip_S( actor_index, SENDTYPE_ACTOR, &Value );
	return 0;
}

int equip_sendbag( int actor_index, int offset )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Equip *pEquip = actor_equip_getptr( actor_index, offset );
	if ( pEquip == NULL )
		return -1;
	SLK_NetS_Equip Value = { 0 };
	Value.m_offset = pEquip->offset;
	Value.m_kind = pEquip->kind;
	Value.m_washid[0] = pEquip->washid[0];
	Value.m_washid[1] = pEquip->washid[1];
	Value.m_washid[2] = pEquip->washid[2];
	Value.m_washid[3] = pEquip->washid[3];
	netsend_equip_S( actor_index, SENDTYPE_ACTOR, &Value );
	return 0;
}

int equip_sendhero( int actor_index, Hero *pHero, int index )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( index < 0 || index >= EQUIP_TYPE_MAX )
		return -1;
	Equip *pEquip = &pHero->equip[index];
	if ( pEquip == NULL )
		return -1;
	SLK_NetS_Equip Value = { 0 };
	Value.m_offset = pEquip->offset;
	Value.m_kind = pEquip->kind;
	Value.m_washid[0] = pEquip->washid[0];
	Value.m_washid[1] = pEquip->washid[1];
	Value.m_washid[2] = pEquip->washid[2];
	Value.m_washid[3] = pEquip->washid[3];
	netsend_equip_S( actor_index, SENDTYPE_ACTOR, &Value );
	return 0;
}

int equip_sendget( int actor_index, int offset, char path )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Equip *pEquip = actor_equip_getptr( actor_index, offset );
	if ( pEquip == NULL )
		return -1;

	SLK_NetS_EquipGet pValue = { 0 };
	pValue.m_offset = offset;
	pValue.m_kind = pEquip->kind;
	pValue.m_path = path;
	netsend_equipget_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

int equip_sendlost( int actor_index, short equipkind, int offset, char path )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	SLK_NetS_EquipLost pValue = { 0 };
	pValue.m_offset = offset;
	pValue.m_kind = equipkind;
	pValue.m_path = path;
	netsend_equiplost_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}


// ��������ʱ��
int equip_forgingtime( int city_index, short kind )
{
	CITY_CHECK_INDEX( city_index );
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return -1;
	return g_equipinfo[kind].sec;
}

// ����
int equip_forging( int actor_index, short kind )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( pCity->forgingsec > 0 )
		return -1;
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return -1;

	// �������
	if ( pCity->level < g_equipinfo[kind].actorlevel )
		return -1;
	if ( pCity->silver < g_equipinfo[kind].silver )
		return -1;
	for ( int tmpi = 0; tmpi < 6; tmpi++ )
	{
		if ( g_equipinfo[kind].material_kind[tmpi] <= 0 )
			continue;
		if ( item_getitemnum( actor_index, g_equipinfo[kind].material_kind[tmpi] ) < g_equipinfo[kind].material_num[tmpi] )
			return -1;
	}
	
	// �۳�
	city_changesilver( pCity->index, -g_equipinfo[kind].silver, PATH_EQUIP_FORGING );
	for ( int tmpi = 0; tmpi < 6; tmpi++ )
	{
		if ( g_equipinfo[kind].material_kind[tmpi] <= 0 )
			continue;
		item_lost( actor_index, g_equipinfo[kind].material_kind[tmpi], g_equipinfo[kind].material_num[tmpi], PATH_EQUIP_FORGING );
	}

	pCity->forgingkind = kind;
	pCity->forgingsec = g_equipinfo[kind].sec;
	building_smithy_send( pCity->index );

	wlog( 0, LOGOP_FORGING, PATH_EQUIP_FORGING, kind, 0, 0, pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

int equip_forging_quick( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	int sec = pCity->forgingsec;
	if ( sec <= 0 )
		return -1;
	int kind = pCity->forgingkind;
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return -1;

	int token = (int)ceil( (sec / 60 + 1) * global.forgingquick_token );
	if ( actor_change_token( actor_index, -token, PATH_FORGING_QUICK, 0 ) < 0 )
		return -1;
	pCity->forgingsec = 0;
	building_smithy_send( pCity->index );
	wlog( 0, LOGOP_FORGING, PATH_FORGING_QUICK, kind, sec, pCity->ofkind[0], pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

int equip_forging_freequick( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	int sec = pCity->forgingsec;
	if ( sec <= 0 )
		return -1;
	int kind = pCity->forgingkind;
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return -1;
	int ofkind = pCity->ofkind[0];
	if ( ofkind <= 0 || ofkind >= g_official_forging_maxnum )
		return -1;

	// -1 ��������Ѿ�ʹ�ù���Ѽ���
	if ( pCity->ofquick[0] == -1 )
		return -1;
	
	if ( pCity->ofquick[0] == 0 )
	{ // ��������ʱ��
		pCity->forgingsec -= g_official_forging[ofkind].quick;
	}

	// ���
	if ( pCity->forgingsec <= 0 )
	{
		pCity->forgingsec = 0;
		building_smithy_send( pCity->index );
	}
	else
	{
		// ����������Ϣ
		pCity->ofquick[0] = -1;
		city_officialhire_sendinfo( pCity, 0 );
		building_smithy_send( pCity->index );
	}

	wlog( 0, LOGOP_FORGING, PATH_FORGING_FREEQUICK, kind, sec, pCity->ofkind[0], pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

// װ��������ȡ
int equip_forging_get( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( pCity->forgingsec > 0 )
		return -1;
	int kind = pCity->forgingkind;
	if ( kind <= 0 || kind >= g_equipinfo_maxnum )
		return -1;

	equip_getequip( actor_index, kind, PATH_EQUIP_FORGING );

	pCity->ofquick[0] = 0;
	city_officialhire_sendinfo( pCity, 0 );

	pCity->forgingkind = 0;
	pCity->forgingsec = 0;
	building_smithy_send( pCity->index );
	return 0;
}

// GMָ��ʹ��,ɾ�����е���
int equip_clear( int actor_index )
{
	int tmpi = 0;
	int num = 0;
	for ( tmpi = 0; tmpi < MAX_ACTOR_EQUIPNUM; tmpi++ )
	{
		if ( g_actors[actor_index].equip[tmpi].kind > 0 )
		{
			equip_lostequip( actor_index, tmpi, PATH_GM );
		}
	}

	return 0;
}