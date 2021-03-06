
#ifndef __ACTIVITY_H
#define __ACTIVITY_H

#define MAX_ACTIVITY_COUNT					48

#define ACTIVITY_NORMAL						0 
#define ACTIVITY_1	1	//	首充礼包
#define ACTIVITY_2	2	//	主城等级
#define ACTIVITY_3	3	//	攻城略地
#define ACTIVITY_4	4	//	七日狂欢
#define ACTIVITY_5	5	//	七星拜将
#define ACTIVITY_6	6	//	全服返利
#define ACTIVITY_7	7	//	大咖带队
#define ACTIVITY_8	8	//	成长计划
#define ACTIVITY_9	9	//	幸运罗盘
#define ACTIVITY_10	10	//	特价礼包
#define ACTIVITY_11	11	//	出师大宴
#define ACTIVITY_12	12	//	副本掉落
#define ACTIVITY_13	13	//	流寇图纸
#define ACTIVITY_14	14	//	流寇资源
#define ACTIVITY_15	15	//	经验翻倍
#define ACTIVITY_16	16	//	作坊加速
#define ACTIVITY_EVERYDAY_PAY	17	//	每日充值
#define ACTIVITY_18	18	//	镔铁转盘
#define ACTIVITY_19	19	//	采集翻倍
#define ACTIVITY_20	20	//	屯田活动
#define ACTIVITY_21	21	//	国器暴击
#define ACTIVITY_22	22	//	皇城采集
#define ACTIVITY_23	23	//	官员召唤
#define ACTIVITY_24	24	//	募兵翻倍
#define ACTIVITY_25	25	//	消费有礼
#define ACTIVITY_26	26	//	强国策
#define ACTIVITY_27	27	//	西凉暴乱
#define ACTIVITY_28	28	//	黄巾军暴乱
#define ACTIVITY_29	29	//	体力大卖
#define ACTIVITY_30	30	//	图纸活动
#define ACTIVITY_31	31	//	全民寻宝
#define ACTIVITY_32	32	//	抢夺名城
#define ACTIVITY_33	33	//	充值排行
#define ACTIVITY_34	34	//	屯银排行
#define ACTIVITY_35	35	//	屯木排行
#define ACTIVITY_36	36	//	屯粮排行
#define ACTIVITY_37	37	//	屯铁排行
#define ACTIVITY_38	38	//	国战排行
#define ACTIVITY_39	39	//	城战排行
#define ACTIVITY_40	40	//	洗练排行
#define ACTIVITY_41	41	//	建设排行
#define ACTIVITY_42	42	//	锻造排行
#define ACTIVITY_43	43	//	充值排行
#define ACTIVITY_44	44	//	兵力排行

typedef struct _activity_item
{
	int m_activityid;
	int m_warningtime;	// 活动预热时间
	int m_starttime;	// 活动启动时间
	int m_endtime;		// 活动结束时间
	int m_closetime;	// 活动关闭时间，好多活动为了玩家看积分排名什么的，会有最后隐藏时间
	char m_openstat;	// 是否调用过开启函数
	char m_endstat;		// 是否调用过结束函数
}ActivityItem;

int activity_init();
int activity_set( int activityid, int warningtime, int starttime, int endtime, int closetime );
int activity_setendtime( int activityid, int endtime, int closetime );
int activity_force_end( int activityid );
int activity_force_close( int activityid );
int activity_setopenstat( int activityid, int stat );
int activity_setendstat( int activityid, int stat );
int activity_intime( int activityid );
int activity_inclose( int activityid );
int activity_lefttime( int activityid );
int activity_totaltime( int activityid );
int activity_logic();

int activity_onwarning( int activityid, int lefttime );
int activity_onopen( int activityid );
int activity_onend( int activityid );
int activity_onclose( int activityid );
int activity_onlogic( int activityid );

// 活动列表
int activity_sendlist( int actor_index );

// 首充礼包活动
int activity_01_sendinfo( int actor_index );
int activity_01_get( int actor_index );

// 主城等级活动
int activity_02_sendinfo( int actor_index );
int activity_02_get( int actor_index, int id );

// 攻城略地活动
int activity_03_sendinfo( int actor_index );
int activity_03_get( int actor_index, int id );

// 七星拜将活动
int activity_05_sendinfo( int actor_index );
int activity_05_buy( int actor_index, int index );
int activity_05_update( int actor_index );
int activity_05_callhero( int actor_index );

// 全服返利活动
void activity_06_onopen();
void activity_06_onend();
void activity_06_onclose();
int activity_06_sendinfo( int actor_index );
int activity_06_get( int actor_index, int id );

// 成长计划活动
int activity_08_sendinfo( int actor_index );
int activity_08_open( int actor_index );
int activity_08_get( int actor_index, int id );

// 特价礼包
int activity_10_init();

// 出师大宴活动
int activity_11_sendinfo( int actor_index );
int activity_11_get( int actor_index );
#endif
