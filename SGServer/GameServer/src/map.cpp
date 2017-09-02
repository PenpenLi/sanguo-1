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
#include "global.h"
#include "mapunit.h"
#include "script_auto.h"
#include "city.h"

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
int g_nUnitQueueNumLimit;		// �������еļ��ޣ��������ٷ���
int *g_pTmpEnterArmy;
int *g_pTmpLeaveArmy;

short g_last_cityposx = 0;
short g_last_cityposy = 0;

//-----------------------------------------------------------------------------
// map_init
// ����˵��: �����ͼ��ʼ��
//-----------------------------------------------------------------------------
int map_init()
{
	g_nUnitQueueNumLimit = 200;

	g_pTmpEnterArmy = (int *)malloc( sizeof(int)*g_nUnitQueueNumLimit );
	g_pTmpLeaveArmy = (int *)malloc( sizeof(int)*g_nUnitQueueNumLimit );

	g_map.m_nMaxWidth = MAP_W;
	g_map.m_nMaxHeight = MAP_H;

	// ��������
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

	// �����������
	g_map.m_aTileData = (Tile **)malloc( sizeof( Tile * )* g_map.m_nMaxWidth );
	for ( int tmpi = 0; tmpi < g_map.m_nMaxWidth; tmpi++ )
	{
		g_map.m_aTileData[tmpi] = (Tile *)malloc( sizeof( Tile )* g_map.m_nMaxHeight );
		memset( g_map.m_aTileData[tmpi], 0, sizeof( Tile )*(g_map.m_nMaxHeight) );
	}
	
	// �����ͼ�ű�
	sc_OnWorldMapInit( g_map.m_nMaxWidth, g_map.m_nMaxHeight );
	return 0; 
}

// ��ͼ֡�߼�
void map_logic()
{
	for ( int tmpi = 0; tmpi < g_map.m_nAreaXNum*g_map.m_nAreaYNum; tmpi++ )
	{
		area_logic( tmpi );
	}
}

// �����ͼ������Ϣ
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

// �����Ƿ���ָ��������
char map_zone_inrange( int zoneid, short posx, short posy )
{
	if ( zoneid <= 0 || zoneid >= g_zoneinfo_maxnum )
		return 0;
	if ( posx >= g_zoneinfo[zoneid].top_left_posx && posx <= g_zoneinfo[zoneid].bottom_right_posx &&
		 posy >= g_zoneinfo[zoneid].top_left_posy && posx <= g_zoneinfo[zoneid].bottom_right_posy )
	{
		return 1;
	}
	return 0;
}

// ��ȡ����id
char map_zone_getid( int posx, int posy )
{
	int zonex, zoney;
	if ( posx >= g_map.m_nMaxWidth )
		posx = g_map.m_nMaxWidth - 1;
	if ( posy >= g_map.m_nMaxHeight )
		posy = g_map.m_nMaxHeight - 1;
	zonex = (posx) / 100;
	zoney = (posy) / 100;
	return zoney*(5) + zonex + 1;
}

// ������Ԫ�б�
int map_zone_unitlist( int actor_index, int zoneid )
{
	if ( zoneid <= 0 || zoneid >= g_zoneinfo_maxnum )
		return -1;
	City *pCity = NULL;
	SLK_NetS_MapZoneUnitList pValue = {0};
	for ( int tmpi = g_zoneinfo[zoneid].top_left_posx; tmpi <= g_zoneinfo[zoneid].bottom_right_posx; tmpi++ )
	{
		for ( int tmpj = g_zoneinfo[zoneid].top_left_posy; tmpj <= g_zoneinfo[zoneid].bottom_right_posy; tmpj++ )
		{
			short x = tmpi;
			short y = tmpj;
			if ( x <= 0 || y <= 0 || x >= g_map.m_nMaxWidth || y >= g_map.m_nMaxHeight )
				continue;
			if ( g_map.m_aTileData[x][y].unit_type == MAPUNIT_TYPE_CITY )
			{
				pCity = city_indexptr( g_map.m_aTileData[x][y].unit_index );
				if ( pCity )
				{
					pValue.m_list[pValue.m_count].m_posx = pCity->posx;
					pValue.m_list[pValue.m_count].m_posy = pCity->posy;
					pValue.m_list[pValue.m_count].m_nation = pCity->nation;
					pValue.m_list[pValue.m_count].m_level = (char)pCity->level;
				}
				pValue.m_count += 1;
				if ( pValue.m_count >= 255 )
				{
					netsend_mapzoneunitlist_S( actor_index, SENDTYPE_ACTOR, &pValue );
					pValue.m_count = 0;
				}
			}
			
		}
	}
	if ( pValue.m_count > 0 )
	{
		netsend_mapzoneunitlist_S( actor_index, SENDTYPE_ACTOR, &pValue );
	}
	return 0;
}

