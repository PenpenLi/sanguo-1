#ifndef _BUILDING_H_
#define _BUILDING_H_
#include "define.h"

// ����������ͨ����
#define	BUILDING_Main		1	// �ٸ�
#define	BUILDING_Wall		2	// ��ǽ
#define	BUILDING_StoreHouse	3	// �ֿ�
#define	BUILDING_Tech		4	// ̫ѧԺ
#define	BUILDING_Craftsman	5	// ��������
#define	BUILDING_Cabinet	6	// �ڸ�

// ��Ӫ
#define	BUILDING_Infantry	11	// ����Ӫ
#define	BUILDING_Cavalry	12	// ���Ӫ
#define	BUILDING_Archer		13	// ����Ӫ
#define	BUILDING_Militiaman	14	// ���Ӫ

// ��Դ����
#define	BUILDING_Silver		21	// ����
#define	BUILDING_Wood		22	// ľ��
#define	BUILDING_Food		23	// ʳ��
#define	BUILDING_Iron		24	// ����

// ����ڽ���
#define	BUILDING_Smithy		31	// ������
#define	BUILDING_Wash		32	// ϴ����
#define	BUILDING_Fangshi	33	// ����
#define	BUILDING_Shop		34	// �̵�
#define	BUILDING_Hero		35	// ���͹�
#define	BUILDING_Wishing	36	// �۱���
#define	BUILDING_Help		37	// ����

// ��ȡ����ָ��
Building* building_getptr( int city_index, int offset );
BuildingBarracks* buildingbarracks_getptr( int city_index, int offset );
BuildingRes* buildingres_getptr( int city_index, int offset );

// ��������
int building_create( int city_index, int kind, int offset );

// ��������
int building_upgrade( int city_index, int offset );

// �����ȼ�
int building_level( int city_index, int offset );

// ��ȡʿ������
int building_soldiers_total( int city_index, char kind );

// �������н����б�
int building_sendlist( int city_index );

#endif