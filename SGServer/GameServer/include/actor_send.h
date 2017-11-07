#ifndef __ACTOR_SEND_H
#define __ACTOR_SEND_H
#include "define.h"

#define SENDTYPE_ACTOR		0	// �����������
#define SENDTYPE_AREA		1	// ������ǰ�߼�����
#define SENDTYPE_WORLDMAP	2	// ������ǰҰ���ͼ
#define SENDTYPE_ZONE		3	// ������ǰ��Ϸ����
#define SENDTYPE_WORLD		4	// ������ǰ������
#define SENDTYPE_INZONE		5	// ������ǰ��Ϸ����(��ǰ��ͼ���������)
#define SENDTYPE_SUBSCRIBE	6	// ����������

#define SENDTYPE_NATION		10	// 
#define SENDTYPE_NATION1	11	// ���͸�κ��
#define SENDTYPE_NATION2	12	// ���͸����
#define SENDTYPE_NATION3	13	// ���͸����

#define SENDTYPE_WORLDMAP_NATION	15	// 
#define SENDTYPE_WORLDMAP_NATION1	16	// ���͸�κ��(��Ұ������)
#define SENDTYPE_WORLDMAP_NATION2	17	// ���͸����(��Ұ������)
#define SENDTYPE_WORLDMAP_NATION3	18	// ���͸����(��Ұ������)

int readtoqueue( int client_index, char *pBuf, int readsize, char stat );
int actor_senddata( int actor_index, char send_type, char *data, int datasize );

#endif
