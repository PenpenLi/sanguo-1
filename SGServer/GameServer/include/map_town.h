#ifndef _MAP_TOWN_H_
#define _MAP_TOWN_H_
#include "define.h"

int map_town_load();
int map_town_save( FILE *fp );
MapTown *map_town_getptr( int townid );

// ��ʾ��Ԫ����
void map_town_makeunit( int index, SLK_NetS_AddMapUnit *pAttr );

// λ��
void map_town_getpos( int index, short *posx, short *posy );

#endif
