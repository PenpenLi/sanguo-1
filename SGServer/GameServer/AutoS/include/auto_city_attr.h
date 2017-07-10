#ifndef __CITYATTR_AUTO_H
#define __CITYATTR_AUTO_H
#include "define.h"

struct _city_attr {
//--Automatically generated
				int actorid;	//��ɫID
				short silver_per;	//���Ҳ�������%
				short wood_per;	//ľ�Ĳ�������%
				short food_per;	//��ʳ��������%
				short iron_per;	//������������%
				short protectres_per;	//�ֿⱣ������%
				short buildingsec_per;	//����ʱ�����%
				short infantry_attack;	//�����佫���ӹ�����
				short cavalry_attack;	//����佫���ӹ�����
				short archer_attack;	//�����佫���ӹ�����
};
typedef struct _city_attr CityAttr;

typedef CityAttr * (*LPCB_GETCITYATTR)( int actorid );
typedef int (*LPCB_LOADCITYATTR)( int actorid );
int city_attr_load_auto( LPCB_GETCITYATTR pCB_GetCityAttr, LPCB_LOADCITYATTR pCB_LoadCityAttr, const char *pTab );
int city_attr_save_auto( CityAttr *pCityAttr, const char *pTab, FILE *fp );

#endif
