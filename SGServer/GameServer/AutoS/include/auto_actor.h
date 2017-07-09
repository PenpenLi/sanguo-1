#ifndef __ACTOR_AUTO_H
#define __ACTOR_AUTO_H
#include "define.h"

struct _actor {
//--Automatically generated
				int actorid;	//��ɫ���
				int accountid;	//��½id
				i64 userid;	//�˺ű��
				char username[51];	//�˺���
				short admin;	//����Ա����
				char lastip[16];	//�ϴε�½ip
				int createtime;	//����ʱ��
				int forbidtime;	//����ʱ��
				int savetime;	//�ϴα���ʱ��
				unsigned char isexit;	//�Ƿ��뿪��Ϸ��
				short view_areaindex;	//��ǰ�ӿڵĵ�ͼ����
				char name[22];	//��ɫ����
				char nation;	//��ɫ����
				unsigned char shape;	//����
				short level;	//����
				int city_index;	//�ǳ�����
				int token;	//��ʯ
				int total_charge;	//�ܳ�ֵ
				float charge_dollar;	//�����Ѷ���Ǯ
				unsigned char itemext;	//��չ�ı�����λ��
				Item item[300];	//��ɫЯ���ĵ���
				Equip equip[150];	//��ɫЯ����װ��
				unsigned char equipext;	//��չ��װ����λ��
				Hero hero[128];	//δ����Ӣ��
				int sflag;	//�ض���־λ
				int fdate;	//ˢ�µ�����������
				char today_char[128];	//char����ÿ�մ���
				int today_int[8];	//int����ÿ�մ���
				int cd[8];	//ͨ��CDʱ��
				char config[8];	//�������
				int function;	//�����Ƿ���
				int view_lastframe;	//�ϴη��͵�������Ϣʱ��
				short subscribe_cmd[8];	//���ĵ���ϢID
				int cdkey1;	//�Ƿ���ȡ�����ζһ���
				int cdkey2;	//�Ƿ���ȡ�����ζһ���
				int cdkey3;	//�Ƿ���ȡ�����ζһ���
				int cdkey4;	//�Ƿ���ȡ�����ζһ���
				int talkspeed_frame;	//˵���ӳ�
				char cdkeywait;	//CDKEY�ȴ�
};
typedef struct _actor Actor;

int actor_load_auto( int actorid, Actor *pActor, char *pTab );
int actor_save_auto( Actor *pActor, char *pTab, FILE *fp );

#endif
