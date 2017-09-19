#ifndef _ARMY_GROUP_H_
#define _ARMY_GROUP_H_
#include "define.h"

#define ARMYGROUP_MAXCOUNT			128	// �����128�˼���

#define ARMYGROUP_STATE_IDLE		0	// ����
#define ARMYGROUP_STATE_ING			1	// ������


int armygroup_load();
int armygroup_save( FILE *fp );
ArmyGroup *armygroup_getptr( int group_index );

int armygroup_create( char from_type, int from_id, char to_type, int to_id, int stateduration );
void armygroup_delete( int group_index );
void armygroup_alllogic();
void armygroup_logic( int group_index );
#endif
