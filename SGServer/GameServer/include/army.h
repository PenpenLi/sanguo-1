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

#define ARMY_ACTION_GROUP_START			10	// ���𼯽���
#define ARMY_ACTION_GROUP_ING			11	// ȥ������


#define ARMY_STATE_FIGHT_TIME		3	// ս��ʱ��(S)
#define ARMY_CARRY_ITEMMAX			5	// ����Я���ĵ���

int army_load();
int army_save( FILE *fp );
Army *army_getptr( int army_index );

// ��ʾ��Ԫ����
void army_makeunit( int army_index, SLK_NetS_AddMapUnit *pAttr );

// ����λ��
void army_getpos( int army_index, short *posx, short *posy );

#endif
