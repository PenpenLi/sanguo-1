#ifndef _ARMY_H_
#define _ARMY_H_
#include "define.h"

// ��ʾ��Ԫ����
void army_makeunit( int army_index, SLK_NetS_AddMapUnit *pAttr );

// ����λ��
void army_getpos( int army_index, short *posx, short *posy );

#endif
