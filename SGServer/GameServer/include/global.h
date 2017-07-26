#ifndef _GLOBAL_H_
#include "share_memory.h"

// ȫ�ֱ���
typedef struct _global
{
	int actorlevel_max;
	short body_max;
	short body_sec;
	short levy_sec;
	char levy_max;
	int building_delete_cd;
	char equip_wash_max;
	short equip_wash_sec;
	char hero_wash_max;
	short hero_wash_sec;
	char buildinglevel_max;
	short city_guard_sec;
	float city_guard_sec_token;
	short city_guard_up_token;
	short worker_freetime;
	int trainfood;
	short equipext_token;
	int nequip_open_silver;
	int nequip_open_wood;
}Global;
int global_init();
void global_reload();

// �������������������ȫ������
#define WORLD_DATA_LAST_CITYPOSX		1
#define WORLD_DATA_LAST_CITYPOSY		2
#define WORLD_DATA_SAVEFLAG				99		// �浵�ı��ʱ��
#define WORLD_DATA_SAVEFILE_FLAG		100		// ����ִ����ϵı��ʱ��
#define WORLD_DATA_MAX					128		
int world_data_init();
int world_data_get( int index, char *strvalue );
int world_data_set( int index, int value, char *strvalue, FILE *fp );
#endif
