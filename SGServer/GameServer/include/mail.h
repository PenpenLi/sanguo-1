#ifndef _MAIL_H_ 
#define _MAIL_H_
#include "define.h"

#define MAX_MAIL_SAVETIME			86400*7		// �ʼ�����ʱ��7��
#define MAIL_TITLE_MAXSIZE			64			// �ʼ����ⳤ��
#define MAIL_CONTENT_MAXSIZE		1024		// �ʼ���Ϣ����
#define MAIL_ATTACH_MAXSIZE			256			// �ʼ���������
#define MAIL_ACTORID				-2			//

// �ʼ�����
#define MAIL_TYPE_SYSTEM		0	// ϵͳ��Ϣ�ʼ�
#define MAIL_TYPE_NOTIFY		1	// �����ʼ��������ⲿhttp��������ȡ
#define MAIL_TYPE_FIGHT_ENEMY	10	// ����
#define MAIL_TYPE_FIGHT_CITY	11	// ��ս
#define MAIL_TYPE_FIGHT_NATION	12	// ��ս

#define TAG_TEXTID			"#$"// ���--���Ϊ���ֱ�id
#define TAG_ITEMKIND		"$$"// ���--���Ϊ����װ��ר��
#define TAG_POS				"$#"// ���--���Ϊ����

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
int mail_readed( int actor_index, i64 mailid );

// ɾ���ʼ�
int mail_delete( i64 mailid );

// δ���ʼ�����
int mail_noread_check( int actor_index );

// ��ȡ�ʼ��б�
int mail_getlist( int actor_index, int op, i64 min, i64 max );

// ��ȡ����
int mail_attachget( int actor_index, i64 mailid );
#endif
