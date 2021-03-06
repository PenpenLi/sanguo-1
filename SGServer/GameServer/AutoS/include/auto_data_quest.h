#ifndef __QUEST_DATA_AUTO_H
#define __QUEST_DATA_AUTO_H
#include "define.h"

struct _questinfo {
//--Automatically generated
				int questid;	//
				short type;	//
				short nameid;	//
				int descid;	//
				int nextid;	//
				int unlock_branch[4];	//
				int datatype;	//
				int datakind;	//
				short dataoffset;	//
				int needvalue;	//
				short brushlevel;	//
				short brushnum;	//
				short brushrange;	//
				int awardkind[5];	//
				int awardnum[5];	//
				int trigger_kind[2];	//
				int trigger_num[2];	//
				int trigger_talk;	//
				short guide;	//
};
typedef struct _questinfo QuestInfo;

int questinfo_init_auto();
int questinfo_reload_auto();

#endif
