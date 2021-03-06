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
#include "system.h"
#include "actor.h"
#include "server_netsend_auto.h"
#include "actor_send.h"
#include "map.h"
#include "map_zone.h"
#include "global.h"
#include "mapunit.h"
#include "script_auto.h"
#include "city.h"
#include "world_quest.h"
#include "quest.h"

extern Global global;
extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;

extern Actor *g_actors;
extern int g_maxactornum;

extern MapZoneInfo *g_zoneinfo;
extern int g_zoneinfo_maxnum;

extern MapTownInfo *g_towninfo;
extern int g_towninfo_maxnum;

Map g_map;
int g_nUnitQueueNumLimit;		// 单个队列的极限，超过后不再分配
int *g_pTmpEnterArmy;
int *g_pTmpLeaveArmy;

//-----------------------------------------------------------------------------
// map_init
// 函数说明: 世界地图初始化
//-----------------------------------------------------------------------------
int map_init()
{
	g_nUnitQueueNumLimit = 200;

	g_pTmpEnterArmy = (int *)malloc( sizeof(int)*g_nUnitQueueNumLimit );
	g_pTmpLeaveArmy = (int *)malloc( sizeof(int)*g_nUnitQueueNumLimit );

	g_map.m_nMaxWidth = MAP_W;
	g_map.m_nMaxHeight = MAP_H;

	// 区域数据
	g_map.m_nAreaXNum = (g_map.m_nMaxWidth - 1) / AREA_WIDTH + 1;
	g_map.m_nAreaYNum = (g_map.m_nMaxHeight - 1) / AREA_HEIGHT + 1;
	g_map.m_nAreaMaxCount = g_map.m_nAreaXNum*g_map.m_nAreaYNum;
	g_map.m_aArea = (Area*)malloc( sizeof(Area)*(g_map.m_nAreaMaxCount) );
	memset( g_map.m_aArea, 0, sizeof(Area)*(g_map.m_nAreaMaxCount) );
	for ( int tmpi = 0; tmpi < g_map.m_nAreaMaxCount; tmpi++ )
	{
		g_map.m_aArea[tmpi].unit_head = -1;
		g_map.m_aArea[tmpi].unit_tail = -1;
		area_initqueue( &g_map.m_aArea[tmpi] );
	}


	// 坐标格子数据
	g_map.m_aTileData = (Tile **)malloc( sizeof( Tile * )* g_map.m_nMaxWidth );
	for ( int tmpi = 0; tmpi < g_map.m_nMaxWidth; tmpi++ )
	{
		g_map.m_aTileData[tmpi] = (Tile *)malloc( sizeof( Tile )* g_map.m_nMaxHeight );
		memset( g_map.m_aTileData[tmpi], 0, sizeof( Tile )*(g_map.m_nMaxHeight) );
	}
	
	for ( int tmpi = 0; tmpi < g_map.m_nMaxWidth; tmpi++ )
	{
		for ( int tmpj = 0; tmpj < g_map.m_nMaxHeight; tmpj++ )
		{
			g_map.m_aTileData[tmpi][tmpj].nation = -1;
			g_map.m_aTileData[tmpi][tmpj].townid = 0;
			g_map.m_aTileData[tmpi][tmpj].unit_type = 0;
			g_map.m_aTileData[tmpi][tmpj].unit_index = -1;
		}
	}

	// 世界地图脚本
	sc_OnWorldMapInit( g_map.m_nMaxWidth, g_map.m_nMaxHeight );
	return 0; 
}

// 地图帧逻辑
void map_logic()
{
	for ( int tmpi = 0; tmpi < g_map.m_nAreaXNum*g_map.m_nAreaYNum; tmpi++ )
	{
		area_logic( tmpi );
	}
}

// 世界地图配置信息
void map_sendinfo( int actor_index, short tposx, short tposy )
{
	SLK_NetS_WorldMapInfo info = { 0 };
	info.m_area_width = AREA_WIDTH;
	info.m_area_height = AREA_HEIGHT;
	info.m_map_area_xnum = g_map.m_nAreaXNum;
	info.m_map_area_ynum = g_map.m_nAreaYNum;
	info.m_target_posx = tposx;
	info.m_target_posy = tposy;
	City *pCity = city_getptr( actor_index );
	if ( pCity )
	{
		info.m_citystate = pCity->state;
		info.m_my_city_unit_index = pCity->unit_index;
		info.m_my_city_posx = pCity->posx;
		info.m_my_city_posy = pCity->posy;
	}
	netsend_worldmapinfo_S( actor_index, SENDTYPE_ACTOR, &info );
}

