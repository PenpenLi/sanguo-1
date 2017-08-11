#ifndef __HERO_AUTO_H
#define __HERO_AUTO_H
#include "define.h"

struct _actor_hero {
//--Automatically generated
				i64 id;	//������
				int actorid;	//�ǳ�
				int offset;	//����
				short kind;	//Ӣ������
				char color;	//��ɫ
				short level;	//�ȼ�
				int exp;	//����
				int soldiers;	//��ǰ����
				short attack_wash;	//ϴ�蹥������
				short defense_wash;	//ϴ���������
				short troops_wash;	//ϴ���������
				short colorup;	//����ͻ��ֵ
				Equip equip[6];	//װ��
				int attack;	//����
				int defense;	//����
				int troops;	//����
				short attack_increase;	//������ǿ
				short defense_increase;	//������ǿ
				short assault;	//����
				short defend;	//�س�
				char state;	//״̬
};
typedef struct _actor_hero Hero;

typedef Hero * (*LPCB_GETHERO)( int actorid, int offset );
int actor_hero_load_auto( int actorid, int actor_index, LPCB_GETHERO pCB_GetHero, const char *pTab );
int actor_hero_save_auto( Hero *pHero, const char *pTab, FILE *fp );
int actor_hero_batch_save_auto( Hero *pHero, int maxcount,  const char *pTab, FILE *fp );

#endif
