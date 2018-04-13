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

extern ItemKind *g_itemkind;
extern int g_itemkind_maxnum;

extern NationHero *g_nation_hero;
extern int g_nation_hero_maxcount;

extern GirlInfo *g_girlinfo;
extern int g_girlinfo_maxnum;

extern GirlLove *g_girllove;
extern int g_girllove_maxnum;

extern GirlSon *g_girlson;
extern int g_girlson_maxnum;

extern FangshiNode *g_fangshi_node;
extern int g_fangshi_node_maxnum;

extern FangshiPalace *g_fangshi_palace;
extern int g_fangshi_palace_maxnum;

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

GirlLove *girl_love_getconfig( int level )
{
	if ( level <= 0 || level >= g_girllove_maxnum )
		return NULL;
	return &g_girllove[level];
}

void girl_makestruct( City *pCity, Girl *pGirl, SLK_NetS_Girl *pValue )
{
	pValue->m_kind = pGirl->kind;
	pValue->m_color = pGirl->color;
	pValue->m_soul = pGirl->soul;
	pValue->m_sflag = pGirl->sflag;
	pValue->m_herokind = pGirl->herokind;
	pValue->m_love_exp = pGirl->love_exp;
	pValue->m_love_level = pGirl->love_level;
	pValue->m_love_today = pGirl->love_today;
}

// ��һ��Ů��
int girl_getgirl( City *pCity, int kind, char path )
{
	if ( !pCity )
		return -1;
	if ( kind <= 0 || kind >= g_girlinfo_maxnum )
		return -1;
	if ( !g_girlinfo[kind].config )
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
	pCity->girl[kind].sflag = 0;
	pCity->girl[kind].herokind = 0;
	pCity->girl[kind].love_level = 1;
	pCity->girl[kind].love_exp = 0;
	pCity->girl[kind].love_today = 0;

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
	if ( !g_girlinfo[kind].config )
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

//  ÿ���������
void girl_update()
{
	for ( int city_index = 0; city_index < g_city_maxindex/*ע�⣺ʹ������λ�ã�Ϊ��Ч��*/; city_index++ )
	{
		if ( g_city[city_index].actorid <= 0 )
			continue;
		for ( char kind = 1; kind < ACTOR_GIRL_MAX; kind++ )
		{
			if ( g_city[city_index].girl[kind].kind > 0 )
			{
				g_city[city_index].girl[kind].sflag &= ~(1 << GIRL_SFLAG_MAKELOVE);
				g_city[city_index].girl[kind].love_today = 0;
			}
		}
		if ( g_city[city_index].actor_index >= 0 )
		{ // ���߸���
			girl_list( g_city[city_index].actor_index );
		}
	}
}

// ί���н�
int girl_allot( int actor_index, short herokind, short girlkind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	if ( girlkind <= 0 || girlkind >= g_girlinfo_maxnum || girlkind >= ACTOR_GIRL_MAX )
		return -1;
	Hero *pHero = hero_getptr( actor_index, herokind );
	if ( !pHero )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, girlkind );
	if ( !pGirl )
		return -1;
	if ( pGirl->herokind > 0 )
		return -1;
	/*if ( pHero->girlkind > 0 && pGirl->herokind > 0 )
		return -1;*/
	pHero->girlkind = (char)girlkind;
	pHero->sontime = 0;
	pGirl->herokind = herokind;
	pGirl->love_level = 1;
	pGirl->love_exp = 0;
	pGirl->love_today = 0;
	pGirl->sflag = 0;
	hero_attr_calc( pCity, pHero );
	city_battlepower_hero_calc( pCity );
	hero_sendinfo( pCity->actor_index, pHero );
	girl_info( pCity, pGirl );
	return 0;
}

// ���ί��
int girl_unallot( int actor_index, short kind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	Hero *pHero = hero_getptr( actor_index, pGirl->herokind );
	if ( !pHero )
		return -1;
	pHero->girlkind = 0;
	pHero->sontime = 0;
	pGirl->herokind = 0;
	hero_attr_calc( pCity, pHero );
	city_battlepower_hero_calc( pCity );
	hero_sendinfo( pCity->actor_index, pHero );
	girl_info( pCity, pGirl );
	return 0;
}

