#ifndef _SHOP_H_
#define _SHOP_H_
#include "define.h"

#define SHOPTYPE_SALE	1	// �ؼ�
#define SHOPTYPE_FIGHT	2	// ����
#define SHOPTYPE_OTHER	3	// ����

int shop_list( int actor_index, int type );
int shop_buy( int actor_index, int type, int offset, int awardkind );
#endif
