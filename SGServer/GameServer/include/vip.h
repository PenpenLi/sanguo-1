#ifndef _VIP_H_
#define _VIP_H_
#include "define.h"

// ����VIP�ȼ�
int vip_calclevel( int city_index );

// VIP��������ֵ
int vip_expmax_get( int level );

// ����VIP����
int vip_exp( int city_index, int value, short path );

// �����������
int vip_attr_buildfree( City *pCity );

// �����������
int vip_attr_bodybuy( City *pCity );

// �Զ��������
int vip_attr_autobuild( City *pCity );

// ÿ������о��ٻش���
int vip_attr_marchcall( City *pCity );

// ����ټ���ļ��
int vip_attr_train( City *pCity );

// VIP���
int vipbag_list( int actor_index );
int vipbag_buy( int actor_index, int level );

// VIP�ؼ��̵�
int vipshop_list( int actor_index );
int vipshop_buy( int actor_index, int id, int awardkind );
int vipshop_set_useitembuy( int actor_index, int close );
#endif