// ͻ��
int girl_colorup( int actor_index, short kind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->color >= ITEM_COLOR_LEVEL_PURPLE )
		return -1;
	GirlInfoConfig *config = girl_getconfig( kind, pGirl->color );
	if ( !config )
		return -1;
	if ( config->soul <= 0 )
		return -1;
	if ( pGirl->soul < config->soul )
	{
		actor_notify_pop( actor_index, 3404 );
		return -1;
	}
	pGirl->soul -= config->soul;
	pGirl->color += 1;
	if ( pGirl->herokind > 0 )
	{
		Hero *pHero = hero_getptr( actor_index, pGirl->herokind );
		if ( pHero )
		{
			hero_attr_calc( pCity, pHero );
			city_battlepower_hero_calc( pCity );
			hero_sendinfo( pCity->actor_index, pHero );
		}
	}
	wlog( 0, LOGOP_GIRLSOUL, PATH_GIRLCOLORUP, kind, -config->soul, pGirl->soul, pCity->actorid, city_mainlevel( pCity->index ) );
	girl_info( pCity, pGirl );
	return 0;
}

// ���ܶȵ���ʹ��
int girl_loveitemuse( int actor_index, short kind, short itemkind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->herokind <= 0 )
		return -1;
	if ( itemkind <= 0 || itemkind >= g_itemkind_maxnum )
		return -1;
	short ability0 = item_get_base_ability( itemkind, 0 );
	short ability1 = item_get_base_ability( itemkind, 1 );
	int value0 = item_get_base_value( itemkind, 0 );
	int value1 = item_get_base_value( itemkind, 1 );
	if ( ability0 != ITEM_ABILITY_GIRLTYPE || ability1 != ITEM_ABILITY_GIRLLOVEEXP )
		return -1;

	if ( item_lost( actor_index, itemkind, 1, PATH_ITEMUSE ) < 0 )
	{ // û�е��ߣ���ôʹ����ʯ
		int price = item_gettoken( itemkind );
		if ( actor_change_token( actor_index, -price, PATH_ITEMUSE, itemkind ) == -2 )
		{
			return -1;
		}
	}

	// �������ܶ�
	girl_addloveexp( pCity, pGirl, value1, PATH_ITEMUSE );
	return 0;
}

// ϲ������
int girl_marry( int actor_index, short kind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->herokind <= 0 )
		return -1;
	if ( pGirl->love_level < global.girl_marry_lovelevel )
		return -1;
	pGirl->sflag |= (1 << GIRL_SFLAG_MARRY);
	girl_info( pCity, pGirl );
	return 0;
}

// ���ܻ���
int girl_makelove( int actor_index, short kind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->herokind <= 0 )
		return -1;
	if ( (pGirl->sflag & (1 << GIRL_SFLAG_MARRY)) == 0 )
		return -1; // ����Ժ�������ܻ���
	if ( (pGirl->sflag & (1 << GIRL_SFLAG_MAKELOVE)) == 1 )
		return -1; // �����Ѿ����ܻ���
	if ( pGirl->love_level >= g_girllove_maxnum )
		return -1;
	GirlLove *loveconfig = girl_love_getconfig( pGirl->love_level );
	if ( !loveconfig )
		return -1;
	Hero *pHero = hero_getptr( actor_index, pGirl->herokind );
	if ( !pHero )
		return -1;
	if ( pHero->sontime > 0 )
		return -1;

	// �������ܶ�
	girl_addloveexp( pCity, pGirl, loveconfig->makelove_exp, PATH_GIRLMAKELOVE );

	// ������
	int born = 0;
	if ( loveconfig->soncount > 0 && pHero->sonnum < loveconfig->soncount )
	{
		if ( pHero->kind < g_girlson_maxnum && pHero->sonnum < g_girlson[pHero->kind].maxnum )
		{
			if ( g_girlson[pHero->kind].config )
			{
				int odds = g_girlson[pHero->kind].config[pHero->sonnum].born_odds;
				if ( rand() % 100 < odds )
				{
					pHero->sontime = (int)time( NULL ) + g_girlson[pHero->kind].config[pHero->sonnum].grow_sec;
					hero_sendinfo( pCity->actor_index, pHero );
					born = 1;
				}
			}
		}
	}
	pGirl->sflag |= (1 << GIRL_SFLAG_MAKELOVE);
	SLK_NetS_GirlLoveResult pValue = { 0 };
	pValue.m_kind = (char)kind;
	pValue.m_sflag = pGirl->sflag;
	pValue.m_born = born;
	pValue.m_makelove_exp = loveconfig->makelove_exp;
	netsend_girlloveresult_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

