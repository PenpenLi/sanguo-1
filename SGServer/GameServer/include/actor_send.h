#ifndef __ACTOR_SEND_H
#define __ACTOR_SEND_H
#include "define.h"

#define SENDTYPE_ACTOR		0	// �����������
#define SENDTYPE_AREA		1	// ������ǰ�߼�����
#define SENDTYPE_MAP		2	// ������ǰ��ͼ
#define SENDTYPE_ZONE		3	// ������ǰ��Ϸ����
#define SENDTYPE_NATION		4	// ������ǰ����
#define SENDTYPE_WORLD		5	// ������ǰ������

int readtoqueue( int client_index, char *pBuf, int readsize, char stat );
int actor_senddata( int actor_index, char send_type, char *data, int datasize );

#endif
