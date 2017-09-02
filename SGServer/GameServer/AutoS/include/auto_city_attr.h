#ifndef __CITYATTR_AUTO_H
#define __CITYATTR_AUTO_H
#include "define.h"

struct _city_attr {
//--Automatically generated
				int actorid;	//��ɫID
				float silver_per;	//���Ҳ�������%
				float wood_per;	//ľ�Ĳ�������%
				float food_per;	//��ʳ��������%
				float iron_per;	//������������%
				float train_per[3];	//����ÿ������ļ����%
				float movespeed_per[3];	//�����佫�о��ٶ�%
				float protectres_per;	//�ֿⱣ������%
				float buildingsec_per;	//���̽�����������ʱ��%
				float materialsec_per[2];	//��������������ʱ%
				float gather_per[2];	//�ɼ��ջ�ӳ�%
				float heroluck_per;	//�����佫����ͻ�Ƹ���%
				float prestige_per;	//�����佫ɱ�л����������%
				float damageguard_per;	//�ԳǷ����˺�%
				float trainspeed_per;	//����ļ��%
				short hero_attack[3];	//��߲����佫���������̶���ֵ��
				short hero_defense[3];	//��߲����佫���������̶���ֵ��
				short hero_troops[3];	//�������佫�������̶���ֵ��
				char hero_up_num;	//���������佫�������̶���ֵ��
				char hero_row_num;	//�����佫�����������̶���ֵ��
				char nequip_crit;	//������N���������̶���ֵ��
				char spy_city;	//�����й���ҳǳ���Ϣ���̶���ֵ��
				int free_sec;	//�������������
				char everyday_body_buymax;	//���������������
				char everyday_autobuild_buynum;	//�Զ�������ѹ������
				char everyday_army_recall;	//ÿ������о��ٻ�
				char ability_open_201;	//�ؼ�����ɫ����װ��������������ͬ���ɿ����ؼ����������ܣ�
				char ability_open_202;	//��Ʒװ��������װ���и���ֱ�ӻ���ؼ�װ�����������ܣ�
				char ability_open_203;	//�����ٵأ��ɲ��������ѡ��ָ�����ͽ��������ؽ����������ܣ�
				char ability_open_204;	//�Զ������������Զ��������������ܣ�
				char ability_open_205;	//ɨ���������������ܣ�
				char ability_open_206;	//����ս�����������ܣ�
				char ability_open_207;	//�����ʹ���Ժ���������ܣ�
};
typedef struct _city_attr CityAttr;

typedef CityAttr * (*LPCB_GETCITYATTR)( int actorid );
typedef int (*LPCB_LOADCITYATTR)( int actorid );
int city_attr_load_auto( LPCB_GETCITYATTR pCB_GetCityAttr, LPCB_LOADCITYATTR pCB_LoadCityAttr, const char *pTab );
int city_attr_save_auto( CityAttr *pCityAttr, const char *pTab, FILE *fp );

#endif
