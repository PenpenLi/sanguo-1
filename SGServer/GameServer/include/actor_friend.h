#ifndef _ACTOR_FRIEND_H_
#define _ACTOR_FRIEND_H_
#include "define.h"
#define ACTOR_FRIEND_MAXCOUNT		100 // ��������
#define ACTOR_STUDENT_MAXCOUNT		30  // ͽ������

#define ACTOR_FRIEND_EVENT_ASK			1	// �Է����������Ϊ����
#define ACTOR_FRIEND_EVENT_AGREE		2	// �Է�ͬ�������Ϊ����
#define ACTOR_FRIEND_EVENT_REJECT		3	// �Է��ܾ������Ϊ����
#define ACTOR_FRIEND_EVENT_DEL			4	// �Է�ɾ����

// ���ѽṹָ��
ActorFriend *actor_friend_getptr( int actor_index, int offset );

// ��������¼�
int actor_friend_addevent( int event, int actorid, int target_actorid );

// ��ȡ���������¼�
int actor_friend_loadevent( int actor_index );

// �����¼�����
int actor_friend_enevt( int actor_index, int event, int target_actorid );

// ����Ӻ���
int actor_friend_ask( int actor_index, int target_actorid, const char *target_name );

// ͬ����Ӻ���
int actor_friend_agree( int actor_index, int target_actorid, int target_city_index );

// �ܾ���Ӻ���
int actor_friend_reject( int actor_index, int target_actorid, int target_city_index );

// ɾ������
int actor_friend_delete( int actor_index, int target_actorid, int target_city_index );
int actor_friend_delete_db( int actorid, int target_actorid );
// �����б�
int actor_friend_sendlist( int actor_index );


// ʦͽ
// ͽ���б�
int actor_student_sendlist( int actor_index );

// ��ʦ
int actor_take_teacher( int actor_index, int teacher_actorid );

#endif // !_ACTOR_FRIEND_H_
