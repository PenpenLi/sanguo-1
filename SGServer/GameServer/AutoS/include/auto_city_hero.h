#ifndef __CITYHERO_AUTO_H
#define __CITYHERO_AUTO_H
#include "define.h"

struct _city_hero {
//--Automatically generated
				short kind;	//Ӣ������
				short level;	//�ȼ�
				int exp;	//����
				short soldiers;	//����
				short attack;	//��������
				short defense;	//��������
				short troops;	//��������
				short growth;	//������
				HeroEquip equip[6];	//װ��
};
typedef struct _city_hero CityHero;

typedef CityHero * (*LPCB_GETCITYHERO)( int cityid, int offset );
int city_hero_load_auto( int cityid, int city_index, LPCB_GETCITYHERO pCB_GetCityHero, char *pTab );
int city_hero_save_auto( int cityid, int offset, CityHero *pCityHero, char *pTab, FILE *fp );
int city_hero_batch_save_auto( int cityid, CityHero *pCityHero, int maxcount,  char *pTab, FILE *fp );

#endif
