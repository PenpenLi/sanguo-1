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
#include "actor_times.h"
#include "hero.h"
#include "city.h"
#include "building.h"
#include "city_attr.h"
#include "mail.h"
#include "girl.h"

extern Global global;
extern MYSQL *myData;
extern MYSQL *myGame;

extern Actor *g_actors;
extern int g_maxactornum;
extern Actor g_temp_actor[2];

extern int g_city_maxindex;
extern City *g_city;
extern int g_city_maxcount;

extern GirlInfo *g_girlinfo;
extern int g_girlinfo_maxnum;
i64 g_maxgirlid;

Girl *girl_getptr( int city_index, int kind )
{
	if ( city_index < 0 || city_index >= g_city_maxcount )
		return NULL;
	if ( kind <= 0 || kind >= ACTOR_GIRL_MAX )
		return NULL;
	return &g_city[city_index].girl[kind];
}

GirlInfoConfig *girl_getconfig( int kind, int color )
{
	if ( kind <= 0 || kind >= g_girlinfo_maxnum )
		return NULL;
	if ( color < 0 || color >= g_girlinfo[kind].maxnum )
		return NULL;
	return &g_girlinfo[kind].config[color];
}

void girl_makestruct( City *pCity, Girl *pGirl, SLK_NetS_Girl *pValue )
{
	pValue->m_kind = pGirl->kind;
	pValue->m_color = pGirl->color;
	pValue->m_soul = pGirl->soul;
	pValue->m_love_exp = pGirl->love_exp;
	pValue->m_love_level = pGirl->love_level;
	pValue->m_love_num = pGirl->love_num;
}

// ��һ��Ů��
int girl_getgirl( City *pCity, int kind, char path )
{
	if ( !pCity )
		return -1;
	if ( kind <= 0 || kind >= g_girlinfo_maxnum )
		return -1;

	// ����Ƿ��Ѿ������Ů����
	Girl *pHasGirl = girl_getptr( pCity->index, kind );
	if ( pHasGirl && pHasGirl->color > 0 )
	{
		GirlInfoConfig *config = girl_getconfig( kind, pHasGirl->color );
		if ( !config )
			return -1;
		// Ѱ�ü�ʹ����ˣ�ҲҪ����ȥ��������Ҫ��ʾ
		SLK_NetS_GirlGet pValue = { 0 };
		pValue.m_kind = kind;
		pValue.m_path = path;
		if ( config )
		{
			pValue.m_soulnum = config->soulchange;
			pHasGirl->soul += config->soulchange;
		}
		girl_makestruct( pCity, pHasGirl, &pValue.m_girl );
		netsend_girlget_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );
		wlog( 0, LOGOP_GIRLSOUL, path, kind, config->soulchange, pHasGirl->soul, pCity->actorid, city_mainlevel( pCity->index ) );
		return -1;
	}
	if ( g_girlinfo[kind].config[0].init_color <= 0 )
		return -1;
	
	pCity->girl[kind].actorid = pCity->actorid;
	pCity->girl[kind].kind = kind;
	pCity->girl[kind].color = (char)g_girlinfo[kind].config[0].init_color;
	pCity->girl[kind].love_level = 1;
	pCity->girl[kind].love_exp = 0;
	pCity->girl[kind].love_num = 0;
	pCity->girl[kind].love_fday = 0;

	SLK_NetS_GirlGet pValue = { 0 };
	pValue.m_kind = kind;
	pValue.m_path = path;
	girl_makestruct( pCity, &pCity->girl[kind], &pValue.m_girl );
	netsend_girlget_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );

	// ����
	actor_girl_save_auto( pCity->actorid, kind, &pCity->girl[kind], "actor_girl", NULL );
	wlog( 0, LOGOP_GIRL, path, kind, pCity->girl[kind].color, 0, pCity->actorid, city_mainlevel( pCity->index ) );
	return 0;
}

// ��һ��Ů����Ƭ
int girl_getsoul( City *pCity, int kind, int soul, char path )
{
	if ( !pCity )
		return -1;
	if ( kind <= 0 || kind >= g_girlinfo_maxnum || kind >= ACTOR_GIRL_MAX )
		return -1;

	pCity->girl[kind].actorid = pCity->actorid;
	pCity->girl[kind].kind = kind;
	pCity->girl[kind].soul += soul;
	girl_info( pCity, &pCity->girl[kind] );

	char v1[32] = { 0 };
	char v2[32] = { 0 };
	sprintf( v1, "%s%d", TAG_GIRL, kind );
	sprintf( v2, "%d", soul );
	actor_notify_pop_v( pCity->actor_index, 3339, v1, v2 );


	wlog( 0, LOGOP_GIRLSOUL, path, kind, soul, pCity->girl[kind].soul, pCity->actorid, city_mainlevel( pCity->index ) );
	if ( pCity->girl[kind].color == 0 && pCity->girl[kind].soul >= g_girlinfo[kind].config[0].soul )
	{ // �Զ��ϳ�
		pCity->girl[kind].soul -= g_girlinfo[kind].config[0].soul;
		girl_getgirl( pCity, kind, path );
	}
	return 0;
}

// Ů����Ϣ
int girl_info( City *pCity, Girl *pGirl )
{
	if ( !pCity || !pGirl )
		return -1;
	ACTOR_CHECK_INDEX( pCity->actor_index );
	SLK_NetS_Girl pValue = { 0 };
	girl_makestruct( pCity, pGirl, &pValue );
	netsend_girl_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

// Ů���б�
int girl_list( int actor_index )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return 0;
	SLK_NetS_GirlList pValue = { 0 };
	for ( char kind = 1; kind < ACTOR_GIRL_MAX; kind++ )
	{
		if ( kind >= g_girlinfo_maxnum )
			break;
		if ( pCity->girl[kind].kind <= 0 )
			continue;
		girl_makestruct( pCity, &pCity->girl[kind], &pValue.m_list[pValue.m_count] );
		pValue.m_count += 1;
	}
	netsend_girllist_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

void girl_gm_getall( City *pCity )
{
	if ( !pCity )
		return;
	for ( int kind = 1; kind < g_girlinfo_maxnum; kind++ )
	{
		girl_getgirl( pCity, kind, PATH_GM );
	}
}
