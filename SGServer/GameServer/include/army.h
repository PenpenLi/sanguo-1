#ifndef _ARMY_H_
#define _ARMY_H_
#include "define.h"

// ��֧����״̬
#define ARMY_STATE_IDLE				0	// ����
#define ARMY_STATE_GROUP_START		1	// ���𼯽�
#define ARMY_STATE_GROUP_ING		2	// ������
#define ARMY_STATE_GROUP_END		3	// ����ָ������ص�,�������
#define ARMY_STATE_READY			4	// ׼����
#define ARMY_STATE_MARCH			10	// �о���
#define ARMY_STATE_FIGHT			20	// ս����
#define ARMY_STATE_OCCUPY			21	// פ����
#define ARMY_STATE_GATHER			22	// �ɼ���
#define ARMY_STATE_SHELTER			23	// �ӻ���
#define ARMY_STATE_HELP				24	// Ԯ����
#define ARMY_STATE_REBACK			30	// ������

// ��Ϊ
#define ARMY_ACTION_IDLE				0	// ����
#define ARMY_ACTION_FIGHT				1	// ȥս��
#define ARMY_ACTION_OCCUPY				2	// ȥפ��
#define ARMY_ACTION_GATHER				3	// ȥ�ɼ�
#define ARMY_ACTION_HELP_TROOP			6	// ȥʿ��Ԯ��

#define ARMY_ACTION_GROUP_START			10	// ���𼯽���
#define ARMY_ACTION_GROUP_ING			11	// ȥ������


#define ARMY_STATE_FIGHT_TIME		1	// ս��ʱ��(S)
#define ARMY_CARRY_ITEMMAX			8	// ����Я���ĵ���
#define ARMY_HERO_MAX				4	// ��������佫

int army_load();
int army_save( FILE *fp );
Army *army_getptr( int army_index );

// ��ʾ��Ԫ����
void army_makeunit( int army_index, SLK_NetS_AddMapUnit *pAttr );

// ����λ��
void army_getpos( int army_index, short *posx, short *posy );

// ����
int army_battle( City *pCity, SLK_NetC_MapBattle *info );

// ����һ֧����
int army_create( char from_type, int from_id, char to_type, int to_id, char stat, SLK_NetC_MapBattle *info );

// ɾ��һ֧����
void army_delete( int army_index );

// ������Ϣ��ԭ���ǳ�
int army_tocity( int army_index );

// ���ò���״̬
void army_setstate( int army_index, char state );

// �����߼�
void army_alllogic();

// ��ֻ�����߼�
void army_logic( int army_index );

// ��ȡ���������ǳ�
City *army_getcityptr( int army_index );

// ��ȡ����Ŀ�������ǳ�
City *army_getcityptr_target( int army_index );

// ��ȡ��������
char *army_getname( int army_index );

// ��ȡ����Ŀ������
char *army_getname_target( int army_index );

// ��ȡ���������ǳ�
int army_getcityid( int army_index );

// ��ȡ����Ŀ��ǳ�
int army_getcityid_target( int army_index );

// ��ȡ������������
int army_getnation( int army_index );

// ��ȡ����Ŀ�����
int army_getnation_target( int army_index );

// �������Я������
int army_carry_additem( int army_index, int itemkind, int itemnum );

// �ɼ�ʱ��
int army_gather_time( int army_index );

// ���Ӳɼ�������
int army_gather_calc( int army_index );

// ���Ӳɼ���
int army_gather( int army_index );

// ���ӱӻ���
void army_shelter( int army_index );

// ����Ԯ����
void army_help( int army_index );

// פ����
void army_occupy( int army_index );

// ����ս����
void army_fight( int army_index );

// ��鲿���ǲ����Լ���
int army_myself( int actor_index, int army_index );

#endif
