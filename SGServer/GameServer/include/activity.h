
#ifndef __ACTIVITY_H
#define __ACTIVITY_H

#define MAX_ACTIVITY_COUNT					64

#define ACTIVITY_NORMAL						0 

#define ACTIVITY_1	1	//	�׳����
#define ACTIVITY_2	2	//	���ǵȼ�
#define ACTIVITY_3	3	//	�����Ե�
#define ACTIVITY_4	4	//	���տ�
#define ACTIVITY_5	5	//	���ǰݽ�
#define ACTIVITY_6	6	//	ȫ������
#define ACTIVITY_7	7	//	�󿧴���
#define ACTIVITY_8	8	//	�ɳ��ƻ�
#define ACTIVITY_9	9	//	��������
#define ACTIVITY_PAYBAG	10	//	�ؼ����
#define ACTIVITY_11	11	//	��ʦ����
#define ACTIVITY_12	12	//	��������
#define ACTIVITY_13	13	//	����ͼֽ
#define ACTIVITY_14	14	//	������Դ
#define ACTIVITY_15	15	//	���鷭��
#define ACTIVITY_16	16	//	��������
#define ACTIVITY_EVERYDAY_PAY	17	//	ÿ�ճ�ֵ
#define ACTIVITY_18	18	//	����ת��
#define ACTIVITY_19	19	//	�ɼ�����
#define ACTIVITY_20	20	//	����
#define ACTIVITY_21	21	//	��������
#define ACTIVITY_22	22	//	�ʳǲɼ�
#define ACTIVITY_23	23	//	��Ա�ٻ�
#define ACTIVITY_24	24	//	ļ������
#define ACTIVITY_25	25	//	��������
#define ACTIVITY_26	26	//	ǿ����
#define ACTIVITY_27	27	//	��������
#define ACTIVITY_28	28	//	�ƽ������
#define ACTIVITY_29	29	//	��������
#define ACTIVITY_30	30	//	ͼֽ�
#define ACTIVITY_31	31	//	ȫ��Ѱ��
#define ACTIVITY_32	32	//	��������
#define ACTIVITY_33	33	//	��ֵ����
#define ACTIVITY_34	34	//	��������
#define ACTIVITY_35	35	//	��ľ����
#define ACTIVITY_36	36	//	��������
#define ACTIVITY_37	37	//	��������
#define ACTIVITY_38	38	//	��ս����
#define ACTIVITY_39	39	//	��ս����
#define ACTIVITY_40	40	//	ϴ������
#define ACTIVITY_41	41	//	��������
#define ACTIVITY_42	42	//	��������
#define ACTIVITY_43	43	//	��ֵ����
#define ACTIVITY_44	44	//	��������

typedef struct _activity_item
{
	int m_activityid;
	int m_starttime;	// �����ʱ��
	int m_endtime;		// �����ʱ��
	int m_closetime;	// ��ر�ʱ�䣬�ö�Ϊ����ҿ���������ʲô�ģ������������ʱ��
	int m_nexttime;		// �´ο���ʱ��
	int m_value[4];
	char m_strvalue[256];
	char m_openstat;
	char m_endstat;
}ActivityItem;

int activity_init();
int activity_logic();
int activity_onwarning( int activityid, int surplus );
int activity_onopen( int activityid );
int activity_onend( int activityid );
int activity_onclose( int activityid );
int activity_onlogic( int activityid );

// ��û����ʱ��
int activity_starttime( int activityid );

// �����ʱ��
int activity_endtime( int activityid );

// ��ر�ʱ��
int activity_closetime( int activityid );

// ��ûʣ��ʱ��
int activity_lefttime( int activityid );

// ��ûӦ�ó���ʱ��
int activity_totaltime( int activityid );

int activity_intime( int activityid );
int activity_inclose( int activityid );
int activity_settime( int activityid, int begin_min, int len_min, int value0, int value1, int value2, int value3, char *pstr );
int activity_setendtime( int activityid, int endtime );
int activity_getdata( int activityid, int *value, char *pstr );
int activity_setdata( int activityid, int value0, int value1, int value2, int value3, char* pstr );
int activity_getvalue( int activityid, int index );
int activity_setopenstat( int activityid, int stat );
int activity_setendstat( int activityid, int stat );
int activity_countdown( int activityid );

// ��б�
int activity_sendlist( int actor_index );

// �����Եػ
int activity_03_sendinfo( int actor_index );
int activity_03_get( int actor_index, int id );

// �ɳ��ƻ��
int activity_08_sendinfo( int actor_index );
int activity_08_open( int actor_index );
int activity_08_get( int actor_index, int id );

// ��ʦ����
int activity_body_sendinfo( int actor_index );
int activity_body_get( int actor_index );
#endif
