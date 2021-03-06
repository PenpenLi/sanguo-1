#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include "db.h"
#include "actor.h"
#include "auto_city_building_res.h"
extern MYSQL *myGame;
extern char g_batchsql[BATCHSQL_MAXSIZE];

int city_building_res_load_auto( int actorid, int city_index, LPCB_GETBUILDINGRES pCB_GetBuildingRes, const char *pTab )
{
	MYSQL_RES	*res;
	MYSQL_ROW	row;
	char	szSQL[8192] = {0};
	int offset = 0;
	BuildingRes *pBuildingRes;

	sprintf( szSQL, "select `actorid`,`offset`,`kind`,`level` from %s where actorid='%d'", pTab, actorid );
	if( mysql_query( myGame, szSQL ) )
	{
		printf( "Query failed (%s)\n", mysql_error(myGame) );
		write_gamelog( "%s", szSQL );
		if( mysql_ping(myGame) != 0 )
			db_reconnect_game();
		return -1;
	}
	res = mysql_store_result( myGame );

	while( ( row = mysql_fetch_row( res ) ) )
	{
		offset = 0;
		pBuildingRes = pCB_GetBuildingRes( city_index, atoi(row[1]) );
		if( pBuildingRes == NULL )
			continue;
		offset++;
		offset++;
		pBuildingRes->kind = atoi(row[offset++]);
		pBuildingRes->level = atoi(row[offset++]);
	}
	mysql_free_result( res );
	return 0;
}
int city_building_res_save_auto( int actorid, int offset, BuildingRes *pBuildingRes, const char *pTab, FILE *fp )
{
	char	szSQL[8192] = {0};
	char reconnect_flag = 0;
	if ( pBuildingRes == NULL )
		return -1;

RE_BUILDINGRES_UPDATE:
	sprintf( szSQL, "REPLACE INTO %s (`actorid`,`offset`,`kind`,`level`) Values('%d','%d','%d','%d')",pTab,actorid,offset,pBuildingRes->kind,pBuildingRes->level);
	if( fp )
	{
		fprintf( fp, "%s;\n", szSQL );
	}
	else if( mysql_query( myGame, szSQL ) )
	{
		printf( "Query failed (%s)\n", mysql_error(myGame) );
		write_gamelog( "%s", szSQL );
		if( reconnect_flag )
			return -1;
		if( mysql_ping(myGame) != 0 )
		{
			db_reconnect_game();
			reconnect_flag = 1;
			goto RE_BUILDINGRES_UPDATE;
		}
		return -1;
	}
	return 0;
}

int city_building_res_batch_save_auto( int actorid, BuildingRes *pBuildingRes, int maxcount, const char *pTab, FILE *fp )
{
	char	szSQL[8192] = {0};
	if ( pBuildingRes == NULL )
		return -1;

	int count = 0;
	memset( g_batchsql, 0, sizeof(char)*BATCHSQL_MAXSIZE );
	for ( int index = 0; index < maxcount; index++ )
	{
		if ( pBuildingRes[index].kind <= 0 )
			continue;
		if ( count == 0 )
		{
			sprintf( g_batchsql, "REPLACE INTO %s (`actorid`,`offset`,`kind`,`level`) Values('%d','%d','%d','%d')",pTab,actorid,index,pBuildingRes[index].kind,pBuildingRes[index].level);
		}
		else
		{
			sprintf( szSQL, ",('%d','%d','%d','%d')",actorid,index,pBuildingRes[index].kind,pBuildingRes[index].level);
			strcat( g_batchsql, szSQL );
		}
		count += 1;
		if ( count > 64 )
		{
			count = 0;
			db_query( fp, g_batchsql );
			memset( g_batchsql, 0, sizeof(char)*BATCHSQL_MAXSIZE );
		}
	}
	if ( count > 0 )
	{
		count = 0;
		db_query( fp, g_batchsql );
		memset( g_batchsql, 0, sizeof(char)*BATCHSQL_MAXSIZE );
	}
	return 0;
}
