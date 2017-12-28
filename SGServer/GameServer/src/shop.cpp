#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "db.h"
#include "city.h"
#include "city_attr.h"
#include "actor.h"
#include "actor_times.h"
#include "global.h"
#include "actor_send.h"
#include "server_netsend_auto.h"
#include "vip.h"
#include "item.h"
#include "shop.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;

extern Actor *g_actors;
extern int g_maxactornum;

extern City *g_city;
extern int g_city_maxcount;

extern VipInfo *g_vipinfo;
extern int g_vipinfo_maxnum;

extern Shop *g_shop;
extern int g_shop_maxnum;

int shop_list( int actor_index, int type )
{
	ACTOR_CHECK_INDEX( actor_index );
	if ( type <= 0 || type >= g_shop_maxnum )
		return -1;
	SLK_NetS_ShopList pValue = { 0 };
	pValue.m_type = type;
	for ( int tmpi = 0; tmpi < g_shop[type].maxnum; tmpi++ )
	{
		if ( g_shop[type].config[tmpi].awardkind <= 0 )
			continue;
		pValue.m_list[pValue.m_count].m_offset = g_shop[type].config[tmpi].offset;
		pValue.m_list[pValue.m_count].m_awardkind = g_shop[type].config[tmpi].awardkind;
		pValue.m_list[pValue.m_count].m_awardnum = g_shop[type].config[tmpi].awardnum;
		pValue.m_list[pValue.m_count].m_token = g_shop[type].config[tmpi].token;
		pValue.m_list[pValue.m_count].m_sale = g_shop[type].config[tmpi].sale;
		pValue.m_count += 1;
		if ( pValue.m_count >= 64 )
		{
			netsend_shoplist_S( actor_index, SENDTYPE_ACTOR, &pValue );
			pValue.m_count = 0;
		}
		
	}
	if ( pValue.m_count > 0 )
	{
		netsend_shoplist_S( actor_index, SENDTYPE_ACTOR, &pValue );
	}
	return 0;
}

int shop_buy( int actor_index, int type, int offset, int awardkind )
{
	ACTOR_CHECK_INDEX( actor_index );
	if ( type <= 0 || type >= g_shop_maxnum )
		return -1;
	if ( offset < 0 || offset >= g_shop[type].maxnum )
		return -1;
	if ( g_shop[type].config[offset].awardkind != awardkind )
		return -1;
	
	if ( actor_change_token( actor_index, -g_shop[type].config[offset].token, PATH_SHOP, 0 ) < 0 )
		return -1;
	award_getaward( actor_index, g_shop[type].config[offset].awardkind, g_shop[type].config[offset].awardnum, -1, PATH_SHOP, NULL );
	return 0;
}

