#ifndef _MAP_ENEMY_H_
#define _MAP_ENEMY_H_
#include "define.h"

// ��ʾ��Ԫ����
void map_enemy_makeunit( int index, SLK_NetS_AddMapUnit *pAttr );

// λ��
void map_enemy_getpos( int index, short *posx, short *posy );

#endif
