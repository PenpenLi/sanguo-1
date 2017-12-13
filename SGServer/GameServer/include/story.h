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
#endif
