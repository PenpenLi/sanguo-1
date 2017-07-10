#ifndef _BUILDING_H_
#define _BUILDING_H_
#include "define.h"
#include "server_netsend_auto.h"

#define BUILDING_MAXNUM				6 // ��ͨ��������
#define BUILDING_BARRACKS_MAXNUM	4 // ��Ӫ��������
#define BUILDING_RES_MAXNUM			64// ��Դ��������

// ����������ͨ����
#define	BUILDING_Main		1	// �ٸ�
#define	BUILDING_Wall		2	// ��ǽ
#define	BUILDING_StoreHouse	3	// �ֿ�
#define	BUILDING_Tech		4	// ̫ѧԺ
#define	BUILDING_Craftsman	5	// ��������
#define	BUILDING_Cabinet	6	// �ڸ�

// ��Ӫ
#define	BUILDING_Infantry				11	// ����Ӫ
#define	BUILDING_Cavalry				12	// ���Ӫ
#define	BUILDING_Archer					13	// ����Ӫ
#define	BUILDING_Militiaman_Infantry	14	// ���Ӫ-����
#define	BUILDING_Militiaman_Cavalry		15	// ���Ӫ-���
#define	BUILDING_Militiaman_Archer		16	// ���Ӫ-����

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

#define	BUILDING_OP_BUILD	1	// ����
#define	BUILDING_OP_UPGRADE	2	// ����
#define	BUILDING_OP_DELETE	3	// ���

#define	BUILDING_TRAIN_MAXNUM	8	// ��Ӫ���8����ļ����	

// ��ȡ����ָ��
Building* building_getptr( int city_index, int offset );
BuildingBarracks* buildingbarracks_getptr( int city_index, int offset );
BuildingRes* buildingres_getptr( int city_index, int offset );
BuildingRes *buildingres_getptr_number( int city_index, int kind, int no );

// ��ȡ������������Ϣ
BuildingUpgradeConfig* building_getconfig( int kind, int level );

// ��ȡ�����ȼ�
int building_getlevel( int city_index, int kind, int no );

// ����һ������
int building_give( int city_index, int kind, int num );

// ��������
int building_create( int city_index, int kind, int offset );

// ��������
int building_upgrade( int city_index, int kind, int offset );

// �������
int building_delete( int city_index, int kind, int offset );

// �������������������
int building_finish( int city_index, int op, int kind, int offset );

// ��ȡʿ������
int building_soldiers_total( int city_index, char kind );

// ƴ���ͽṹ
void building_makestruct( Building *pBuilding, int offset, SLK_NetS_Building *pValue );
void building_barracks_makestruct( BuildingBarracks *pBuilding, int offset, SLK_NetS_BuildingBarracks *pValue );
void building_res_makestruct( BuildingRes *pBuilding, int offset, SLK_NetS_BuildingRes *pValue );

// ����������Ϣ����
int building_sendinfo( int actor_index, int kind );
int building_sendinfo_barracks( int actor_index, int kind );
int building_sendinfo_res( int actor_index, int offset );

// �������н����б�
int building_sendlist( int city_index );

#endif