// ���ܶ���������
float girl_loveexp_speed( short herokind, short kind, char color )
{
	GirlInfoConfig *config = girl_getconfig( kind, color );
	if ( !config )
		return 1.0f;
	short star = 0;
	if ( config->private_herokind == herokind )
	{
		star = config->love_star + config->private_love_star;
	}
	else
	{
		star = config->love_star;
	}
	return (float)(1 + (star - 1) * 0.5);
}

// ������ȡ���Ƕ�
int girl_addloveexp_killenemy( City *pCity, short herokind, short kind )
{
	if ( !pCity )
		return -1;
	if ( herokind <= 0 || kind <= 0 )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->love_level < 0 || pGirl->love_level >= g_girllove_maxnum - 1 )
		return -1;
	float speed = girl_loveexp_speed( herokind, pGirl->kind, pGirl->color );
	int maxexp = (int)ceil(g_girllove[pGirl->love_level].today_maxexp*speed);
	if ( pGirl->love_today >= maxexp )
		return -1;
	int add = (int)ceil( g_girllove[pGirl->love_level].killenemy_exp*speed );
	girl_addloveexp( pCity, pGirl, add, PATH_FIGHT );
	return 0;
}
int girl_addloveexp_citywar( City *pCity, short herokind, short kind )
{
	if ( !pCity )
		return -1;
	if ( herokind <= 0 || kind <= 0 )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->love_level < 0 || pGirl->love_level >= g_girllove_maxnum - 1 )
		return -1;
	float speed = girl_loveexp_speed( herokind, pGirl->kind, pGirl->color );
	int maxexp = (int)ceil( g_girllove[pGirl->love_level].today_maxexp*speed );
	if ( pGirl->love_today >= maxexp )
		return -1;
	int add = (int)ceil( g_girllove[pGirl->love_level].citywar_exp*speed );
	girl_addloveexp( pCity, pGirl, add, PATH_FIGHT );
	return 0;
}
int girl_addloveexp_nationwar( City *pCity, short herokind, short kind )
{
	if ( !pCity )
		return -1;
	if ( herokind <= 0 || kind <= 0 )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->love_level < 0 || pGirl->love_level >= g_girllove_maxnum - 1 )
		return -1;
	float speed = girl_loveexp_speed( herokind, pGirl->kind, pGirl->color );
	int maxexp = (int)ceil( g_girllove[pGirl->love_level].today_maxexp*speed );
	if ( pGirl->love_today >= maxexp )
		return -1;
	int add = (int)ceil( g_girllove[pGirl->love_level].nationwar_exp*speed );
	girl_addloveexp( pCity, pGirl, add, PATH_FIGHT );
	return 0;
}
int girl_addloveexp_kingwar( City *pCity, short herokind, short kind )
{
	if ( !pCity )
		return -1;
	if ( herokind <= 0 || kind <= 0 )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->love_level < 0 || pGirl->love_level >= g_girllove_maxnum - 1 )
		return -1;
	float speed = girl_loveexp_speed( herokind, pGirl->kind, pGirl->color );
	int maxexp = (int)ceil( g_girllove[pGirl->love_level].today_maxexp*speed );
	if ( pGirl->love_today >= maxexp )
		return -1;
	int add = (int)ceil( g_girllove[pGirl->love_level].kingwar_exp*speed );
	girl_addloveexp( pCity, pGirl, add, PATH_FIGHT );
	return 0;
}