//��ͼ��������
void map_zoneenter( int actor_index, short posx, short posy )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return;
	if ( posx < 0 && posy < 0 )
	{
		g_actors[actor_index].view_zoneid = 0;
		return;
	}
	char zoneid = map_zone_getid( posx, posy );
	if ( g_actors[actor_index].view_zoneid != zoneid )
	{// ֪ͨ�ͻ��˽����µĵ���
		g_actors[actor_index].view_zoneid = zoneid;
		SLK_NetS_MapZoneChange pValue = {0};
		pValue.m_zoneid = zoneid;
		if ( zoneid > 0 && zoneid < g_zoneinfo_maxnum )
		{
			pValue.m_open = (char)g_zoneinfo[zoneid].open;
		}
		netsend_mapzonechange_S( actor_index, SENDTYPE_ACTOR, &pValue );

		// ���͵�Ԫ�б�
		map_zone_unitlist( actor_index, zoneid );
	}
}

// ������Ϣ
void map_areaenter( int actor_index, int areaindex, short posx, short posy )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return;
	if ( areaindex >= g_map.m_nAreaMaxCount )
		return;
	if ( g_actors[actor_index].view_areaindex != areaindex )
	{
		map_zoneenter( actor_index, posx, posy );
		view_area_change( actor_index, areaindex );
		if ( areaindex < 0 )
			g_actors[actor_index].view_areaindex = -1;
		else
			g_actors[actor_index].view_areaindex = areaindex;
	}
}

// ��ȡռ�ظ���
int map_getobject_grid( int type, int index )
{
	int grid = 1;
	switch ( type )
	{
	case MAPUNIT_TYPE_CITY:	// ��ҳǳ�
		grid = 1;
		break;
	case MAPUNIT_TYPE_TOWN://  ����
	{
		if ( index <= 0 || index >= g_towninfo_maxnum )
			return 1;
		grid = g_towninfo[index].grid;
	}
		break;
	case MAPUNIT_TYPE_ENEMY:// ����
		grid = 1;
		break;
	case MAPUNIT_TYPE_RES: // ��Դ
		grid = 1;
		break;
	default:
		return 1;
	}
	return grid;
}

