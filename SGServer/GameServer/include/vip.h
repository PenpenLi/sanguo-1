#ifndef _VIP_H_
#define _VIP_H_
#include "define.h"

#define VIP_ABILITY_MAXNUM 6

// ����VIP�ȼ�
int vip_calclevel( int city_index );

// VIP��������ֵ
int vip_expmax_get( int level );

// ����VIP����
int vip_exp( int city_index, int value, short path );
#endif
