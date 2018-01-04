#ifndef _CITY_ATTR_H_
#define _CITY_ATTR_H_
#include "define.h"

#define CITY_ATTR_ABILITY_1			1	// ��������ÿСʱ����%
#define CITY_ATTR_ABILITY_2			2	// ����ľ��ÿСʱ����%
#define CITY_ATTR_ABILITY_3			3	// ������ʳÿСʱ����%
#define CITY_ATTR_ABILITY_4			4	// ��������ÿСʱ����%
#define CITY_ATTR_ABILITY_5			5	// ��������ÿ������ļ����%
#define CITY_ATTR_ABILITY_6			6	// �������ÿ������ļ����%
#define CITY_ATTR_ABILITY_7			7	// ��������ÿ������ļ����%
#define CITY_ATTR_ABILITY_8			8	// �����佫�о��ٶ�%���Ƽ�ʹ�ã�
#define CITY_ATTR_ABILITY_9			9	// �����ֿⱣ����Դ��%
#define CITY_ATTR_ABILITY_10		10	// ���̽�����������ʱ��%
#define CITY_ATTR_ABILITY_11		11	// ��������������ʱ%(�Ƽ�ʹ��)
#define CITY_ATTR_ABILITY_12		12	// ��λʱ��ɼ��ջ�ӳ�%(�Ƽ�ʹ��)
#define CITY_ATTR_ABILITY_13		13	// �����佫����ͻ�Ƹ���%
#define CITY_ATTR_ABILITY_14		14	// �����佫ɱ�л����������%
#define CITY_ATTR_ABILITY_15		15	// �ԳǷ����˺�%
#define CITY_ATTR_ABILITY_16		16	// ��ټ���ļ��%
#define CITY_ATTR_ABILITY_17		17	// ��������������ʱ%���ʹ�ã�
#define CITY_ATTR_ABILITY_18		18	// �����佫�о��ٶ�%������ʹ�ã�
#define CITY_ATTR_ABILITY_19		19	// �����佫�о��ٶ�%������ʹ�ã�
#define CITY_ATTR_ABILITY_20		20	// ��λʱ��ɼ��ջ�ӳ�%(�ʹ��)

#define CITY_ATTR_ABILITY_100		100	// ��������佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_101		101	// ��߲����佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_102		102	// �������佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_103		103	// ��߹����佫���������̶���ֵ��

#define CITY_ATTR_ABILITY_110		110	// ��������佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_111		111	// ��߲����佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_112		112	// �������佫���������̶���ֵ��
#define CITY_ATTR_ABILITY_113		113	// ��߹����佫���������̶���ֵ��

#define CITY_ATTR_ABILITY_120		120	// ��������佫�������̶���ֵ��
#define CITY_ATTR_ABILITY_121		121	// ��߲����佫�������̶���ֵ��
#define CITY_ATTR_ABILITY_122		122	// �������佫�������̶���ֵ��
#define CITY_ATTR_ABILITY_123		123	// ��߹����佫�������̶���ֵ��

#define CITY_ATTR_ABILITY_130		130	// ���������佫�������̶���ֵ�����Ƽ�ʹ�ã�
#define CITY_ATTR_ABILITY_131		131	// �����佫�����������̶���ֵ��
#define CITY_ATTR_ABILITY_132		132	// ����������������N���������̶���ֵ��
#define CITY_ATTR_ABILITY_133		133	// ��飺�����й���ҳǳ���Ϣ���̶���ֵ��
#define CITY_ATTR_ABILITY_134		134	// ������������루�̶���ֵ��
#define CITY_ATTR_ABILITY_135		135	// ��������������ޣ��̶���ֵ��
#define CITY_ATTR_ABILITY_136		136	// �Զ�������ѹ���������̶���ֵ��
#define CITY_ATTR_ABILITY_137		137	// ÿ������о��ٻأ��̶���ֵ��
#define CITY_ATTR_ABILITY_138		138	// �����佫�����������̶���ֵ�����ڸ�����
#define CITY_ATTR_ABILITY_139		139	// �����佫�����������̶���ֵ�����ڸ�ɼ���

#define CITY_ATTR_ABILITY_201		201	// �ؼ�����ɫ����װ��������������ͬ���ɿ����ؼ����������ܣ�
#define CITY_ATTR_ABILITY_202		202 // ��Ʒװ��������װ���и���ֱ�ӻ���ؼ�װ�����������ܣ�
#define CITY_ATTR_ABILITY_203		203	// �����ٵأ��ɲ��������ѡ��ָ�����ͽ��������ؽ����������ܣ�
#define CITY_ATTR_ABILITY_204		204	// �Զ������������Զ��������������ܣ�

void city_attr_reset( City *pCity );
void city_attr_calc( CityAttr *pAttr, short ability, int value, float digit );
void city_attr_sendinfo( int actor_index );

// ս���仯;��
#define  BATTLEPOWER_PATH_HERO		1
#define  BATTLEPOWER_PATH_EQUIP		2
#define  BATTLEPOWER_PATH_TECH		3
#define  BATTLEPOWER_PATH_NEQUIP	4
#define  BATTLEPOWER_PATH_PLACE		5
#define  BATTLEPOWER_PATH_GIRL		6
#define  BATTLEPOWER_PATH_BUILDING	7

// ������ս��
void city_battlepower_reset( City *pCity );

// ��ս������
void city_battlepower_calc( City *pCity, char path );

// Ӣ���ṩս��
void city_battlepower_hero_calc( City *pCity );

// װ���ṩս��
void city_battlepower_equip_calc( City *pCity );

// �Ƽ��ṩս��
void city_battlepower_tech_calc( City *pCity );

// �����ṩս��
void city_battlepower_nequip_calc( City *pCity );

// ��λ�ṩս��
void city_battlepower_place_calc( City *pCity );

// Ů���ṩս��
void city_battlepower_girl_calc( City *pCity );

// �����ṩս��
void city_battlepower_building_calc( City *pCity );


// buff
#define CITY_BUFF_MAX		8 // buff����
#define CITY_BUFF_MARCH		0 // ���ܹ�buff �о���ʱ����15%
#define CITY_BUFF_TRAIN		1 // �����buff ��ļ��ʱ����15%
#define CITY_BUFF_WIND		2 // ������buff �о���ʱ����15%
#define CITY_BUFF_FIRE		3 // ������buff ʿ������+5%
#define CITY_BUFF_MOUNTAIN	4 // ɽ����buff ʿ������+5%
#define CITY_BUFF_FOREST	5 // ������buff �ڱ�Ӫ�ж�������20%�˲��ָ�
// buff
int city_change_buff( int city_index, int index, int sec, short path );

#endif
