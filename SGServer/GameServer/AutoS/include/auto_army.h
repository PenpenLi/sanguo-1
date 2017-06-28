#ifndef __ARMY_AUTO_H
#define __ARMY_AUTO_H
#include "define.h"

struct _army {
//--Automatically generated
				int index;	//��������
				int id;	//����ΨһID,�Ϸ�����֤
				int unit_index;	//��ʾ����
				char state;	//״̬
				int statetime;	//״̬ʱ���
				int stateduration;	//״̬����������
				int action;	//��Ϊ
				short from_type;	//�����Ķ�������
				int from_id;	//�����Ķ���ID
				int from_index;	//�����Ķ�������
				short from_posx;	//�����Ķ�������
				short from_posy;	//�����Ķ�������
				short to_type;	//Ŀ�Ķ�������
				int to_id;	//Ŀ�Ķ���ID
				int to_index;	//Ŀ�Ķ�������
				short to_posx;	//Ŀ�Ķ�������
				short to_posy;	//Ŀ�Ķ�������
				short posx;	//��ǰ����
				short posy;	//��ǰ����
				short herokind[4];	//�佫
};
typedef struct _army Army;

typedef Army * (*LPCB_GETARMY)( int index );
typedef int (*LPCB_LOADARMY)( int index );
int army_load_auto( LPCB_GETARMY pCB_GetArmy, LPCB_LOADARMY pCB_LoadArmy, const char *pTab );
int army_save_auto( Army *pArmy, const char *pTab, FILE *fp );
int army_batch_save_auto( Army *pArmy, int maxcount,  const char *pTab, FILE *fp );

#endif