// 区域信息
void map_areaenter( int actor_index, int areaindex, short posx, short posy, char areaupdate )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return;
	if ( areaindex >= g_map.m_nAreaMaxCount )
		return;
	if ( g_actors[actor_index].view_areaindex != areaindex )
	{
		map_zone_change( actor_index, posx, posy, areaupdate );
		if ( areaupdate == 1 )
		{
			view_area_change( actor_index, areaindex );
			if ( areaindex < 0 )
				g_actors[actor_index].view_areaindex = -1;
			else
				g_actors[actor_index].view_areaindex = areaindex;
		}
	}
}

// 获取占地格子
inline int map_getobject_grid( int type, int index )
{
	int grid = 1;
	switch ( type )
	{
	case MAPUNIT_TYPE_CITY:	// 玩家城池
		grid = 1;
		break;
	case MAPUNIT_TYPE_TOWN://  城镇
	{
		if ( index <= 0 || index >= g_towninfo_maxnum )
			return 1;
		grid = g_towninfo[index].grid;
	}
		break;
	case MAPUNIT_TYPE_ENEMY:// 流寇
		grid = 1;
		break;
	case MAPUNIT_TYPE_RES: // 资源
		grid = 1;
		break;
	case MAPUNIT_TYPE_EVENT: // 事件
		grid = 1;
		break;
	case MAPUNIT_TYPE_NATIONHERO: // 国家名将
		grid = 1;
		break;
	default:
		return 1;
	}
	return grid;
}

// 添加对象
int map_addobject( int type, int index, short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
	{
		return -1;
	}
	int grid = map_getobject_grid( type, index );
	switch ( grid )
	{
	// 占3*3格子
	case 3:
		if ( posx <= 0 || posy <= 0 || posx >= g_map.m_nMaxWidth-1 || posy >= g_map.m_nMaxHeight-1 )
		{
			return -1;
		}
		g_map.m_aTileData[posx][posy].unit_type = type;
		g_map.m_aTileData[posx][posy].unit_index = index;
		g_map.m_aTileData[posx - 1][posy].unit_type = type;
		g_map.m_aTileData[posx - 1][posy].unit_index = index;
		g_map.m_aTileData[posx - 1][posy - 1].unit_type = type;
		g_map.m_aTileData[posx - 1][posy - 1].unit_index = index;
		g_map.m_aTileData[posx][posy - 1].unit_type = type;
		g_map.m_aTileData[posx][posy - 1].unit_index = index;
		g_map.m_aTileData[posx + 1][posy - 1].unit_type = type;
		g_map.m_aTileData[posx + 1][posy - 1].unit_index = index;
		g_map.m_aTileData[posx + 1][posy].unit_type = type;
		g_map.m_aTileData[posx + 1][posy].unit_index = index;
		g_map.m_aTileData[posx + 1][posy + 1].unit_type = type;
		g_map.m_aTileData[posx + 1][posy + 1].unit_index = index;
		g_map.m_aTileData[posx][posy + 1].unit_type = type;
		g_map.m_aTileData[posx][posy + 1].unit_index = index;
		g_map.m_aTileData[posx - 1][posy + 1].unit_type = type;
		g_map.m_aTileData[posx - 1][posy + 1].unit_index = index;
		break;
	// 占2*2个格子
	case 2:
		if ( posy <= 0 || posx >= g_map.m_nMaxWidth - 1 )
		{
			return -1;
		}
		if ( g_map.m_aTileData[posx][posy].unit_type		> 0 ||
			g_map.m_aTileData[posx][posy - 1].unit_type		> 0 ||
			g_map.m_aTileData[posx + 1][posy - 1].unit_type	> 0 ||
			g_map.m_aTileData[posx + 1][posy].unit_type		> 0 )
		{
			return -1;
		}
		g_map.m_aTileData[posx][posy].unit_type = type;
		g_map.m_aTileData[posx][posy].unit_index = index;
		g_map.m_aTileData[posx][posy - 1].unit_type = type;
		g_map.m_aTileData[posx][posy - 1].unit_index = index;
		g_map.m_aTileData[posx + 1][posy - 1].unit_type = type;
		g_map.m_aTileData[posx + 1][posy - 1].unit_index = index;
		g_map.m_aTileData[posx + 1][posy].unit_type = type;
		g_map.m_aTileData[posx + 1][posy].unit_index = index;
		break;

	// 占1*1个格子
	case 1:
		if ( g_map.m_aTileData[posx][posy].unit_type > 0 )
		{
			return -1;
		}
		g_map.m_aTileData[posx][posy].unit_type = type;
		g_map.m_aTileData[posx][posy].unit_index = index;
		break;
	default:
		break;
	}
	return 0;
}

