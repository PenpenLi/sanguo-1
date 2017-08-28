#ifndef _AWARD_H_
#define _AWARD_H_

// -1~ ������ı��
#define AWARDKIND_ITEMBASE		0	  // ���ߣ�0+���߱�ţ�
#define AWARDKIND_EQUIPBASE		10000 // װ����10000+װ����ţ�
#define AWARDKIND_HEROBASE		20000 // Ӣ�ۣ�20000+Ӣ�۱�ţ�
#define AWARDKIND_BUILDINGBASE	30000 // ������30000+������ţ�
#define AWARDKIND_FUNCTION		40000 // ���ܣ�40000+���ܱ�ţ�
#define AWARDKIND_VALUEBASE		50000 // ��ֵ
#define AWARDKIND_SILVER		50001 // ����
#define AWARDKIND_WOOD			50002 // ľ��
#define AWARDKIND_FOOD			50003 // ��ʳ
#define AWARDKIND_IRON			50004 // ����
#define AWARDKIND_TOKEN			50005 // Ԫ��
#define AWARDKIND_BODY			50006 // ����
#define AWARDKIND_INFANTRY		50007 // ����
#define AWARDKIND_CAVALRY		50008 // ���
#define AWARDKIND_ARCHER		50009 // ����
#define AWARDKIND_EXP			50010 // ��ɫ����
#define AWARDKIND_VIPEXP		50011 // VIP����
#define AWARDKIND_AUTOBUILD		50012 // �Զ��������
#define AWARDKIND_LEVYNUM		50013 // ���մ���
#define AWARDKIND_PEOPLE		50014 // �˿�
#define AWARDKIND_PRESTIGE		50015 // ����ֵ
#define AWARDKIND_FRIENDSHIP	50016 // �������

// ��������µĸ�������
#define AWARDKIND_OTHERBASE	100000
#define AWARDKIND_QUEST_SUCCESS	AWARDKIND_OTHERBASE+1	// �������

#define AWARDGETINFO_MAXCOUNT	24

// ������(�����Ϊ�����)
typedef struct _award_group
{
	int *kind;			// ����
	int *minnum;		// ��������
	int *maxnum;		// ��������
	int *value;			// ����ֵ
	char *color;		// ��ɫ
	char *show;			// ��ʾ��ʾ
	short allcount;		// ���齱����Ʒ����
	int allvalue;		// ���齱��������ֵ
	short *type;        // ����
	int *appendnum;     // ����ֵ
}AwardGroup;

// ��ȡ���صĽ���
typedef struct _award_get_info
{
	int kind[AWARDGETINFO_MAXCOUNT];
	int num[AWARDGETINFO_MAXCOUNT];
	char color[AWARDGETINFO_MAXCOUNT];
	short count;
}AwardGetInfo;

// ��ʼ��
int awardgroup_init();

// �ض�
int awardgroup_reload();

// ���͸��ͻ�����ʾ�Ľ�����
int awardgroup_sendinfo( int actor_index, int awardgroup, int callback_code, int unit_index, int limitcount );

// ��������飬��ֱ�Ӹ�
int awardgroup_random( int awardgroup, int level, AwardGetInfo *getinfo );

// ������ ���ŵ��ʼ���������
int awardgroup_mail( int awardgroup, int level, char * itemContent );

// ��������飬ͨ��������Ĭ���������
int awardgroup_withindex( int actor_index, int awardgroup, int level, char path, AwardGetInfo *getinfo );

// ��������飬ͨ�����id����ȷ���Ƿ�����
int awardgroup_withid( int actorid, int awardgroup, char path, AwardGetInfo *getinfo );

// ������
int award_getaward( int actor_index, int kind, int num, char color, char path, AwardGetInfo *getinfo );

// ���߽�������
int gift( int actorid, int kind1, int num1, char color1, int kind2, int num2, char color2, int kind3, int num3, char color3, int kind4, int num4, char color4, unsigned char path );
int gift_check( int actor_index );

// ���߽������֣�����uid��
int gift_uid_check( int actor_index );

// ���߻�ȡ�������uid��
int gift_uid_get( int actor_index );

// �����
int awardgroup_randnum( int awardgroup, int level, int index );


#endif
