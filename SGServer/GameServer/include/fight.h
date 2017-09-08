#ifndef _FIGHT_H_
#define _FIGHT_H_

#define FIGHT_UNIT_MAX		256	// 战场双方单元数量
#define FIGHT_TURNS_MAX		8192
#define FIGHT_INT			100
#define FIGHT_FLOAT			100.0f

#define FIGHT_WIN			1	
#define FIGHT_LOSE			2

#define FIGHT_ATTACK		1	
#define FIGHT_DEFENSE		2

#define FIGHT_UNITTYPE_HERO		1 // 玩家英雄
#define FIGHT_UNITTYPE_GUARD	2 // 玩家城墙守卫
#define FIGHT_UNITTYPE_MONSTER	3 // 怪物表

#define FIGHTTYPE_STORY		1 // 副本战斗
#define FIGHTTYPE_CITY		2 // 城战
#define FIGHTTYPE_NATION	3 // 国战
#define FIGHTTYPE_ENEMY		4 // 流寇
#define FIGHTTYPE_RES		5 // 资源点争夺

// 一个战斗单元
typedef struct _fightunit
{
	short	offset;

	char	type;				// 1玩家英雄，2城墙守卫，3monster
	int		city_index;			// 类型索引
	int		index;				// (type=1 kind=英雄索引) (type=2 kind=守卫索引)
	int		kind;				// (type=1 kind=英雄kind) (type=2 kind=守卫kind) (type=3 kind=monsterid)

	short	level;				// 等级
	char	color;				// 颜色
	char	corps;				// 兵种
	int		attack;				// 攻击
	int		defense;			// 防御
	int		hp;					// 当前血
	int		maxhp;				// 参战时血
	int		troops;				// 血上限
	short	attack_increase;	// 攻击增强
	short	defense_increase;	// 防御增强
	short	assault;			// 攻城
	short	defend;				// 守城
	char	line;				// 带兵排数
	char	skillid;			// 武将技

	char	line_left;			// 当前剩余排数
	int		line_hp;			// 当前排剩余兵力
	int		damage;				// 总伤害
}FightUnit;

// 战斗结构
typedef struct _fight
{
	char	type;							// 战斗类型
	char	result;							// 战斗结果
	int		turns;							// 当前回合
	int		randspeed;						// 随机种子

	int		attack_armyindex;				// 攻击方部队索引，攻击方只能是部队
	char	defense_type;					// 防守方类别，1玩家城池，2部队 ...
	int		defense_index;					// 防守方索引，防守方类别

	FightUnit attack_unit[FIGHT_UNIT_MAX];	// 攻击方单元列表
	FightUnit defense_unit[FIGHT_UNIT_MAX];	// 防御方单元列表

	short attack_unit_num;					// 攻击方单元数量
	short defense_unit_num;					// 防御方单元数量

	short attack_unit_index;				// 攻击方当前出战单元
	short defense_unit_index;				// 防御方当前出战单元

	int attack_total_hp;
	int defense_total_hp;

	int attack_total_maxhp;
	int defense_total_maxhp;

	int attack_total_damage;
	int defense_total_damage;

	char unit_json[8192];	// 单元json字符串
}Fight;

// 向战场里添加一个英雄
int fight_add_hero( int pos, char type, int city_index, int index, int kind, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid );

// 战斗启动
int fight_start( int attack_armyindex, char defense_type, int defense_index );

// 战斗启动-副本战斗
int fight_start_bystory( int actor_index, SLK_NetC_StoryBattle *pValue, int chapter, int rank );

// 战斗每一回合
int fight_oneturn();

// 使用技能
int fight_useskill( int pos, FightUnit *pUnit, FightUnit *pTargetUnit );

// 普通攻击
int fight_damage( int pos, FightUnit *pUnit, FightUnit *pTargetUnit );

// 减血
int fight_changehp( int pos, FightUnit *pTargetUnit, int damage );

// 下一个英雄
FightUnit *fight_nextptr( int pos );

// 获取双方城池指针
City *fight_getcityptr( int pos );

// 战斗信息
int fight_unit2json();
#endif

