#ifndef _ITEM_H_
#define _ITEM_H_
#include "auto_actor_item.h"

#define ITEM_ABILITY_NUM	4	// 玩家道具动态属性个数
#define ITEM_EXCHANGE_NUM	5	// 道具兑换材料个数

/* 物品颜色 */
#define ITEM_COLOR_LEVEL_WHITE	0 // 白色
#define ITEM_COLOR_LEVEL_BLUE	1 // 蓝色
#define ITEM_COLOR_LEVEL_GREEN	2 // 绿色
#define ITEM_COLOR_LEVEL_GOLD	3 // 金色
#define ITEM_COLOR_LEVEL_RED	4 // 红色
#define ITEM_COLOR_LEVEL_PURPLE	5 // 紫色


#define ITEM_COLOR_LEVEL_MAX	6 // 最大颜色数量


/* 物品类型 */
#define ITEM_TYPE_NORMAL_USE		1	// 点击类道具（主动使用）
#define ITEM_TYPE_SCRIPT_USE		2	// 脚本使用类道具
#define	ITEM_TYPE_EQUIP_MATERIAL	3	// 装备材料
#define	ITEM_TYPE_EQUIP_DRAWING		4	// 装备图纸
#define	ITEM_TYPE_ACTIVITY			5	// 活动类（无点击按钮，被动使用）
#define	ITEM_TYPE_AUTO				6	// 自动使用类
#define	ITEM_TYPE_HEROEXP			7	// 武将经验
#define ITEM_TYPE_QUICK				8	// 加速类道具（城内）

/* 动态属性 */
#define ITEM_ABILITY_NONE					0
#define ITEM_ABILITY_AWARDGROUP		1	// 掉落包
#define ITEM_ABILITY_SCRIPTID		2	// 脚本调用ID
#define ITEM_ABILITY_ADDBODY		3	// 加体力
#define ITEM_ABILITY_ADDEXP			4	// 加主公经验
#define ITEM_ABILITY_ADDHEROEXP		5	// 加英雄经验
#define ITEM_ABILITY_AWARDID		6	// 奖励id
#define ITEM_ABILITY_CITYRES_SILVER 11	// 银币数量
#define ITEM_ABILITY_CITYRES_WOOD	12	// 木材数量
#define ITEM_ABILITY_CITYRES_FOOD	13	// 粮食数量
#define ITEM_ABILITY_CITYRES_IRON	14	// 铁数量
#define ITEM_ABILITY_BUFF			15	// buff
#define ITEM_ABILITY_CITYMOVE		16	// 低级迁城
#define ITEM_ABILITY_CORPS1			17	// 加步兵
#define ITEM_ABILITY_CORPS2			18	// 加骑兵
#define ITEM_ABILITY_CORPS3			19	// 加弓兵
#define ITEM_ABILITY_VIPEXP			20	// VIP点数
#define ITEM_ABILITY_GIRLTYPE		21	// 女将类型
#define ITEM_ABILITY_GIRLLOVEEXP	22	// 女将亲昵度

/* 道具操作 */ 
#define ITEM_PROCESS_INFO		1 // 获取道具信息
#define ITEM_PROCESS_USE		2 // 使用道具
#define ITEM_PROCESS_SELL		3 // 出售道具
#define ITEM_PROCESS_TOKENUSE	4 // 钻石方式使用道具
#define ITEM_PROCESS_BUY		5 // 购买

/* 场合 */
#define ITEM_SITUATION_NOUSEMORE	0x01	// 禁止使用多个

/* 创建物品成功后返回的结构 */
typedef struct _itemout
{
	int m_itemkind;			// 物品种类
	short m_item_offset;	// 物品栏的位置
	short m_count;			// 增加的个数
}ItemOut;

/* 物品信息初始化 */
int itemkind_init();
int itemkind_reload();
int item_maxid_init();

/* 获取物品全局配置信息 */
char *item_getname( int itemkind );
short item_getlevel( int itemkind );
int item_getprice( int itemkind );
int item_gettoken( int itemkind );
short item_gettype( int itemkind );
unsigned char item_getsituation( int itemkind );
short item_get_overlap( int itemkind );
char item_getcolorlevel( int itemkind );

/* 物品动态属性 */
short item_get_base_ability( int itemkind, char pos );
int item_get_base_value( int itemkind, char pos );
int item_get_ability_value_withpos( int itemkind, char pos, short *ability, int *value );
char item_get_ability_value( int itemkind, short ability, int *value );
int _item_get_ability_value( Item *pItem, short ability );
int _item_set_ability_value( Item *pItem, short ability, int value );

/* 将offset转换成对应的属性结构 */
Item *item_getptr( int actor_index, int offset );

/* 服务器道具操作部分 */
int item_load( int actor_index );	// 玩家读取道具
int item_save( int actor_index, FILE *fp ); // 玩家保存所有道具
int item_insert( int actor_index, short offset ); // 创建道具的时候调用，保存刚创建的道具
int item_getitem( int actor_index, int itemkind, int itemnum, char color, char path ); // 玩家获得道具
int item_create( int actor_index, int itemkind, int itemnum, char color, ItemOut *pOut ); // 玩家创建道具
int item_lost( int actor_index, int itemkind, int num, char path ); // 服务器丢掉道具，根据kind
int item_lostitem( int actor_index, int itemoffset, int num, char path ); // 服务器丢掉道具，根据offset
int item_deletebox( int actor_index, int item_offset ); // 删除一个格子的道具
int item_deleteitemdb( int actorid, i64 itemid ); // 删除一个道具格子
int item_hasitem( int actor_index, int itemkind, int num ); // 是否有这个数量的物品
int item_hasitem_between( int actor_index, int minitemkind, int maxitemkind ); // 是否有这个数量的物品区间
int item_getitemnum( int actor_index, int itemkind );// 获取这个道具的数量 
int item_getitemindex( int actor_index, int itemkind );//获取道具的索引
int item_getitemindex_whihitemid( int actor_index, i64 itemid );//获取道具的索引

// ---------------------------------- 服务器响应道具操作 item_proc.cpp -----------------------------------------------------
int item_use( int actor_index, short itemindex, short itemnum, int herokind, int ask ); // 服务器响应道具操作-使用
int item_use_withtoken( int actor_index, short itemkind, short itemnum, int herokind, int ask ); // 服务器响应道具操作-直接花钱使用
int item_use_quick( int actor_index, short itemkind, char op, int buildingkind, int buildingoffset ); // 服务器响应道具操作-加速道具使用
int item_drop( int actor_index, short itemindex, short dorpcount ); // 服务器响应道具操作-丢弃
int item_buy( int actor_index, short itemkind, short itemnum ); // 服务器响应道具操作-购买
int item_settle( int actor_index );   // 服务器响应道具操作-整理

// ---------------------------------- 服务器发送道具协议 item_send.cpp -----------------------------------------------------
int item_sendnotuse( int actor_index, short itemindex, int err );
void item_sendlost( int actor_index, int target_index, short item_index, short item_num, char path );
void item_sendget( int actor_index, int target_index, short item_index, short item_num, char path );
int item_list( int actor_index );	// 发送道具列表
int item_info( int actor_index, short itemindex ); // 发送道具详细信息
int item_info_withitem( Item *pItem, int actor_index, short itemindex );// 真正的发送道具信息函数
int item_tokenbuy_getinfo( int actor_index, int itemkind );
int item_gm_getall( int actor_index );
#endif
