#ifndef _MAP_RES_H_
#define _MAP_RES_H_
#include "define.h"

int map_res_load();
int map_res_save( FILE *fp );
MapRes *map_res_getptr( int index );

// ��ʾ��Ԫ����
void map_res_makeunit( int index, SLK_NetS_AddMapUnit *pAttr );

// λ��
void map_res_getpos( int index, short *posx, short *posy );

#endif
