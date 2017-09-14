#ifndef _MAIL_H_ 
#define _MAIL_H_
#include "define.h"

#define MAX_MAIL_SAVETIME			86400*7		// �ʼ�����ʱ��7��
#define MAIL_TITLE_MAXSIZE			128			// �ʼ����ⳤ��
#define MAIL_CONTENT_MAXSIZE		1024		// �ʼ���Ϣ����
#define MAIL_ATTACH_MAXSIZE			256			// �ʼ���������
#define MAIL_ACTORID				-2			//
#define MAIL_SEARCHCACHE_MAX		128			// �ʼ�������

// �ʼ�����
#define MAIL_TYPE_SYSTEM			0	// ϵͳ��Ϣ�ʼ�
#define MAIL_TYPE_NOTIFY			1	// �����ʼ��������ⲿhttp��������ȡ
#define MAIL_TYPE_ACTOR_SEND		2	// ��ҷ����ʼ�
#define MAIL_TYPE_ACTOR_REPLY		3	// ��һظ��ʼ�
#define MAIL_TYPE_FIGHT_ENEMY		10	// ����
#define MAIL_TYPE_FIGHT_CITY		11	// ��ս
#define MAIL_TYPE_FIGHT_NATION		12	// ��ս
#define MAIL_TYPE_CITY_SPY			13	// ���
#define MAIL_TYPE_CITY_BESPY		14	// �����
#define MAIL_TYPE_GATHER			20	// �ɼ�


#define TAG_TEXTID			"#$"// ���--���Ϊ���ֱ�id
#define TAG_ITEMKIND		"$$"// ���--���Ϊ����װ��ר��
#define TAG_POS				"$#"// ���--���Ϊ����

typedef struct _mailfight_searchcache
{
	i64 m_mailid;
	char m_content[8192];
}MailFightSearchCache;

// �����ʼ�
i64 mail( int actor_index, int actorid, char type, char *title, char *content, char *attach, i64 fightid );
i64 mail_system( int actor_index, int actorid, int titleid, int contentid, char *attach );
i64 mail_system( int actor_index, int actorid, int titleid, int contentid, AwardGetInfo *getinfo );
i64 mail_system( int actor_index, int actorid, int titleid, int contentid, int awardgroup );

// ս�������ʼ�
int mail_fight( i64 mailid, int actorid, char *json );

// ƴ����
i64 mail_maketitle( int titleid, char *v1, char *v2, char *v3, char *v4 );

// ƴ����
i64 mail_makecontent( int contentid, char *v1, char *v2, char *v3, char *v4 );

// ��ȡս����ϸ����
int mail_fight_read( int actor_index, i64 mailid );

// ����ս����ϸ����
int mail_fight_send( int actor_index, i64 mailid, char *content );

// �����Ѷ�״̬
int mail_readed( int actor_index, i64 mailid );

// ����ȫ���Ѷ�״̬
int mail_readed_all( int actor_index );

// ɾ���ʼ�
int mail_delete( i64 mailid );

// ɾ���ʼ�
int mail_delete_actor( int actor_index, i64 mailid );

// ����ɾ���ʼ�
int mail_delete_all( int actor_index, SLK_NetC_MailAllDel *pValue );

// ��������״̬
int mail_locked( int actor_index, i64 mailid );

// ���ý������״̬
int mail_unlocked( int actor_index, i64 mailid );

// ��ȡδ���ʼ�����
int mail_noread_check( int actor_index );

// ����δ���ʼ�����
int mail_noread_send( int actor_index );

// ��ȡ�ʼ��б�
int mail_getlist( int actor_index, int op, i64 min, i64 max );

// ��ȡ����
int mail_attachget( int actor_index, i64 mailid );

// �����ʼ�
int mail_share( int actor_index, SLK_NetS_MailShare *pValue );

// ��ҵ��������ʼ���ȡ����
int mail_share_getcontent( int actor_index, i64 mailid );

// ��ҵ��������ʼ���ȡ����
int mail_share_getfightcontent( int actor_index, i64 mailid );

// ��Ҽ��ʼ�����
int mail_actor_send( int actor_index, SLK_NetC_MailSend *pValue );

// ��Ҽ��ʼ��ظ�
int mail_actor_reply( int actor_index, SLK_NetC_MailReply *pValue );
#endif
