#ifndef __MAP_H_
#define __MAP_H_

#include "area.h"
#define MAP_SIZEOFFSET 4

#define MAP_W	500
#define MAP_H	500

// һ���������ݽṹ
typedef struct _tile
{
	char nation;			// ������������
	char unit_type;			// �����ϵ���ʾ��������
	int unit_index;			// �����ϵ���ʾ��������
	char owner_unit_type;	// ���ӵ�����
	int owner_unit_index;	// ���ӵ�����
}Tile;


// �����ͼ
typedef struct _map
{
	int				m_nMaxWidth;	// ��ͼ�Ŀ��(���鵥λ)
	int				m_nMaxHeight;	// ��ͼ�ĸ߶�(���鵥λ)
	short			m_nAreaXNum;
	short			m_nAreaYNum;
	int				m_nAreaMaxCount;
	Area			*m_aArea;
	Tile			**m_aTileData;		// ÿ�����ӵ�����
}Map;

typedef struct _pos
{
	short x;
	short y;
}Pos;

int map_init();
void map_logic();
void map_sendinfo( int actor_index, short tposx, short tposy );
void map_sendthumbinfo( int actor_index );
void map_areaenter( int actor_index, int areaindex, short posx, short posy );

// �����Ƿ���ָ��������
char map_zone_inrange( int zoneid, short posx, short posy );

// ��ȡ����id
char map_zone_getid( short posx, short posy );

// ����ǲ�����ͬһ������
char map_zone_checksame( short posx, short posy, short tposx, short tposy );

// ��Ӷ���
int map_addobject( int type, int index, short posx, short posy );

// �Ƴ�����
int map_delobject( int type, int index, short posx, short posy );

// ��ȡռ�ظ���
int map_getobject_grid( int type, int index );

// ���һ����ָ���ص�����Ŀ�Ǩ�ǿհ׵� ��������
int map_getcanmovenearest( short *pPosx, short *pPosy );

// ���һ���հ׵�
int map_getrandpos( int type, short *pPosx, short *pPosy );

// ����ָ����ķ�Χ��ȡһ�����������
int map_getrandpos_withrange( short posx, short posy, int range, short *pPosx, short *pPosy );

// �����ҳǳ�λ��
int map_getrandcitypos( short *pPosx, short *pPosy );

// ָ���������һ��������
int map_zone_randpos( short zoneid, short *pPosx, short *pPosy );

// �ж�����ص��Ƿ���Ǩ��
int map_canmove( short posX, short posY );

// dump��ͼ����
void map_tile_dump();
#endif
