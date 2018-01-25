#ifndef __NATIONHERO_AUTO_H
#define __NATIONHERO_AUTO_H
#include "define.h"

struct _nation_hero {
//--Automatically generated
				short kind;	//��������kind
				int actorid;	//��ǰ�������
				short posx;	//λ��
				short posy;	//λ��
				int runsec;	//���ܵ���ʱ
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
				int unit_index;	//��ʾ����
				int city_index;	//��ǰ�����ǳ�����
};
typedef struct _nation_hero NationHero;

typedef NationHero * (*LPCB_GETNATIONHERO)( int kind );
typedef int (*LPCB_LOADNATIONHERO)( int kind );
int nation_hero_load_auto( LPCB_GETNATIONHERO pCB_GetNationHero, LPCB_LOADNATIONHERO pCB_LoadNationHero, const char *pTab );
int nation_hero_save_auto( NationHero *pNationHero, const char *pTab, FILE *fp );
int nation_hero_batch_save_auto( NationHero *pNationHero, int maxcount,  const char *pTab, FILE *fp );

#endif
