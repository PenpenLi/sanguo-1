#ifndef _ACTOR_TIMES_H_
#define _ACTOR_TIMES_H_

// 32λ��������־λ����0��1 ��ʾ��û������û�У���û�������ô浵��
#define ACTOR_SFLAG_BODY_FREEBUY	0	// �״ι����������
void actor_set_sflag( int actor_index, int offset, char value );
int actor_get_sflag( int actor_index, int offset );

// char ���͵�ÿ�����ݣ�ÿ����£�
#define MAX_TODAY_COUNT		127
#define TODAY_CHAR_BUYBODY		0 // ���칺����������
int actor_get_today_char_times( int actor_index, int offset );
int actor_add_today_char_times( int actor_index, int offset );
int actor_set_today_char_times( int actor_index, int offset, char value );

// int ���͵�ÿ�����ݣ�ÿ����£�
#define MAX_TODAY_INTNUM	8
int actor_get_today_int_times( int actor_index, int offset );
int actor_add_today_int_times( int actor_index, int offset );
int actor_set_today_int_times( int actor_index, int offset, int value );

// CDʱ��
#define USELIMIT_CD_MAXCOUNT 8
int actor_set_uselimit_cd( int actor_index, char index, int cdtime );
int actor_add_uselimit_cd( int actor_index, char index, int cdtime );
int actor_check_uselimit_cd( int actor_index, char index );
int actor_clear_uselimit_cd( int actor_index, char index );

#endif
