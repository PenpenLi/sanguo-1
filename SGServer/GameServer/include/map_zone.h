#ifndef _MAP_ZONE_H_
#define _MAP_ZONE_H_
#include "define.h"
#define MAPZONE_TYPE0		0 // ����
#define MAPZONE_TYPE1		1 // �ݵ�
#define MAPZONE_TYPE2		2 // �ʳ�
#define MAPZONE_CENTERID	13
#define MAPZONE_MAXNUM		26 // 1-25

int map_zone_load();
int map_zone_save( FILE *fp );
MapZone *map_zone_getptr( int zoneid );

// �����Ƿ���ָ��������
char map_zone_inrange( int zoneid, short posx, short posy );

// ��ȡ����id
char map_zone_getid( short posx, short posy );
char map_zone_gettype( char zoneid );

// �Ƿ��ǵ�ǰ��ͼ�Ŀ��ƶ���ͼ
char map_zone_ismovezone( char zoneid, char movezoneid );

// ����ʾ��Ԫ��ӵ�����
int map_zone_addunit( int unit_index, int zoneid );

// ����ʾ��Ԫ�Ƴ�������
int map_zone_delunit( int unit_index );

// ����ǲ�����ͬһ������
char map_zone_checksame( short posx, short posy, short tposx, short tposy );

// ���õ�������
int map_zone_setnation( int zoneid, char nation );

// ָ���������һ��������
int map_zone_randpos( short zoneid, short *pPosx, short *pPosy, int scope );

// ָ�������͹����������һ��������
int map_zone_nation_randpos( char nation, short *pPosx, short *pPosy, int scope );

// �����л�
void map_zone_change( int actor_index, short posx, short posy, char areaupdate );

// ��������б�
int map_zone_citylist( int actor_index, int zoneid );

// ���������б�
int map_zone_townlist( int actor_index, int zoneid );

// �����ʳ����򶼳Ǻ����������б�
int map_zone_center_townlist( int actor_index );

// �����ʳ����򶼳Ǻ����Ǹ���
int map_zone_center_townchange( int townid );

// ��ʾǰ���ݳǰ�ť
int map_zone_goto_zc_send( int actor_index );

// ǰ���ݳ�
int map_zone_goto_zc( int actor_index );
#endif 
