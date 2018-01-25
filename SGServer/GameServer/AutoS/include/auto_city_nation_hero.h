#ifndef __CITYNATIONHERO_AUTO_H
#define __CITYNATIONHERO_AUTO_H
#include "define.h"

struct _city_nation_hero {
//--Automatically generated
				short herokind;	//����Ӣ��
				char state;	//1��Ѻ,2�Ѿ�Ȱ��
				char forever;	//�Ƿ�����ӵ��
				char loyal;	//�ҳ϶�
				char buypos;	//�����������
				short posx;	//���������
				short posy;	//���������
};
typedef struct _city_nation_hero CityNationHero;

typedef CityNationHero * (*LPCB_GETCITYNATIONHERO)( int actorid, int offset );
int city_nation_hero_load_auto( int actorid, int city_index, LPCB_GETCITYNATIONHERO pCB_GetCityNationHero, const char *pTab );
int city_nation_hero_save_auto( int actorid, int offset, CityNationHero *pCityNationHero, const char *pTab, FILE *fp );
int city_nation_hero_batch_save_auto( int actorid, CityNationHero *pCityNationHero, int maxcount, const char *pTab, FILE *fp );

#endif
