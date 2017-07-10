#ifndef _CITY_H_
#define _CITY_H_
#include "define.h"

#define CITY_QUEST_MAX				6	// ��������
#define CITY_TECH_MAX				40	// �ǳؿƼ�
#define CITY_DATA_RECORD_MAX		16	// ���ݼ�¼

// �������
#define	CITY_FUNCTION_SMITHY		0	// ������
#define	CITY_FUNCTION_WASH			1	// ϴ����
#define	CITY_FUNCTION_FANGSHI		2	// ����
#define	CITY_FUNCTION_SHOP			3	// �̵�
#define	CITY_FUNCTION_HERO			4	// ���͹�
#define	CITY_FUNCTION_WISHING		5	// �۱���

// �ǳ���������
typedef enum
{
	CityLairdType_Player = 0,		//	��ҵĳǳ�
	CityLairdType_Robot = 2,		//  �����˳ǳ�
}CityLairdType;

// ������������ȡ���гǳ���Ϣ���ڴ�
int city_load();

// �������رգ����гǳ���Ϣ�浽���ݿ�
int city_save( FILE *fp );
int city_single_save( City *pCity, FILE *fp );

// ��ȡ����ǳ�����
City *city_indexptr( int city_index );

// ��ȡ�����ҵĳǳ�����
City *city_getptr( int actor_index );

// ��ȡ����ǳ�����
City *city_getptr_withactorid( int actorid );

// �������id�ҵ��ǳ�����
int city_getindex_withactorid( int actorid );

// ����һ���³ǳ�
int city_new( City *pCity );

// ���г���ÿ����߼�
void city_logic_sec();

// �������ǵȼ�
int city_mainlevel( int city_index );

// 32λ��������־λ����0��1 ��ʾ��û������û�У���û�������ô浵��
void city_set_sflag( City *pCity, int offset, char value );
int city_get_sflag( City *pCity, int offset );

// ���ܻ�ȡ
void city_function_open( City *pCity, int offset );
int city_function_check( City *pCity, int offset );

// ���Ǿ�������
int city_actorexp( int city_index, int exp, char path );
int city_actorupgrade( int city_index, char path, AwardGetInfo *getinfo );

// ����
int city_changebody( int city_index, int value, short path );
// ���մ���
int city_changelevy( int city_index, int value, short path );
// ����
int city_changesilver( int city_index, int value, short path );
// ľ��
int city_changewood( int city_index, int value, short path );
// ����
int city_changefood( int city_index, int value, short path );
// ����
int city_changeiron( int city_index, int value, short path );
// �˿�
int city_changepeople( int city_index, int value, short path );
// ����ֵ
int city_changeprestige( int city_index, int value, short path );
// �������
int city_changefriendship( int city_index, int value, short path );

#endif