// 移除对象
int map_delobject( int type, int index, short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
	{
		return -1;
	}
	int grid = map_getobject_grid( type, index );
	switch ( grid )
	{
		// 占3*3格子
	case 3:
		if ( posx <= 0 || posy <= 0 || posx >= g_map.m_nMaxWidth - 1 || posy >= g_map.m_nMaxHeight - 1 )
		{
			return -1;
		}
		g_map.m_aTileData[posx][posy].unit_type = 0;
		g_map.m_aTileData[posx][posy].unit_index = -1;
		g_map.m_aTileData[posx - 1][posy].unit_type = 0;
		g_map.m_aTileData[posx - 1][posy].unit_index = -1;
		g_map.m_aTileData[posx - 1][posy - 1].unit_type = 0;
		g_map.m_aTileData[posx - 1][posy - 1].unit_index = -1;
		g_map.m_aTileData[posx][posy - 1].unit_type = 0;
		g_map.m_aTileData[posx][posy - 1].unit_index = -1;
		g_map.m_aTileData[posx + 1][posy - 1].unit_type = 0;
		g_map.m_aTileData[posx + 1][posy - 1].unit_index = -1;
		g_map.m_aTileData[posx + 1][posy].unit_type = 0;
		g_map.m_aTileData[posx + 1][posy].unit_index = -1;
		g_map.m_aTileData[posx + 1][posy + 1].unit_type = 0;
		g_map.m_aTileData[posx + 1][posy + 1].unit_index = -1;
		g_map.m_aTileData[posx][posy + 1].unit_type = 0;
		g_map.m_aTileData[posx][posy + 1].unit_index = -1;
		g_map.m_aTileData[posx - 1][posy + 1].unit_type = 0;
		g_map.m_aTileData[posx - 1][posy + 1].unit_index = -1;
		break;

	// 占2*2个格子
	case 2: 
		if ( posy <= 0 || posx >= g_map.m_nMaxWidth - 1 )
		{
			return -1;
		}
		g_map.m_aTileData[posx][posy].unit_type = 0;
		g_map.m_aTileData[posx][posy].unit_index = -1;
		g_map.m_aTileData[posx][posy - 1].unit_type = 0;
		g_map.m_aTileData[posx][posy - 1].unit_index = -1;
		g_map.m_aTileData[posx + 1][posy - 1].unit_type = 0;
		g_map.m_aTileData[posx + 1][posy - 1].unit_index = -1;
		g_map.m_aTileData[posx + 1][posy].unit_type = 0;
		g_map.m_aTileData[posx + 1][posy].unit_index = -1;
		break;

	// 占1*1个格子
	case 1:
		g_map.m_aTileData[posx][posy].unit_type = 0;
		g_map.m_aTileData[posx][posy].unit_index = -1;
		break;
	default:
		break;
	}
	return 0;
}

// 设置格子所属国家
int map_tile_setnation( short posx, short posy, int range, short townid, char nation )
{
	if ( range == 3 )
	{
		for ( int tmpi = -1; tmpi <= 1; tmpi++ )
		{
			for ( int tmpj = -1; tmpj <= 1; tmpj++ )
			{
				short x = posx + tmpi;
				short y = posy + tmpj;
				if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
					continue;
				g_map.m_aTileData[x][y].nation = nation;
				g_map.m_aTileData[x][y].townid = townid;
			}
		}
	}
	else if ( range == 4 )
	{
		for ( int tmpi = -1; tmpi <= 2; tmpi++ )
		{
			for ( int tmpj = -2; tmpj <= 1; tmpj++ )
			{
				short x = posx + tmpi;
				short y = posy + tmpj;
				if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
					continue;
				g_map.m_aTileData[x][y].nation = nation;
				g_map.m_aTileData[x][y].townid = townid;
			}
		}
	}
	else if ( range == 20 )
	{
		for ( int tmpi = -10; tmpi <= 9; tmpi++ )
		{
			for ( int tmpj = -10; tmpj <= 9; tmpj++ )
			{
				short x = posx + tmpi;
				short y = posy + tmpj;
				if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
					continue;
				g_map.m_aTileData[x][y].nation = nation;
				g_map.m_aTileData[x][y].townid = townid;
			}
		}
	}
	return 0;
}
char map_tile_getnation( short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
		return -1;
	return g_map.m_aTileData[posx][posy].nation;
}

