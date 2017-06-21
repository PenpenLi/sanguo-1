#ifndef __EQUIP_AUTO_H
#define __EQUIP_AUTO_H
#include "define.h"

struct _actor_equip {
//--Automatically generated
				i64 id;	//������
				int actorid;	//��ɫID
				int offset;	//װ�����ڱ���λ��
				int kind;	//��Ʒ����
				short ability[4];	//����
				int value[4];	//����ֵ
};
typedef struct _actor_equip Equip;

typedef Equip * (*LPCB_GETEQUIP)( int actorid, int offset );
int actor_equip_load_auto( int actorid, int actor_index, LPCB_GETEQUIP pCB_GetEquip, char *pTab );
int actor_equip_save_auto( Equip *pEquip, char *pTab, FILE *fp );
int actor_equip_batch_save_auto( Equip *pEquip, int maxcount,  char *pTab, FILE *fp );

#endif
