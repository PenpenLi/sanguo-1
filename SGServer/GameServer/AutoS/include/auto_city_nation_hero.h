#ifndef __NATIONHERO_AUTO_H
#define __NATIONHERO_AUTO_H
#include "define.h"

struct _city_nation_hero {
//--Automatically generated
				char herokind;	//����Ӣ��
				char state;	//1��Ѻ,2�Ѿ�Ȱ��
				char forever;	//�Ƿ�����ӵ��
				unsigned char loyal;	//�ҳ϶�
};
typedef struct _city_nation_hero NationHero;

typedef NationHero * (*LPCB_GETNATIONHERO)( int actorid, int offset );
int city_nation_hero_load_auto( int actorid, int city_index, LPCB_GETNATIONHERO pCB_GetNationHero, const char *pTab );
int city_nation_hero_save_auto( int actorid, int offset, NationHero *pNationHero, const char *pTab, FILE *fp );
int city_nation_hero_batch_save_auto( int actorid, NationHero *pNationHero, int maxcount, const char *pTab, FILE *fp );

#endif
