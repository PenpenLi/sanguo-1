#ifndef __BUILDINGBARRACKS_AUTO_H
#define __BUILDINGBARRACKS_AUTO_H
#include "define.h"

struct _city_building_barracks {
//--Automatically generated
				char kind;	//��Ӫ����
				char level;	//��Ӫ�ȼ�
				int soldiers;	//��Ӫ����
				char queue;	//���ݶ�������
				int trainnum[8];	//ѵ������ʿ����
				int trainsec[8];	//ѵ������ʣ��ʱ��
				char trainlong;	//ļ����ʱ����
				short quicksec;	//ļ������ʱ����
				char value;	//���Ӫʹ��
};
typedef struct _city_building_barracks BuildingBarracks;

typedef BuildingBarracks * (*LPCB_GETBUILDINGBARRACKS)( int actorid, int offset );
int city_building_barracks_load_auto( int actorid, int city_index, LPCB_GETBUILDINGBARRACKS pCB_GetBuildingBarracks, char *pTab );
int city_building_barracks_save_auto( int actorid, int offset, BuildingBarracks *pBuildingBarracks, char *pTab, FILE *fp );
int city_building_barracks_batch_save_auto( int actorid, BuildingBarracks *pBuildingBarracks, int maxcount,  char *pTab, FILE *fp );

#endif
