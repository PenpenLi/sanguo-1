#ifndef __BUILDING_AUTO_H
#define __BUILDING_AUTO_H
#include "define.h"

struct _city_building {
//--Automatically generated
				char kind;	//��������
				char level;	//�����ȼ�
				char officialkind;	//����ʹ�ù�Ա
				int officialfree;	//�Ƿ�ʹ�ù����(��λ)
				int officialsec;	//��Աʣ��ʱ��
				int value;	//ͨ��ֵ
				int sec;	//ʱ��
				short quicksec;	//����ʱ��
};
typedef struct _city_building Building;

typedef Building * (*LPCB_GETBUILDING)( int actorid, int offset );
int city_building_load_auto( int actorid, int city_index, LPCB_GETBUILDING pCB_GetBuilding, const char *pTab );
int city_building_save_auto( int actorid, int offset, Building *pBuilding, const char *pTab, FILE *fp );
int city_building_batch_save_auto( int actorid, Building *pBuilding, int maxcount, const char *pTab, FILE *fp );

#endif