// ��Ӷ���
int map_addobject( int type, int index, short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
	{
		return -1;
	}
	int grid = map_getobject_grid( type, index );
	switch ( grid )
	{
	// ռ3*3����
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
	// ռ2*2������
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

	// ռ1*1������
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

// �Ƴ�����
int map_delobject( int type, int index, short posx, short posy )
{
	if ( posx < 0 || posy < 0 || posx >= g_map.m_nMaxWidth || posy >= g_map.m_nMaxHeight )
	{
		return -1;
	}
	int grid = map_getobject_grid( type, index );
	switch ( grid )
	{
		// ռ3*3����
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

	// ռ2*2������
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

	// ռ1*1������
	case 1:
		g_map.m_aTileData[posx][posy].unit_type = 0;
		g_map.m_aTileData[posx][posy].unit_index = -1;
		break;
	default:
		break;
	}
	return 0;
}

// �ж�����ص��Ƿ���Ǩ��
int map_canmove( short posX, short posY )
{
	if( posX < 0 || posY < 0 || posX >= g_map.m_nMaxWidth || posY >= g_map.m_nMaxWidth )
	{
		return 0;
	}

	// �����
	if ( g_map.m_aTileData[posX][posY].unit_type == 0 )
	{
		return 1;
	}

	return 0;
}

// ���һ����ָ���ص�����Ŀ�Ǩ�ǿհ׵� ��������
int map_getcanmovenearest( short *pPosx, short *pPosy )
{
	if( *pPosx < 0 || *pPosy < 0 || *pPosx >= g_map.m_nMaxWidth || *pPosy >= g_map.m_nMaxWidth )
	{
		return -1;
	}

	/* ����������˵���һȦ�������Ͽ�ʼ*/
	// ����
	short stepX = 3;
	short stepY = 4;

	// ������������
	short stepXForward = 1;
	short stepYForward = -1;

	// ���
	short posX = *pPosx - 1;
	short posY = *pPosy + 2;
	// ��������
	if ( map_canmove( posX, posY ) )
	{
		*pPosx = posX;
		*pPosy = posY;
		return 0;
	}

	// ���գ�������1000������
	short count = 0;

	while( count < 1000 )
	{
		// ����X����
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

		// ����Y����
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

		// ѭ��һ������һ�β���
		stepX++;
		stepY++;

		// ��ֹ��ѭ��
		count += 1;
	}

	return -1;
}

// ���һ���հ׵�
int map_getrandpos( int grid, short *pPosx, short *pPosy )
{
	*pPosx = rand() % (g_map.m_nMaxWidth - MAP_SIZEOFFSET) + 1;
	*pPosy = rand() % (g_map.m_nMaxHeight - MAP_SIZEOFFSET) + 1;

	switch ( grid )
	{
		// ռ3*3����
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
	// ռ2*2������
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

	// ռ1*1������
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

// ����ָ����ķ�Χ��ȡһ�����������1*1��
int map_getrandpos_withrange( short posx, short posy, int range, short *pPosx, short *pPosy )
{
	short findlistx[256] = { 0 };
	short findlisty[256] = { 0 };
	short offset = 0;
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
			//if ( map_addobject( type, x, y ) < 0 )
			//	continue;
			// �ҵ����еĿ����
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

// �����ҳǳ�λ��
int map_getrandcitypos( short *pPosx, short *pPosy )
{
	short zoneidlist[8] = { 1, 5, 21, 25, 3, 11, 15, 23 };
	int openday = system_getopentime() / 86400;

	// �����һ����������Ȼ������������������λ�������1�����Ȼû��λ�ã���ô���������һ��һ���ң�������ˣ�����û�ҵ�����ô����һ������
	int step = 0;
	while ( true )
	{
		short zoneid = 0;
		if ( openday <= 14 )
		{ // ����������
			zoneid = zoneidlist[random( 0, 3 )];
		}
		else
		{ // �������ܺ�
			zoneid = zoneidlist[random( 4, 7 )];
		}
		if ( zoneid >= g_zoneinfo_maxnum )
		{
			continue;
		}

		short findlistx[256] = { 0 };
		short findlisty[256] = { 0 };
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
				// �ҵ����еĿ����
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
		if ( *pPosx >= 0 && *pPosy >= 0 )
		{
			break;
		}
		step += 1;
		if ( step >= 8 )
		{// ����
			*pPosx = 0;
			*pPosy = 0;
			break;
		}
	}
	
	return 0;
}

// ָ���������һ��������
int map_zone_randpos( short zoneid, short *pPosx, short *pPosy )
{
	if ( zoneid <= 0 || zoneid >= g_zoneinfo_maxnum )
		return -1;
	int step = 0;

	short findlistx[256] = { 0 };
	short findlisty[256] = { 0 };
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
			// �ҵ����еĿ����
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

// dump��ͼ����
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
