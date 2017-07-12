#ifndef _EQUIP_H_
#define _EQUIP_H_
#include "define.h"

#define EQUIP_TYPE_EQUIP1  1	// ����
#define EQUIP_TYPE_EQUIP2  2	// ����
#define EQUIP_TYPE_EQUIP3  3	// ����
#define EQUIP_TYPE_EQUIP4  4	// ͷ��
#define EQUIP_TYPE_EQUIP5  5	// ��ӡ
#define EQUIP_TYPE_EQUIP6  6	// ����
#define EQUIP_TYPE_MAX		6
#define EQUIP_BASEOFFSET		1000	// ����Ӣ�����ϵ�װ������ƫ��

// �������߳ɹ��󷵻صĽṹ
typedef struct _equipout
{
	int m_equip_kind;		// ��Ʒ����
	int m_equip_offset;	// ��Ʒ����λ��
}EquipOut;

// ��offsetת���ɶ�Ӧ�����Խṹ
Equip *actor_equip_getptr( int actor_index, int offset );
Equip *city_equip_getptr( int city_index, int offset );
int equip_load( int actor_index );
int equip_save( int actor_index, FILE *fp );
int equip_maxid_init();

int equip_gettype( short kind );
int equip_insert( int actor_index, int offset ); // ����װ����ʱ����ã�����մ�����װ��
int equip_create( int actor_index, short equipkind, EquipOut *pOut ); // ��Ҵ���װ��
int equip_getequip( int actor_index, int equipkind, char path ); // ��һ��װ��

int equip_up( int actor_index, short herokind, int equip_offset ); // װ����,�����滻Ч��
int equip_down( int actor_index, short herokind, int index ); // ж���ϵ�װ��

int equip_list( int actor_index ); // ����װ���б�
int equip_sendbag( int actor_index, int offset ); // ���±������װ��
int equip_sendhero( int actor_index, Hero *pHero, int index ); // ����Ӣ�۵�װ��
int equip_sendget( int actor_index, int offset, char path );
int equip_sendlost( int actor_index, short equipkind, int offset, char path );
int equip_sendswap( int actor_index, int src_offset, int dest_offset );

int equip_forgingtime( int city_index, short kind );
#endif
