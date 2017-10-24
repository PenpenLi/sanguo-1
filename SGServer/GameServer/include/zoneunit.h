#ifndef __ZONEUNIT_H_
#define __ZONEUNIT_H_

#define ZONEUNIT_TYPE_CITY			1	// �ǳ�
#define ZONEUNIT_TYPE_ARMY			2	// ����
#define ZONEUNIT_TYPE_TOWN			3	// ����
#define ZONEUNIT_TYPE_ENEMY			4	// ����
#define ZONEUNIT_TYPE_RES			5	// ��Դ
#define ZONEUNIT_TYPE_EVENT			6	// �¼�

// �����ͼ��ʾ��Ԫ
typedef struct _zoneunit
{
	char type;					// ����1=City 2=ARMY 3...
	short lastadd_zoneid;		// �ϴν����������
	int index;					// ���Ͷ�Ӧ����
	int pre_index;				// ǰһ����Ԫ������
	int next_index;				// ��һ����Ԫ������
}ZoneUnit;

int zoneunit_init();

// �������ͺͶ�Ӧ����ȷ����Ԫ����
int zoneunit_getindex( char type, int index );

// ��ȡ��ʾ��Ԫ��Ӧ��������Ϣ
int zoneunit_getattr( int unit_index, SLK_NetS_ZoneUnit *pAttr );

// ��ȡ��ʾ��Ԫ��Ӧ��λ��
int zoneunit_getpos( int unit_index, short *posx, short *posy );

// ����Ҫ��ʾ�ĳǳػ������ӵ���ʾ��Ԫ
int zoneunit_add( char type, int index );

// ���Ѿ������ĵ�ͼ��Ԫɾ����
int zoneunit_del( char type, int index, int unit_index );

// ���µ�ͼ��Ԫ����
int zoneunit_update( char type, int index, int unit_index );

// ��ʾ��Ԫ���������ͼ
int zoneunit_enterworld( int unit_index, short posx, short posy );

#endif