// �������Ƕ�
int girl_addloveexp( City *pCity, Girl *pGirl, int exp, short path )
{
	if ( !pCity )
		return -1;
	if ( !pGirl )
		return -1;
	if ( pGirl->love_level < 0 || pGirl->love_level >= g_girllove_maxnum-1 )
		return -1;
	
	pGirl->love_exp += exp;
	if ( path != PATH_ITEMUSE && path != PATH_GIRLMAKELOVE )
	{
		pGirl->love_today += exp;
	}
	if ( pGirl->love_exp >= g_girllove[pGirl->love_level].exp )
	{
		pGirl->love_exp -= g_girllove[pGirl->love_level].exp;
		pGirl->love_level += 1;
	}

	if ( pCity->actor_index >= 0 )
	{
		SLK_NetS_GirlLove pValue = { 0 };
		pValue.m_kind = pGirl->kind;
		pValue.m_love_level = pGirl->love_level;
		pValue.m_love_exp = pGirl->love_exp;
		pValue.m_love_today = pGirl->love_today;
		pValue.m_add = exp;
		pValue.m_path = path;
		netsend_girllove_S( pCity->actor_index, SENDTYPE_ACTOR, &pValue );
	}

	return 0;
}

// ��Ů��ʦ
int girl_son_growth( int actor_index, short kind )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	Girl *pGirl = girl_getptr( pCity->index, kind );
	if ( !pGirl )
		return -1;
	if ( pGirl->herokind <= 0 )
		return -1;
	Hero *pHero = hero_getptr( actor_index, pGirl->herokind );
	if ( !pHero )
		return -1;
	if ( pHero->sontime <= 0 )
		return -1;
	if ((int)time(NULL) < pHero->sontime )
		return -1;
	if ( pHero->kind >= g_girlson_maxnum )
		return -1;
	if ( pHero->sonnum < g_girlson[pHero->kind].maxnum-1 )
	{
		pHero->sonnum += 1;
	}
	pHero->sontime = 0;
	hero_attr_calc( pCity, pHero );
	city_battlepower_hero_calc( pCity );
	hero_sendinfo( pCity->actor_index, pHero );
	girl_info( pCity, pGirl );
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

int girl_gm_son_growth_quick( City *pCity, short herokind )
{
	if ( !pCity )
		return -1;
	Hero *pHero = hero_getptr( pCity->actor_index, herokind );
	if ( !pHero )
		return -1;
	if ( pHero->sontime <= 0 )
		return -1;
	pHero->sontime = (int)time( NULL )+30;
	hero_attr_calc( pCity, pHero );
	city_battlepower_hero_calc( pCity );
	hero_sendinfo( pCity->actor_index, pHero );

	Girl *pGirl = girl_getptr( pCity->index, pHero->girlkind );
	if ( pGirl )
	{
		girl_info( pCity, pGirl );
	}
	return 0;
}

// ��ȡ����н���Ӧ��Ů��
char girl_withherokind( short herokind )
{
	for ( char kind = 1; kind < g_girlinfo_maxnum; kind++ )
	{
		if ( g_girlinfo[kind].config && g_girlinfo[kind].config[0].private_herokind == herokind )
		{
			return kind;
		}
	}
	return 0;
}

