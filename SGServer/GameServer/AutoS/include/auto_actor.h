#ifndef __ACTOR_AUTO_H
#define __ACTOR_AUTO_H
#include "define.h"

struct _actor {
//--Automatically generated
				int actorid;	//角色编号
				int accountid;	//登陆id
				i64 userid;	//账号编号
				char username[51];	//账号名
				short admin;	//管理员级别
				char lastip[16];	//上次登陆ip
				int createtime;	//创建时间
				int forbidtime;	//禁言时间
				int savetime;	//上次保存时间
				unsigned char isexit;	//是否离开游戏中
				short view_areaindex;	//当前视口的地图区域（逻辑）
				char name[22];	//角色名称
				char nation;	//角色国家
				unsigned char shape;	//形象
				short level;	//级别
				short view_zoneid;	//当前视口的地图区域（游戏）
				int city_index;	//城池索引
				int token;	//钻石
				int total_charge;	//总充值
				float charge_dollar;	//总消费多少钱
				unsigned char itemext;	//扩展的背包栏位数
				Item item[300];	//角色携带的道具
				Equip equip[150];	//角色携带的装备
				unsigned char equipext;	//扩展的装备栏位数
				Hero hero[128];	//未上阵英雄
				char quest_complete[2048];	//任务完成情况
				int worldquest_complete;	//世界任务领取情况
				short worldquestid;	//世界任务
				int sflag;	//特定标志位
				int fdate;	//刷新的日子是哪天
				char today_char[128];	//char类型每日次数
				int today_int[8];	//int类型每日次数
				int cd[8];	//通用CD时间
				char config[8];	//玩家配置
				int function;	//功能是否开启
				short story_chapter;	//副本进度章节
				char story_rank;	//副本进度关卡
				char story_state[512];	//副本关卡状态
				char story_ranknum[32];	//副本关卡有次数的存档
				int story_ranktime[32];	//副本关卡有时间的存档
				int view_lastframe;	//上次发送的区域信息时间
				short subscribe_cmd[8];	//订阅的消息ID
				int lastpeople_c;	//上次本城人口
				int lastpeople_n;	//上次国家人口
				int cdkey1;	//是否领取该批次兑换码
				int cdkey2;	//是否领取该批次兑换码
				int cdkey3;	//是否领取该批次兑换码
				int cdkey4;	//是否领取该批次兑换码
				char hv_ln;	//良将寻访次数
				char hv_hn;	//神将寻访次数
				short hv_pro;	//当前寻访进度
				int talkspeed_frame;	//说话延迟
				char cdkeywait;	//CDKEY等待
				short mail_notreadnum;	//未读邮件数量
};
typedef struct _actor Actor;

int actor_load_auto( int actorid, Actor *pActor, const char *pTab );
int actor_save_auto( Actor *pActor, const char *pTab, FILE *fp );

#endif
