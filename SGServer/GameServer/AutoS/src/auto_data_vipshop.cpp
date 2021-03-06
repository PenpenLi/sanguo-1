extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include "db.h"
#include "auto_data_vipshop.h"
extern MYSQL *myData;
extern lua_State* servL;
VipShop *g_vipshop = NULL;
int g_vipshop_maxnum = 0;

int vipshop_init_auto()
{
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char	szSQL[2048] = {0};
	int offset = 0;

	sprintf( szSQL, "select max(`id`) from vipshop;" );
	if( mysql_query( myData, szSQL ) )
	{
		printf( "Query failed (%s)\n", mysql_error(myData) );
		write_gamelog( "%s", szSQL );
		return -1;
	}
	res = mysql_store_result( myData );
	if( ( row = mysql_fetch_row( res ) ) )
	{
		if ( row[0] )
			g_vipshop_maxnum = atoi( row[0] ) + 1;
		else
			g_vipshop_maxnum = 0;
	}
	else
	{
		mysql_free_result( res );
		return -1;
	}
	mysql_free_result( res );

	g_vipshop = (VipShop *)malloc( sizeof(VipShop)*g_vipshop_maxnum );
	memset( g_vipshop, 0, sizeof(VipShop)*g_vipshop_maxnum );

	sprintf( szSQL, "select `id`,`awardkind`,`awardnum`,`token`,`itemkind`,`actorlevel`,`viplevel`,`viplevel_max`,`vipbaglevel`,`fun`,`vip_token00`,`vip_token01`,`vip_token02`,`vip_token03`,`vip_token04`,`vip_token05`,`vip_token06`,`vip_token07`,`vip_token08`,`vip_token09`,`vip_token10`,`vip_token11`,`vip_token12`,`vip_token13`,`vip_token14`,`vip_token15`,`vip_buynum00`,`vip_buynum01`,`vip_buynum02`,`vip_buynum03`,`vip_buynum04`,`vip_buynum05`,`vip_buynum06`,`vip_buynum07`,`vip_buynum08`,`vip_buynum09`,`vip_buynum10`,`vip_buynum11`,`vip_buynum12`,`vip_buynum13`,`vip_buynum14`,`vip_buynum15` from vipshop;" );
	if( mysql_query( myData, szSQL ) )
	{
		printf( "Query failed (%s)\n", mysql_error(myData) );
		write_gamelog( "%s", szSQL );
		return -1;
	}
	res = mysql_store_result( myData );
	while( ( row = mysql_fetch_row( res ) ) )
	{
		offset = 0;
		int id = atoi( row[0] );
		if ( id < 0 || id >= g_vipshop_maxnum  )
			continue;
		g_vipshop[id].id = atoi(row[offset++]);
		g_vipshop[id].awardkind = atoi(row[offset++]);
		g_vipshop[id].awardnum = atoi(row[offset++]);
		g_vipshop[id].token = atoi(row[offset++]);
		g_vipshop[id].itemkind = atoi(row[offset++]);
		g_vipshop[id].actorlevel = atoi(row[offset++]);
		g_vipshop[id].viplevel = atoi(row[offset++]);
		g_vipshop[id].viplevel_max = atoi(row[offset++]);
		g_vipshop[id].vipbaglevel = atoi(row[offset++]);
		g_vipshop[id].fun = atoi(row[offset++]);
		g_vipshop[id].vip_token[0] = atoi(row[offset++]);
		g_vipshop[id].vip_token[1] = atoi(row[offset++]);
		g_vipshop[id].vip_token[2] = atoi(row[offset++]);
		g_vipshop[id].vip_token[3] = atoi(row[offset++]);
		g_vipshop[id].vip_token[4] = atoi(row[offset++]);
		g_vipshop[id].vip_token[5] = atoi(row[offset++]);
		g_vipshop[id].vip_token[6] = atoi(row[offset++]);
		g_vipshop[id].vip_token[7] = atoi(row[offset++]);
		g_vipshop[id].vip_token[8] = atoi(row[offset++]);
		g_vipshop[id].vip_token[9] = atoi(row[offset++]);
		g_vipshop[id].vip_token[10] = atoi(row[offset++]);
		g_vipshop[id].vip_token[11] = atoi(row[offset++]);
		g_vipshop[id].vip_token[12] = atoi(row[offset++]);
		g_vipshop[id].vip_token[13] = atoi(row[offset++]);
		g_vipshop[id].vip_token[14] = atoi(row[offset++]);
		g_vipshop[id].vip_token[15] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[0] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[1] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[2] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[3] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[4] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[5] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[6] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[7] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[8] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[9] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[10] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[11] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[12] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[13] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[14] = atoi(row[offset++]);
		g_vipshop[id].vip_buynum[15] = atoi(row[offset++]);
	}
	mysql_free_result( res );
	return 0;
}

int vipshop_reload_auto()
{
	if ( g_vipshop )
	{
		free( g_vipshop );
		g_vipshop = NULL;
	}
	g_vipshop_maxnum = 0;
	vipshop_init_auto();
	return 0;
}