// ������Ϣ
int fangshi_sendinfo( int actor_index )
{
	ACTOR_CHECK_INDEX(actor_index);
	// �ȼ��ǰһ��Ľ����Ƿ���ȡ
	int fday = system_getfday();
	if ( g_actors[actor_index].fs_awardfday != fday )
	{
		fangshi_visit_getaward( actor_index );
		g_actors[actor_index].fs_nodeid = 0;
		g_actors[actor_index].fs_awardfday = fday;
	}
	SLK_NetS_FsInfo pValue = { 0 };
	pValue.m_freenum = actor_get_today_char_times( actor_index, TODAY_CHAR_FANSHI_VISIT_FREE );
	pValue.m_nodeid = g_actors[actor_index].fs_nodeid;
	for ( int tmpi = 0; tmpi < FANGSHI_AWARDNUM; tmpi++ )
	{
		if ( g_actors[actor_index].fs_awardkind[tmpi] > 0 )
		{
			pValue.m_awardlist[pValue.m_awardcount].m_kind = g_actors[actor_index].fs_awardkind[tmpi];
			pValue.m_awardlist[pValue.m_awardcount].m_num = g_actors[actor_index].fs_awardnum[tmpi];
			pValue.m_awardcount += 1;
		}
	}
	netsend_fsinfo_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

// ��һ�ڵ�
char fangshi_next_nodeid( char nodeid )
{
	if ( nodeid < 0 || nodeid >= g_fangshi_node_maxnum )
		return 0;
	FangshiNode *node = &g_fangshi_node[nodeid];
	if ( !node )
		return 0;
	char nextid = 0;
	int odds = rand() % 100;
	if ( odds < node->nextodds[0] )
	{
		nextid = (char)node->nextid[0];
	}
	else if ( odds < node->nextodds[0] + node->nextodds[1] )
	{
		nextid = (char)node->nextid[1];
	}
	else if ( odds < node->nextodds[0] + node->nextodds[1] + node->nextodds[2] )
	{
		nextid = (char)node->nextid[2];
	}
	return nextid;
}

// ����Ѱ��
int fangshi_visit( int actor_index, int type )
{
	ACTOR_CHECK_INDEX( actor_index );
	int count = 0;
	if ( type == 0 )
	{ // ���Ѱ��
		char freenum = actor_get_today_char_times( actor_index, TODAY_CHAR_FANSHI_VISIT_FREE );
		if ( freenum >= global.fangshi_visit_freenum )
		{
			return -1;
		}
		freenum += 1;
		actor_set_today_char_times( actor_index, TODAY_CHAR_FANSHI_VISIT_FREE, freenum );
		count = 1;
	}
	else if ( type == 1 )
	{ // Ԫ��һ��Ѱ��
		if ( actor_change_token( actor_index, -global.fangshi_visit_token, PATH_FANGSHI, 0 ) < 0 )
		{
			return -1;
		}
		count = 1;
	}
	else if ( type == 2 )
	{ // Ԫ��N��Ѱ��
		int awardcount = 0;
		for ( int tmpi = 0; tmpi < FANGSHI_AWARDNUM; tmpi++ )
		{
			if ( g_actors[actor_index].fs_awardkind[tmpi] > 0 )
				awardcount += 1;
		}
		count = FANGSHI_AWARDNUM - awardcount;
		if ( count <= 0 )
			return -1;
		if ( actor_change_token( actor_index, -global.fangshi_visit_token*count, PATH_FANGSHI, 0 ) < 0 )
		{
			return -1;
		}
	}
	else
		return -1;

	SLK_NetS_FsVisitResult pValue = { 0 };
	pValue.m_freenum = actor_get_today_char_times( actor_index, TODAY_CHAR_FANSHI_VISIT_FREE );
	for ( int tmpi = 0; tmpi < count; tmpi++ )
	{
		// ���뵱ǰ�ڵ㽱��
		char nodeid = g_actors[actor_index].fs_nodeid;
		if ( nodeid < 0 || nodeid >= g_fangshi_node_maxnum )
		{
			nodeid = 0;
			g_actors[actor_index].fs_nodeid = 0;
		}
		FangshiNode *node = &g_fangshi_node[nodeid];
		if ( !node )
			continue;

		// ���佱��
		AwardGetInfo getinfo = { 0 };
		char girlkind = 0;
		awardgroup_random( node->awardgroup, 0, &getinfo );
		if ( getinfo.kind[0] >= AWARDKIND_GIRLBASE && getinfo.kind[0] < AWARDKIND_GIRLSOULBASE )
		{ // �������Ƿ���Ƭ��Ҫ����Ƿ�������Ů�������ھ�ת��
			Girl *pGirl = girl_getptr( actor_index, getinfo.kind[0] );
			if ( pGirl && pGirl->color > 0 )
			{
				GirlInfoConfig *config = girl_getconfig( pGirl->kind, pGirl->color );
				if ( config )
				{
					getinfo.kind[0] = getinfo.kind[0] + 1000;
					getinfo.num[0] = config->soulchange;
					girlkind = pGirl->kind;
				}

			}
		}
		// �ŵ������б�
		for ( int i = 0; i < FANGSHI_AWARDNUM; i++ )
		{
			if ( g_actors[actor_index].fs_awardkind[i] <= 0 )
			{
				g_actors[actor_index].fs_awardkind[i] = getinfo.kind[0];
				g_actors[actor_index].fs_awardnum[i] = getinfo.num[0];
				break;
			}
		}

		// ��һ���ڵ�
		g_actors[actor_index].fs_nodeid = fangshi_next_nodeid( nodeid );
		pValue.m_list[pValue.m_count].m_nodeid = g_actors[actor_index].fs_nodeid;
		pValue.m_list[pValue.m_count].m_awardkind = getinfo.kind[0];
		pValue.m_list[pValue.m_count].m_awardnum = getinfo.num[0];
		pValue.m_list[pValue.m_count].m_girlkind = girlkind;
		pValue.m_count += 1;
	}
	netsend_fsvisitresult_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

// ��ȡ����Ѱ�ý���
int fangshi_visit_getaward( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	for ( int tmpi = 0; tmpi < FANGSHI_AWARDNUM; tmpi++ )
	{
		if ( g_actors[actor_index].fs_awardkind[tmpi] > 0 )
		{
			award_getaward( actor_index, g_actors[actor_index].fs_awardkind[tmpi], g_actors[actor_index].fs_awardnum[tmpi], -1, PATH_FANGSHI, NULL );
			g_actors[actor_index].fs_awardkind[tmpi] = 0;
			g_actors[actor_index].fs_awardnum[tmpi] = 0;
		}
	}
	return 0;
}

// ���нڵ㽱��
int fangshi_node_sendaward( int actor_index, int nodeid )
{
	ACTOR_CHECK_INDEX( actor_index );
	if ( nodeid < 0 || nodeid >= g_fangshi_node_maxnum )
		return -1;
	awardgroup_sendinfo( actor_index, g_fangshi_node[nodeid].awardgroup, 5, nodeid, 8 );
	return 0;
}

// ���һ������
int _fangshi_palace_random( int *kind, int *num, int *weight, int count, int *totalweight, int *outkind, int *outnum )
{
	int allvalue = *totalweight;
	int curvalue = 0;
	int odds = allvalue > 0 ? rand() % allvalue : 0;
	for ( int tmpi = 0; tmpi < count; tmpi++ )
	{
		// ��������ֵ��ʽ���
		int awardkind = kind[tmpi];
		int awardnum = num[tmpi];
		if ( awardkind <= 0 || awardnum <= 0 )
			continue;
		curvalue = weight[tmpi];
		if ( curvalue > 0 && curvalue > odds )
		{
			*outkind = awardkind;
			*outnum = awardnum;
			kind[tmpi] = 0;
			num[tmpi] = 0;
			*totalweight -= curvalue;
			break;
		}
		odds -= curvalue;
	}
	return 0;
}

// ��ȡ����
int _fangshi_palace_getaward( City *pCity, int type, int *out_awardkind, int *out_awardnum, int out_count )
{
	if ( type < 0 || type >= g_fangshi_palace_maxnum )
		return -1;
	int count = 0;
	int awardkind[32] = { 0 };
	int awardnum[32] = { 0 };
	int weight[32] = { 0 };
	int totalweight = 0;
	int nowtime = (int)time( NULL );
	for ( int index = 0; index < g_fangshi_palace[type].maxnum; index++ )
	{
		FangshiPalaceConfig *config = &g_fangshi_palace[type].config[index];
		if ( type == 0 )
		{
			int herokind = config->cond_herokind;
			if ( herokind <= 0 || herokind >= g_nation_hero_maxcount )
				continue;
			if ( g_nation_hero[herokind].createtime <= 0 )
				continue;
			if ( (nowtime - g_nation_hero[herokind].createtime) < global.fangshi_nationhero_time )
				continue;
		}
		else if ( type == 1 )
		{
			if ( config->cond_herokind > 0 )
			{
				Hero *pHero = hero_getptr( pCity->actor_index, config->cond_herokind );
				if ( !pHero )
					continue;
			}
		}

		if ( config->awardkind > AWARDKIND_GIRLSOULBASE )
		{ // ��Ƭ��û������������������ͻ��������
			if ( config->cond_girlkind > 0 )
			{
				if ( config->cond_girlkind >= ACTOR_GIRL_MAX )
					continue;
				Girl *pGirl = girl_getptr( pCity->index, config->cond_girlkind );
				if ( !pGirl )
					continue;
				if ( pGirl->color == 0 )
					continue;
				if ( pGirl->color >= ITEM_COLOR_LEVEL_PURPLE )
					continue;
			}
		}
		else
		{ // ���������ˣ�����
			char girlkind = config->awardkind - AWARDKIND_GIRLBASE;
			if ( girlkind <= 0 || girlkind >= ACTOR_GIRL_MAX )
				continue;
			Girl *pGirl = girl_getptr( pCity->index, girlkind );
			if ( !pGirl )
				continue;
			if ( pGirl->color > 0 )
				continue;
		}
		awardkind[count] = config->awardkind;
		awardnum[count] = config->awardnum;
		weight[count] = config->weight;
		totalweight += config->weight;
		count += 1;
		if ( count >= 32 )
		{
			break;
		}
	}

	for ( int tmpi = 0; tmpi < out_count; tmpi++ )
	{
		_fangshi_palace_random( awardkind, awardnum, weight, count, &totalweight, &out_awardkind[tmpi], &out_awardnum[tmpi] );
	}
	return 0;
}

// ���лʹ���Ժ���
int fangshi_palace_update( int actor_index )
{
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;

	// ����
	int nh_awardkind[2] = { 0 };
	int nh_awardnum[2] = { 0 };
	_fangshi_palace_getaward( pCity, 0, nh_awardkind, nh_awardnum, 1 );

	// ��
	int god_awardkind[2] = { 0 };
	int god_awardnum[2] = { 0 };
	_fangshi_palace_getaward( pCity, 1, god_awardkind, god_awardnum, 1 );

	int main_awardkind[2] = { 0 };
	int main_awardnum[2] = { 0 };
	if ( nh_awardkind[0] <= 0 && god_awardkind[0] <= 0 )
	{
		_fangshi_palace_getaward( pCity, 2, main_awardkind, main_awardnum, 2 );
	}
	else if ( god_awardkind[0] <= 0 )
	{
		_fangshi_palace_getaward( pCity, 2, main_awardkind, main_awardnum, 1 );
		main_awardkind[1] = nh_awardkind[0];
		main_awardnum[1] = nh_awardnum[0];
	}
	else if ( nh_awardkind[0] <= 0 )
	{
		_fangshi_palace_getaward( pCity, 2, main_awardkind, main_awardnum, 1 );
		main_awardkind[1] = god_awardkind[0];
		main_awardnum[1] = god_awardnum[0];
	}
	else
	{
		main_awardkind[0] = nh_awardkind[0];
		main_awardnum[0] = nh_awardnum[0];
		main_awardkind[1] = god_awardkind[0];
		main_awardnum[1] = god_awardnum[0];
	}

	// ��Ҫ����
	int other_awardkind[3] = { 0 };
	int other_awardnum[3] = { 0 };
	_fangshi_palace_getaward( pCity, 3, other_awardkind, other_awardnum, 3 );

	for ( int tmpi = 0; tmpi < 2; tmpi++ )
	{
		g_actors[actor_index].fs_weekkind[tmpi] = main_awardkind[tmpi];
		g_actors[actor_index].fs_weeknum[tmpi] = main_awardnum[tmpi];
	}
	for ( int tmpi = 0; tmpi < 3; tmpi++ )
	{
		g_actors[actor_index].fs_weekkind[tmpi + 2] = other_awardkind[tmpi];
		g_actors[actor_index].fs_weeknum[tmpi + 2] = other_awardnum[tmpi];
	}
	return 0;
}

// ���лʹ���Ժ����
int fangshi_palace_sendinfo( int actor_index )
{
	ACTOR_CHECK_INDEX( actor_index );
	int fweek = system_getfweek();
	fangshi_palace_update( actor_index );
	/*if ( g_actors[actor_index].fs_fweek != fweek )
	{
		fangshi_palace_update( actor_index );
		g_actors[actor_index].fs_fweek = fweek;
	}*/
	SLK_NetS_FsPalace pValue = { 0 };
	for ( int tmpi = 0; tmpi < 5; tmpi++ )
	{
		pValue.m_list[pValue.m_count].m_kind = g_actors[actor_index].fs_weekkind[tmpi];
		pValue.m_list[pValue.m_count].m_num = g_actors[actor_index].fs_weeknum[tmpi];
		pValue.m_count += 1;
	}
	netsend_fspalace_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}