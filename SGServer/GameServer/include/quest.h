#ifndef _QUEST_H_
#define _QUEST_H_
#include "define.h"

#define QUEST_MAXNUM		2000		// �����������

#define QUEST_COMPLETEFLAG_NORMAL	0	// ȱʡ
#define QUEST_COMPLETEFLAG_SUCCESS	1	// ���
#define QUEST_COMPLETEFLAG_AWARDED	2	// �Ѿ���ȡ����

#define QUEST_DATAINDEX_WELCOME				0	// ��ӭ����
#define QUEST_DATAINDEX_ACTOR_LEVEL			1	// �����ȼ� datatype=1 datakind=0 needvalue=�ȼ�
#define	QUEST_DATAINDEX_BUILDING_LEVEL		2	// �����ȼ� datatype=2 datakind=����kind dataoffset=��Դ������� needvalue=�����ȼ�
#define	QUEST_DATAINDEX_BUILDING_SILVER		3	// N����ӴﵽN�� datatype=3 datakind=�ȼ� needvalue=��������
#define	QUEST_DATAINDEX_BUILDING_WOOD		4	// N��ľ���ﵽN�� datatype=4 datakind=�ȼ� needvalue=��������
#define	QUEST_DATAINDEX_BUILDING_FOOD		5	// N��ũ��ﵽN�� datatype=5 datakind=�ȼ� needvalue=��������
#define	QUEST_DATAINDEX_BUILDING_IRON		6	// N���󳡴ﵽN�� datatype=6 datakind=�ȼ� needvalue=��������
#define QUEST_DATAINDEX_LEVYNUM				7	// ���մ��� datatype=7 datakind=0 needvalue=����
#define QUEST_DATAINDEX_HISTORY				8	// ���� datatype=8 datakind=������� needvalue=1
#define	QUEST_DATAINDEX_KILLMONSTER			9	// ������N�� datatype=9 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_KILLMONSTER_LEVEL	10	// ������N��N�� datatype=10 datakind=�ȼ� needvalue=����
#define	QUEST_DATAINDEX_EQUIP_FORGING		11	// ����Nװ��N���� datatype=11 datakind=װ��kind needvalue=����
#define	QUEST_DATAINDEX_EQUIP_WASH			12	// װ��ϴ������ datatype=12 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_EQUIP_COLORWASH		13	// ��NƷ��װ��������ϴ�������� datatype=13 datakind=��ɫ needvalue=1
#define	QUEST_DATAINDEX_TRAIN				14	// ļ��N����N���� datatype=14 datakind=���֣�1��2��3�� needvalue=����
#define	QUEST_DATAINDEX_TRAINCOUNT			15	// ļ��N�� datatype=15 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_CITY_TECH			16	// �о�N�Ƽ�N�� datatype=16 datakind=�Ƽ�ID needvalue=�ȼ�
#define	QUEST_DATAINDEX_CITY_TECHONE		17	// �о�һ��N�Ƽ� datatype=17 datakind=�Ƽ�ID needvalue=1
#define	QUEST_DATAINDEX_HERO_WASHCOUNT		18	// �佫ϴ��N�� datatype=18 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_HERO_COLORWASH		19	// ��һ��NƷ�ʵ��佫����ϴ�� datatype=19 datakind=��ɫ needvalue=1
#define	QUEST_DATAINDEX_HERO_CALL			20	// ��ļN���佫 datatype=20 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_WISHING				21	// �۱���N�� datatype=21 datakind=0 needvalue=����
#define	QUEST_DATAINDEX_CITYFIGHT			22	// �ɹ�����N���й���� datatype=22 datakind=0 needvalue=����

// ��������
enum 
{
	QUEST_TYPE_MAIN = 0,	// ��������
	QUEST_TYPE_BRANCH,		// ֧������
	QUEST_TYPE_MAXNUM
};


// �����б���Ϣ��ʼ��
int questlist_init();

//�ض�
int questlist_reload();

// ��ȡ����
int quest_give( int actor_index );

// ��������ֵ
int quest_addvalue( struct _city *pCity, int dataindex, int datakind, int value );

// ��ȡ����״̬
int quest_getcomplete( int actor_index, int questid, int *value );

// ��������״̬
int quest_setcomplete( int actor_index, int questid, int flag );

// ������
int quest_check( int actor_index, int questid, int *value );

// ������
int quest_checkcomplete( struct _city *pCity );

// ������������
int quest_reset( int actor_index );

// ��ȡ������
int quest_getaward( int actor_index, int questid, char type );

// �����б�
int quest_sendlist( int actor_index );

// ������
int quest_sendawardinfo( int actor_index, int questid );

// ����������ʾ
//int quest_sendnotify( int actor_index );

#endif
