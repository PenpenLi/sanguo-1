#ifndef __BUILDINGBARRACKS_AUTO_H
#define __BUILDINGBARRACKS_AUTO_H
#include "define.h"

struct _city_building_barracks {
//--Automatically generated
				char kind;	//��Ӫ����
				char level;	//��Ӫ�ȼ�
				int trainnum;	//��ǰѵ��ʿ����
				int trainsec;	//��ǰѵ��ʣ��ʱ��(��)
				int trainsec_need;	//��ǰѵ����Ҫʱ��(��)
				int queuenum[11];	//��ļ����
				int queuesec[11];	//��ļ����
				char queue;	//���ݶ�������
				char trainlong;	//ļ����ʱ����
				int overnum;	//�Ѿ���ļ��ɵ�����
				short quicksec;	//ļ������ʱ����
};
typedef struct _city_building_barracks BuildingBarracks;

typedef BuildingBarracks * (*LPCB_GETBUILDINGBARRACKS)( int actorid, int offset );
int city_building_barracks_load_auto( int actorid, int city_index, LPCB_GETBUILDINGBARRACKS pCB_GetBuildingBarracks, const char *pTab );
int city_building_barracks_save_auto( int actorid, int offset, BuildingBarracks *pBuildingBarracks, const char *pTab, FILE *fp );
int city_building_barracks_batch_save_auto( int actorid, BuildingBarracks *pBuildingBarracks, int maxcount, const char *pTab, FILE *fp );

#endif
