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
				short view_areaindex;	//��ǰ�ӿڵĵ�ͼ�����߼���
				char name[22];	//��ɫ����
				char nation;	//��ɫ����
				unsigned char shape;	//����
				short level;	//����
				short view_zoneid;	//��ǰ�ӿڵĵ�ͼ������Ϸ��
				int city_index;	//�ǳ�����
				int token;	//��ʯ
				int total_charge;	//�ܳ�ֵ
				float charge_dollar;	//�����Ѷ���Ǯ
				unsigned char itemext;	//��չ�ı�����λ��
				Item item[300];	//��ɫЯ���ĵ���
				Equip equip[150];	//��ɫЯ����װ��
				unsigned char equipext;	//��չ��װ����λ��
				Hero hero[128];	//δ����Ӣ��
				char quest_complete[2048];	//����������
				int sflag;	//�ض���־λ
				int fdate;	//ˢ�µ�����������
				char today_char[128];	//char����ÿ�մ���
				int today_int[8];	//int����ÿ�մ���
				int cd[8];	//ͨ��CDʱ��
				char config[8];	//�������
				int function;	//�����Ƿ���
				short story_chapter;	//���������½�
				char story_rank;	//�������ȹؿ�
				char story_state[512];	//�����ؿ�״̬
				char story_ranknum[32];	//�����ؿ��д����Ĵ浵
				int story_ranktime[32];	//�����ؿ���ʱ��Ĵ浵
				int view_lastframe;	//�ϴη��͵�������Ϣʱ��
				short subscribe_cmd[8];	//���ĵ���ϢID
				int lastpeople_c;	//�ϴα����˿�
				int lastpeople_n;	//�ϴι����˿�
				int cdkey1;	//�Ƿ���ȡ�����ζһ���
				int cdkey2;	//�Ƿ���ȡ�����ζһ���
				int cdkey3;	//�Ƿ���ȡ�����ζһ���
				int cdkey4;	//�Ƿ���ȡ�����ζһ���
				int talkspeed_frame;	//˵���ӳ�
				char cdkeywait;	//CDKEY�ȴ�
				short mail_notreadnum;	//δ���ʼ�����
};
typedef struct _actor Actor;

int actor_load_auto( int actorid, Actor *pActor, const char *pTab );
int actor_save_auto( Actor *pActor, const char *pTab, FILE *fp );

#endif
