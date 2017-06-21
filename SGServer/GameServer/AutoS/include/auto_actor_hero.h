#ifndef __HERO_AUTO_H
#define __HERO_AUTO_H
#include "define.h"

struct _actor_hero {
//--Automatically generated
				i64 id;	//������
				int actorid;	//�ǳ�
				int offset;	//����
				short kind;	//Ӣ������
				short level;	//�ȼ�
				int exp;	//����
				int soldiers;	//����
				short attack;	//��������
				short defense;	//��������
				short troops;	//��������
				short growth;	//������
				Equip equip[6];	//װ��
};
typedef struct _actor_hero Hero;

typedef Hero * (*LPCB_GETHERO)( int actorid, int offset );
int actor_hero_load_auto( int actorid, int actor_index, LPCB_GETHERO pCB_GetHero, char *pTab );
int actor_hero_save_auto( Hero *pHero, char *pTab, FILE *fp );
int actor_hero_batch_save_auto( Hero *pHero, int maxcount,  char *pTab, FILE *fp );

#endif
