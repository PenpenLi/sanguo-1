#ifndef _MAIL_H_ 
#define _MAIL_H_

#define MAX_MAIL_SAVETIME			86400*7		// �ʼ�����ʱ��7��
#define MAIL_TITLE_MAXSIZE			128			// �ʼ����ⳤ��
#define MAIL_CONTENT_MAXSIZE		2048		// �ʼ���Ϣ����
#define MAIL_ATTACH_MAXSIZE			256			// �ʼ���������
#define MAIL_ACTORID				-2			//

// �ʼ�����
#define MAIL_TYPE_SYSTEM	0	// ϵͳ��Ϣ�ʼ�
#define MAIL_TYPE_NOTIFY	1	// �����ʼ��������ⲿhttp��������ȡ
#define MAIL_TYPE_FIGHT		2	// ս�������ʼ�
#define MAIL_TYPE_SPY		3	// ��鱨���ʼ�
#define MAIL_TYPE_GATHER	4	// �ɼ������ʼ�

// ��ȡ�ʼ�;��
#define MAIL_PATH_NORMAL		0
#define MAIL_PATH_EVERYDAY		1	// ÿ�յ�¼
#define MAIL_PATH_FIGHT_MONSTER	2	// ����
#define MAIL_PATH_FIGHT_CITY	3	// ��ս
#define MAIL_PATH_FIGHT_NATION	4	// ��ս

// {\"textid\":\"10001\", \"vlist\":[]}
// 

// �����ʼ�
i64 mail( int actor_index, int actorid, char type, char *title, char *content, char *attach, i64 fightid );

// ƴ����
i64 mail_maktitle( int titleid, char *v1, char *v2, char *v3, char *v4 );

// ƴ����
i64 mail_makcontent( int contentid, char *v1, char *v2, char *v3, char *v4 );

// ��ȡ��ϸ����
int mail_read_content( int actor_index, i64 mailid );

// �����Ѷ�״̬
int mail_readed( i64 mailid );

// ɾ���ʼ�
int mail_delete( i64 mailid );

// δ���ʼ�����
int mail_noread_check( int actor_index );
#endif
