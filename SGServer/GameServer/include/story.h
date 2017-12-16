#ifndef _STORY_H_
#define _STORY_H_
#include "define.h"

#define STORY_TYPE_NORMAL	1	// ��ͨ
#define STORY_TYPE_BOSS		2	// ��Ӣ
#define STORY_TYPE_RES		3	// ��Դ
#define STORY_TYPE_ITEM		4	// ����
#define STORY_TYPE_HERO		5	// �佫��ļ
#define STORY_TYPE_DRAWING	6	// װ��ͼֽ

#define STORY_STAR_OFFSETMAX		128	// ��Ӣ�����Ǽ�
#define STORY_HERO_OFFSETMAX		32	// ��ļ����
#define STORY_RESTIME_OFFSETMAX		32	// ��Դ����ʱ��
#define STORY_RESNUM_OFFSETMAX		32	// ��Դ��������
#define STORY_RESRESET_OFFSETMAX	32	// ��Դ�������ô���
#define STORY_ITEMNUM_OFFSETMAX		64	// ���߸����������
#define STORY_DRAWING_OFFSETMAX		16	// װ��ͼֽ�����Ƿ���

int story_sendinfo( int actor_index );
int story_sendrank( int actor_index, int id );
int story_battle( int actor_index, SLK_NetC_StoryBattle *pValue );
// ���¸���״̬
int story_sendrankstate( int actor_index, int id, int savetype, int saveoffset );
// ��Դ��������
int story_res_get( int actor_index, int id );
// ��Դ��������
int story_res_reset( int actor_index, int id );
// ��ļ���������ļ
int story_hero_free( int actor_index, int id );
// ��ļ������Ǯ��ļ
int story_hero_token( int actor_index, int id );
// ͼֽ��������
int story_drawing_buy( int actor_index, int id );
// ͼֽ��������
int story_drawing_get( int actor_index, int id );

// ����ɨ��
int story_sweep( int actor_index, int id, int herokind0, int herokind1, int herokind2, int herokind3 );
#endif