short map_tile_gettownid( short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
		return -1;
	return g_map.m_aTileData[posx][posy].townid;
}

// 判定这个地点是否能迁城
int map_canmove( short posX, short posY )
{
	if( posX < 0 || posY < 0 || posX >= g_map.m_nMaxWidth || posY >= g_map.m_nMaxWidth )
	{
		return 0;
	}

	// 检查下
	if ( g_map.m_aTileData[posX][posY].unit_type == 0 )
	{
		return 1;
	}

	return 0;
}

// 获得一个离指定地点最近的可迁城空白点 螺旋查找
int map_getcanmovenearest( short *pPosx, short *pPosy )
{
	if( *pPosx < 0 || *pPosy < 0 || *pPosx >= g_map.m_nMaxWidth || *pPosy >= g_map.m_nMaxWidth )
	{
		return -1;
	}

	/* 步长和起点滤掉第一圈。从左上开始*/
	// 步长
	short stepX = 3;
	short stepY = 4;

	// 步长增长方向
	short stepXForward = 1;
	short stepYForward = -1;

	// 起点
	short posX = *pPosx - 1;
	short posY = *pPosy + 2;
	// 检查下起点
	if ( map_canmove( posX, posY ) )
	{
		*pPosx = posX;
		*pPosy = posY;
		return 0;
	}

	// 保险，最多查找1000个坐标
	short count = 0;

	while( count < 1000 )
	{
		// 先走X坐标
		for( int i = 0; i < stepX; i++ )
		{
			posX += stepXForward;
			if ( map_canmove( posX, posY ) )
			{
				*pPosx = posX;
				*pPosy = posY;
				return 0;
			}
		}
		stepXForward *= -1;

		// 再走Y坐标
		for( int i = 0; i < stepY; i++ )
		{
			posY += stepYForward;
			if ( map_canmove( posX, posY ) )
			{
				*pPosx = posX;
				*pPosy = posY;
				return 0;
			}
		}
		stepYForward *= -1;

		// 循环一次增加一次步长
		stepX++;
		stepY++;

		// 防止死循环
		count += 1;
	}

	return -1;
}

