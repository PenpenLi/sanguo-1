#ifndef __CITY_AUTO_H
#define __CITY_AUTO_H
#include "define.h"

struct _city {
//--Automatically generated
				int actorid;	//��ɫID
				int index;	//����
				char name[22];	//����
				char type;	//�ǳ�����
				char shape;	//��������(ѡȡ)
				int headid;	//����ͷ��(�Զ���)
				short country;	//ѡ��Ĺ���(��ʵ)
				char ipcountry[3];	//IP��ַ���ڹ���
				char language;	//ѡ������
				char os;	//ϵͳ1ios 2android 3win
				char platid;	//ƽ̨
				int createtime;	//����ʱ��
				int lastlogin;	//�ϴε�½ʱ��
				int lastlogout;	//�ϴεǳ�ʱ��
				char state;	//�ǳص�ǰ״̬
				short posx;	//λ��
				short posy;	//λ��
				int sflag;	//��־λ
				short level;	//��ҵȼ�
				int exp;	//��Ҿ���
				char viplevel;	//VIP�ȼ�
				int vipexp;	//VIP����
				char nation;	//����(κ����)
				char official;	//��ְ
				char place;	//��λ
				char zone;	//����
				int battlepower;	//ս��
				char mokilllv;	//��ɱҰ����߼���
				short body;	//����
				short bodysec;	//�����ָ�ʱ��(ÿ��-1)
				int silver;	//����
				int wood;	//ľ��
				int food;	//����
				int iron;	//����
				unsigned char levynum;	//��ǰ���մ���
				short levysec;	//�´�����ʱ��(ÿ��-1)
				int people;	//�˿�
				int prestige;	//����ֵ
				int friendship;	//�������
				int function;	//�����Ƿ���
				char equip_washnum;	//װ��ϴ����Ѵ���
				short equip_washsec;	//װ���´����ϴ��ʱ��
				short forgingkind;	//����װ������
				int forgingsec;	//����ʣ��ʱ��
				char hero_washnum;	//Ӣ��ϴ������
				short hero_washsec;	//Ӣ���´�ϴ�����ʱ��
				char autobuild;	//�Զ�����ʣ�����
				char autobuildopen;	//�Զ������Ƿ���
				short guardsec;	//��ǽ������ȴʱ��
