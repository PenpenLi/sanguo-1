#ifndef _WORLD_QUEST_H_
#define _WORLD_QUEST_H_
#include "define.h"

#define WORLDQUEST_ID1	1	//	��ɱ����5��
#define WORLDQUEST_ID2	2	//	��ɱ����10��
#define WORLDQUEST_ID3	3	//	��ɱ����30��
#define WORLDQUEST_ID4	4	//	����Ӫ��
#define WORLDQUEST_ID5	5	//	���˿���
#define WORLDQUEST_ID6	6	//	���˿���
#define WORLDQUEST_WORLDBOSS1	7	//	����boss �Ž�
#define WORLDQUEST_ID8	8	//	�����ݿ�
#define WORLDQUEST_ID9	9	//	�����ݳ�
#define WORLDQUEST_WORLDBOSS2	10	//	����boss ��׿
#define WORLDQUEST_ID11	11	//	�ʳ�Ѫս����

int worldquest_init();
int worldquest_reload();
int worldquest_give( int actor_index );
int worldquest_addvalue( int questid, int value );
int worldquest_setvalue( int questid, int value );
int worldquest_setcomplete( int actor_index, int questid );
int worldquest_getcomplete( int actor_index, int questid, int *value );
int worldquest_check( int actor_index, int questid, int *value );
int worldquest_checkcomplete( int actor_index, char type );
int worldquest_sendinfo( int actor_index );
int worldquest_sendaward( int actor_index, int questid );
int worldquest_getaward( int actor_index, int questid );
#endif