// 随机一个空白点
int map_getrandpos( int grid, short *pPosx, short *pPosy )
{
	*pPosx = rand() % (g_map.m_nMaxWidth - MAP_SIZEOFFSET) + 1;
	*pPosy = rand() % (g_map.m_nMaxHeight - MAP_SIZEOFFSET) + 1;

	switch ( grid )
	{
		// 占3*3格子
	case 3:
		if ( g_map.m_aTileData[*pPosx][*pPosy].unit_type == 0 &&
			g_map.m_aTileData[*pPosx - 1][*pPosy].unit_type == 0 &&
			g_map.m_aTileData[*pPosx - 1][*pPosy - 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx][*pPosy - 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx + 1][*pPosy - 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx + 1][*pPosy].unit_type == 0 &&
			g_map.m_aTileData[*pPosx + 1][*pPosy + 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx][*pPosy + 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx - 1][*pPosy + 1].unit_type == 0 )
		{
			return 0;
		}
		else
		{
			while ( g_map.m_aTileData[*pPosx][*pPosy].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx - 1][*pPosy].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx - 1][*pPosy - 1].unit_type	> 0 ||
				g_map.m_aTileData[*pPosx][*pPosy - 1].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx + 1][*pPosy - 1].unit_type	> 0 ||
				g_map.m_aTileData[*pPosx + 1][*pPosy].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx + 1][*pPosy + 1].unit_type	> 0 ||
				g_map.m_aTileData[*pPosx][*pPosy + 1].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx - 1][*pPosy + 1].unit_type	> 0 )
			{
				*pPosx = rand() % (g_map.m_nMaxWidth - MAP_SIZEOFFSET) + 1;
				*pPosy = rand() % (g_map.m_nMaxHeight - MAP_SIZEOFFSET) + 1;
			}
			return 0;
		}
	// 占2*2个格子
	case 2:
		if ( g_map.m_aTileData[*pPosx][*pPosy].unit_type == 0 &&
			g_map.m_aTileData[*pPosx][*pPosy - 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx + 1][*pPosy - 1].unit_type == 0 &&
			g_map.m_aTileData[*pPosx + 1][*pPosy].unit_type == 0 )
		{
			return 0;
		}
		else
		{
			while ( g_map.m_aTileData[*pPosx][*pPosy].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx][*pPosy - 1].unit_type		> 0 ||
				g_map.m_aTileData[*pPosx + 1][*pPosy - 1].unit_type	> 0 ||
				g_map.m_aTileData[*pPosx + 1][*pPosy].unit_type		> 0 )
			{
				*pPosx = rand() % (g_map.m_nMaxWidth - MAP_SIZEOFFSET) + 1;
				*pPosy = rand() % (g_map.m_nMaxHeight - MAP_SIZEOFFSET) + 1;
			}
			return 0;
		}
		break;

	// 占1*1个格子
	case 1:
		if ( g_map.m_aTileData[*pPosx][*pPosy].unit_type == 0 )
		{
			return 0;
		}
		else
		{
			while ( g_map.m_aTileData[*pPosx][*pPosy].unit_type > 0 )
			{
				*pPosx = rand() % (g_map.m_nMaxWidth - MAP_SIZEOFFSET) + 1;
				*pPosy = rand() % (g_map.m_nMaxHeight - MAP_SIZEOFFSET) + 1;
			}
			return 0;
		}
		break;
	default:
		break;
	}

	return -1;
}

// 根据指定点的范围获取一个可用坐标点1*1的
int map_getrandpos_withrange( short posx, short posy, int range, short *pPosx, short *pPosy )
{
	short findlistx[256] = { 0 };
	short findlisty[256] = { 0 };
	short offset = 0;
	int zoneid = map_zone_getid( posx, posy );
	for ( int tmpi = -range; tmpi <= range; tmpi++ )
	{
		for ( int tmpj = -range; tmpj <= range; tmpj++ )
		{
			short x = posx + tmpi;
			short y = posy + tmpj;
			if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
				continue;
			if ( g_map.m_aTileData[x][y].unit_type > 0 )
				continue;
			if ( map_zone_getid( x, y ) != zoneid )
				continue;
			//if ( map_addobject( type, x, y ) < 0 )
			//	continue;
			// 找到所有的空余点
			findlistx[offset] = x;
			findlisty[offset] = y;
			offset += 1;
			if ( offset >= 256 )
				break;
		}
		if ( offset >= 256 )
			break;
	}

	if ( offset > 0 )
	{
		int index = rand() % offset;
		*pPosx = findlistx[index];
		*pPosy = findlisty[index];
	}
	else
	{
		*pPosx = -1;
		*pPosy = -1;
	}
	return 0;
}

// 随机玩家城池位置
int map_getrandcitypos( short *pPosx, short *pPosy )
{
	short zoneidlist[8] = { 1, 5, 21, 25, 3, 11, 15, 23 };
	int openday = system_getopentime() / 86400;

	// 先随机一个新手区域，然后在这个区域内随机空位，当随机1万次依然没有位置，那么从这个区域一个一个找，不随机了，还是没找到，那么换下一个区域
	int step = 0;
	while ( true )
	{
		short zoneid = 0;
		if ( openday <= 14 )
		{ // 开服两周内
			zoneid = zoneidlist[random( 0, 3 )];
		}
		else
		{ // 开服两周后
			zoneid = zoneidlist[random( 4, 7 )];
		}
		if ( zoneid >= g_zoneinfo_maxnum )
		{
			continue;
		}

		short findlistx[4096] = { 0 };
		short findlisty[4096] = { 0 };
		short offset = 0;
		for ( int tmpi = g_zoneinfo[zoneid].top_left_posx; tmpi <= g_zoneinfo[zoneid].bottom_right_posx; tmpi++ )
		{
			for ( int tmpj = g_zoneinfo[zoneid].top_left_posy; tmpj <= g_zoneinfo[zoneid].bottom_right_posy; tmpj++ )
			{
				short x = tmpi;
				short y = tmpj;
				if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
					continue;
				if ( g_map.m_aTileData[x][y].unit_type > 0 )
					continue;
				// 找到所有的空余点
				findlistx[offset] = x;
				findlisty[offset] = y;
				offset += 1;
				if ( offset >= 4096 )
					break;
			}
			if ( offset >= 4096 )
				break;
		}

		if ( offset > 0 )
		{
			int index = rand() % offset;
			*pPosx = findlistx[index];
			*pPosy = findlisty[index];
		}
		else
		{
			*pPosx = -1;
			*pPosy = -1;
		}
		if ( *pPosx >= 0 && *pPosy >= 0 )
		{
			break;
		}
		step += 1;
		if ( step >= 8 )
		{// 保险
			*pPosx = 0;
			*pPosy = 0;
			break;
		}
	}
	
	return 0;
}

// 随机坐标
int map_getrandpos_withtype( int type, short *pPosx, short *pPosy )
{
	static short s_zoneidlist0[8] = { 1, 3, 5, 11, 15, 21, 23, 25 };
	static short s_zoneidlist1[12] = { 1, 3, 5, 11, 15, 21, 23, 25, 7, 9, 17, 19 };
	static short s_zoneidlist2[13] = { 1, 3, 5, 11, 15, 21, 23, 25, 7, 9, 17, 19, 13 };
	short zoneid = 0;
	if ( type == 0 )
	{
		zoneid = s_zoneidlist0[random( 0, 7 )];
	}
	else if ( type == 1 )
	{
		zoneid = s_zoneidlist1[random( 0, 11 )];
	}
	else if ( type == 2 )
	{
		zoneid = s_zoneidlist1[random( 0, 12 )];
	}
	if ( zoneid == 0 )
		return -1;
	map_zone_randpos( zoneid, pPosx, pPosy, 4096 );
	return 0;
}

int map_goto_withpos( int actor_index, char op, short posx, short posy )
{
	if ( posx <= 0 || posy <= 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
		return -1;
	SLK_NetS_GotoAsyn pValue = { 0 };
	pValue.m_op = op;
	pValue.m_posx = posx;
	pValue.m_posy = posy;
	pValue.m_type = g_map.m_aTileData[posx][posy].unit_type;
	pValue.m_unit_index = g_map.m_aTileData[posx][posy].unit_index;
	netsend_gotoasyn_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}

bool ptInLine( Pos point, Pos lineStartPoint, Pos lineEndPoint, double fTolerance )
{
	double L, R, S;
	bool bResult = false;

	L = sqrt( (double)((lineEndPoint.x - lineStartPoint.x)*(lineEndPoint.x - lineStartPoint.x) + (lineEndPoint.y - lineStartPoint.y)*(lineEndPoint.y - lineStartPoint.y)) );
	if ( L != 0 )
	{
		R = ((lineStartPoint.y - point.y)*(lineStartPoint.y - lineEndPoint.y) - (lineStartPoint.x - point.x)*(lineEndPoint.x - lineStartPoint.x)) / (L*L);
		S = ((lineStartPoint.y - point.y)*(lineEndPoint.x - lineStartPoint.x) - (lineStartPoint.x - point.x)*(lineEndPoint.y - lineStartPoint.y)) / (L*L);
		if ( R > 0 && R < 1 )
		{
			if ( abs( (int)(S*L) ) <= fTolerance )
				bResult = true;
		}
	}

	return bResult;
}

// 距离
int map_distance( short fposx, short fposy, short tposx, short tposy )
{
	return (int)sqrt( (float)((fposx - tposx)*(fposx - tposx)) + (float)((fposy - tposy)*(fposy - tposy)) );
}

// dump地图数据
void map_tile_dump()
{
	FILE *fp = fopen( "./map_tile.txt", "wb" );
	if ( !fp )
		return;
	for ( short posy = 0; posy < g_map.m_nMaxHeight; posy++ )
	{
		for ( short posx = 0; posx < g_map.m_nMaxWidth; posx++ )
		{
			fprintf( fp, "%d\t", g_map.m_aTileData[posx][posy].unit_type );
		}
		fprintf( fp, "\n" );
	}
	fclose( fp );
}
