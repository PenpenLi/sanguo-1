#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <math.h>
#include <limits.h>
#include "dserver.h"
#include "db.h"
#include "global.h"
#include "actor.h"
#include "city.h"
#include "city_attr.h"
#include "hero.h"
#include "mapunit.h"
#include "map.h"
#include "map_town.h"
#include "map_enemy.h"
#include "map_res.h"
#include "army.h"
#include "army_group.h"
#include "server_netsend_auto.h"
#include "system.h"
#include "item.h"
#include "actor_notify.h"
#include "fight.h"
#include "world_boss.h"
#include "nation_hero.h"
#include "girl.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern MapUnit *g_mapunit;
extern int g_mapunit_maxcount;
extern Map g_map;

extern Actor *g_actors;
extern int g_maxactornum;

extern City *g_city;
extern int g_city_maxcount;

extern Army *g_army;
extern int g_army_maxcount;

extern HeroSkillInfo *g_hero_skill;
extern int g_hero_skill_maxnum;

extern HeroCorpsmulInfo *g_hero_corpsmul;
extern int g_hero_corpsmul_maxnum;

extern StoryInfo *g_storyinfo;
extern int g_storyinfo_maxnum;

extern MonsterInfo *g_monster;
extern int g_monster_maxnum;

extern MapZoneInfo *g_zoneinfo;
extern int g_zoneinfo_maxnum;

extern MapEnemyInfo *g_enemyinfo;
extern int g_enemyinfo_maxnum;

extern MapEnemy *g_map_enemy;
extern int g_map_enemy_maxcount;

extern MapRes *g_map_res;
extern int g_map_res_maxcount;

extern MapTownInfo *g_towninfo;
extern int g_towninfo_maxnum;

extern MapTown *g_map_town;
extern int g_map_town_maxcount;

extern Map g_map;

extern ArmyGroup *g_armygroup;
extern int g_armygroup_maxcount;

extern WorldBoss *g_world_boss;
extern int g_world_boss_maxcount;

extern int g_nation_heroinfo_maxnum;

Fight g_fight;
extern char g_gm_outresult[MAX_OUTRESULT_LEN];
char g_gm_isout = 0;
extern int g_map_town_attackmonster[3][8];
static char *s_fight_posname[] = { "", "attack", "defense" };
#ifdef _WIN32
char g_test_mod = 0;
#else
char g_test_mod = 0;
#endif

// 调试输出
#define FIGHT_DEBUG
int fight_debug( const char *format, ... )
{
#ifdef FIGHT_DEBUG
	int rtn = 0;
	va_list arg_ptr;

	// 记录本地log
	va_start( arg_ptr, format );
	rtn = u_log( 1, format, arg_ptr );
	va_end( arg_ptr );

	// GM平台回显
	if ( g_gm_isout == 1 )
	{
		char szMsg[4096] = { 0 };
		va_start( arg_ptr, format );
		vsprintf( szMsg, format, arg_ptr );
		va_end( arg_ptr );
		strcat( g_gm_outresult, "<br>" );
		strcat( g_gm_outresult, szMsg );
	}

	return rtn;
#else
	return 0;
#endif FIGHT_DEBUG
}

// 向战场里添加一个英雄
int fight_add_hero( int pos, char unit_type, int unit_index, char type, int index, int kind, short shape, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid, int expmax )
{
	if ( hp <= 0 )
		return -1;
	if ( hp > troops )
		hp = troops;
	FightUnit *pUnit = NULL;
	if ( pos == FIGHT_ATTACK )
	{
		if ( g_fight.attack_unit_num < FIGHT_UNIT_MAX - 1 )
		{
			pUnit = &g_fight.attack_unit[g_fight.attack_unit_num];
			pUnit->offset = g_fight.attack_unit_num;
			g_fight.attack_unit_num += 1;
			g_fight.attack_total_hp += hp;
			g_fight.attack_total_maxhp += hp;
		}
	}
	else
	{
		if ( g_fight.defense_unit_num < FIGHT_UNIT_MAX - 1 )
		{
			pUnit = &g_fight.defense_unit[g_fight.defense_unit_num];
			pUnit->offset = g_fight.defense_unit_num;
			g_fight.defense_unit_num += 1;
			g_fight.defense_total_hp += hp;
			g_fight.defense_total_maxhp += hp;
		}
	}
	if ( !pUnit )
		return -1;

	pUnit->unit_type = unit_type;
	pUnit->unit_index = unit_index;
	pUnit->type = type;
	pUnit->index = index;
	pUnit->kind = kind;
	pUnit->shape = shape;
	pUnit->level = level;
	pUnit->color = color;
	pUnit->corps = corps;
	pUnit->attack = attack;
	pUnit->defense = defense;
	pUnit->hp = hp;
	pUnit->maxhp = hp;
	pUnit->troops = troops;
	pUnit->attack_increase = attack_increase;
	pUnit->defense_increase = defense_increase;
	if ( g_fight.type == FIGHTTYPE_CITY || g_fight.type == FIGHTTYPE_NATION || g_fight.type == FIGHTTYPE_KINGWAR )
	{
		pUnit->assault = assault;
		pUnit->defend = defend;
	}
	else
	{
		pUnit->assault = assault;
		pUnit->defend = defend;
	}
	pUnit->line = line;
	pUnit->skillid_init = skillid;
	pUnit->skillid = skillid;
	pUnit->damage = 0;
	pUnit->expmax = expmax; // 参战时候经验

	// 战斗中武将每排兵力=武将兵力属性值/武将总带兵排数,结果向下取整
	int line_troops = pUnit->troops / pUnit->line;
	// 战斗中带兵排数 = 实际参战兵力 / 每排兵力，结果向上取整
	if ( pUnit->troops == pUnit->maxhp )
	{
		pUnit->line_left = pUnit->line;
	}
	else
	{
		pUnit->line_left = (int)ceil( pUnit->maxhp / (float)line_troops );
	}
	if ( pUnit->line_left == 1 )
	{ // 最后一排兵力=（可带兵力-实际参战兵力）% 每排兵力
		if ( pUnit->troops == pUnit->maxhp )
			pUnit->line_hp = line_troops;
		else if ( pUnit->troops - pUnit->maxhp >= line_troops )
			pUnit->line_hp = line_troops;
		else
			pUnit->line_hp = (pUnit->troops - pUnit->maxhp) % line_troops;
	}
	else
	{
		// 其余排的兵力都等于每排兵力
		pUnit->line_hp = line_troops;
	}

	char name[64] = { 0 };
	if ( type == FIGHT_UNITTYPE_LEADER_HERO || type == FIGHT_UNITTYPE_HERO )
	{
		if ( unit_type == MAPUNIT_TYPE_CITY )
		{
			if ( unit_index >= 0 && unit_index < g_city_maxcount )
			{
				sprintf( name, "%s", g_city[unit_index].name );
				if ( g_city[unit_index].buffsec[CITY_BUFF_FOREST] > 0 )
					pUnit->buff_forest = 1;
			}
		}
		else if ( unit_type == MAPUNIT_TYPE_ARMY )
		{
			City *pCity = army_getcityptr( unit_index );
			if ( pCity )
			{
				sprintf( name, "%s", pCity->name );
				if ( pCity->buffsec[CITY_BUFF_FOREST] > 0 )
					pUnit->buff_forest = 1;
			}
		}
	}
	fight_debug( "[%s] idx:%d,type:%d,actorname:%s,index:%d,kind:%d,level:%d,color:%d,corps:%d,attack:%d,defense:%d,hp:%d,troops:%d,attack_inc:%d,defense_inc:%d,assault:%d,defend:%d,line:%d,linehp:%d,skill:%d", 
		s_fight_posname[pos], pUnit->offset, pUnit->type, name, pUnit->index, kind, level, color, corps, attack, defense, hp, troops, attack_increase, defense_increase, assault, defend, line, pUnit->line_hp, skillid );
	return 0;
}

int fight_start( int attack_armyindex, char defense_type, int defense_index )
{
	g_gm_isout = 0;
	g_gm_outresult[0] = '\0';
	if ( attack_armyindex < 0 || attack_armyindex >= g_army_maxcount )
		return -1;

	memset( &g_fight, 0, sizeof( Fight ) );
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		g_fight.attack_unit[tmpi].offset = -1;
		g_fight.attack_unit[tmpi].unit_index = -1;
		g_fight.attack_unit[tmpi].index = -1;

		g_fight.defense_unit[tmpi].offset = -1;
		g_fight.defense_unit[tmpi].unit_index = -1;
		g_fight.defense_unit[tmpi].index = -1;
	}
	g_fight.attack_armyindex = -1;
	g_fight.defense_index = -1;
	// 为这场战斗创建一个随机种子，随机要根据这个值，保证客户端服务器同步
	g_fight.randspeed = (int)time( NULL )/7;
	g_fight.randspeed_init = g_fight.randspeed;
	g_fight.attack_armyindex = attack_armyindex;
	g_fight.attack_type = g_army[attack_armyindex].from_type;
	g_fight.defense_type = defense_type;
	g_fight.defense_index = defense_index;

	fight_debug( "\n\n============================================== FIGHT START ==============================================" );
	int result = 0;

	// 攻击方为玩家
	if ( g_army[attack_armyindex].from_type == MAPUNIT_TYPE_CITY )
	{
		// 攻击方出战英雄
		for ( int tmpi = 0; tmpi < 4; tmpi++ )
		{
			short herokind = g_army[attack_armyindex].herokind[tmpi];
			if ( herokind <= 0 )
				continue;
			City *pCity = army_getcityptr( attack_armyindex );
			if ( !pCity )
				continue;
			int hero_index = city_hero_getindex( pCity->index, herokind );
			if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
				continue;
			Hero *pHero = &pCity->hero[hero_index];
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_ARMY, attack_armyindex, FIGHT_UNITTYPE_LEADER_HERO, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );

		}
	}
	
	// 防御方为流寇
	if ( defense_type == MAPUNIT_TYPE_ENEMY )
	{
		g_fight.type = FIGHTTYPE_ENEMY;
		if ( defense_index < 0 || defense_index >= g_map_enemy_maxcount )
			return -1;
		MapEnemyInfo *config = map_enemy_getconfig( g_map_enemy[defense_index].kind );
		if ( !config )
			return -1;
		for ( int tmpi = 0; tmpi < 4; tmpi++ )
		{
			short monsterid = config->monsterid[tmpi];
			if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
				continue;
			MonsterInfo *pMonster = &g_monster[monsterid];
			if ( !pMonster )
				continue;
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ENEMY, defense_index, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
				pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );
		}
	}
	// 防御方为资源点的部队
	else if ( defense_type == MAPUNIT_TYPE_RES )
	{
		g_fight.type = FIGHTTYPE_RES;
		int army_index = map_res_getarmy( defense_index );
		if ( army_index < 0 || army_index >= g_army_maxcount )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		Army *pArmy = &g_army[army_index];
		if ( !pArmy )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}

		short herokind = pArmy->herokind[0];
		if ( herokind <= 0 )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		City *pCity = army_getcityptr( army_index );
		if ( !pCity )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		int hero_index = city_hero_getindex( pCity->index, herokind );
		if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		Hero *pHero = &pCity->hero[hero_index];
		HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
		if ( !config )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_LEADER_HERO, 0, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
			pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_GATHER ), (char)config->skillid, pHero->exp );
	}
	// 防御方为国家名将
	else if ( defense_type == MAPUNIT_TYPE_NATIONHERO )
	{
		g_fight.type = FIGHTTYPE_ENEMY;
		if ( defense_index < 0 || defense_index >= g_nation_heroinfo_maxnum )
			return -1;
		NationHeroInfo *config = nation_hero_getconfig( defense_index );
		if ( !config )
			return -1;
		for ( int tmpi = 0; tmpi < 4; tmpi++ )
		{
			short monsterid = config->monsterid[tmpi];
			if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
				continue;
			MonsterInfo *pMonster = &g_monster[monsterid];
			if ( !pMonster )
				continue;
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_NATIONHERO, defense_index, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
				pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );
		}
	}
	// 防御方为部队（血战皇城使用）
	else if ( defense_type == MAPUNIT_TYPE_KINGWAR_TOWN )
	{
		g_fight.type = FIGHTTYPE_KINGWAR;
		int army_index = defense_index;
		if ( army_index < 0 || army_index >= g_army_maxcount )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		Army *pArmy = &g_army[army_index];
		if ( !pArmy )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}

		short herokind = pArmy->herokind[0];
		if ( herokind <= 0 )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		City *pCity = army_getcityptr( army_index );
		if ( !pCity )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		int hero_index = city_hero_getindex( pCity->index, herokind );
		if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		Hero *pHero = &pCity->hero[hero_index];
		HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
		if ( !config )
		{
			g_fight.result = FIGHT_WIN;
			return 0;
		}
		fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_LEADER_HERO, 0, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
			pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_KINGWAR ), (char)config->skillid, pHero->exp );

	}
	else
	{
		return -1;
	}
	
	// 战斗回合
	for ( int tmpi = 0; tmpi < FIGHT_TURNS_MAX; tmpi++ )
	{
		result = fight_oneturn();
		if ( result > 0 )
		{
			break;
		}
	}
	if ( result == 0 )
	{
		//  超过%回合
		fight_debug( "[pass turns]" );
		g_fight.result = FIGHT_LOSE;
	}
	else
	{
		if ( result == FIGHT_WIN )
		{
			fight_debug( "[ATK WIN]" );
			g_fight.result = FIGHT_WIN;
		}
		else if ( result == FIGHT_LOSE )
		{
			fight_debug( "[DEF WIN]" );
			g_fight.result = FIGHT_LOSE;
		}
	}

	// 信息转json
	if ( g_fight.type != FIGHTTYPE_KINGWAR )
	{
		fight_unit2json();
	}
	return 0;
}

// 战斗启动-团战
int fight_start_armygroup( int group_index )
{
	g_gm_isout = 0;
	g_gm_outresult[0] = '\0';
	if ( group_index < 0 || group_index >= g_armygroup_maxcount )
		return -1;

	memset( &g_fight, 0, sizeof( Fight ) );
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		g_fight.attack_unit[tmpi].offset = -1;
		g_fight.attack_unit[tmpi].unit_index = -1;
		g_fight.attack_unit[tmpi].index = -1;

		g_fight.defense_unit[tmpi].offset = -1;
		g_fight.defense_unit[tmpi].unit_index = -1;
		g_fight.defense_unit[tmpi].index = -1;
	}

	// 为这场战斗创建一个随机种子，随机要根据这个值，保证客户端服务器同步
	g_fight.randspeed = (int)time( NULL ) / 7;
	g_fight.randspeed_init = g_fight.randspeed;
	g_fight.attack_type = g_armygroup[group_index].from_type;
	g_fight.attack_armyindex = g_armygroup[group_index].from_index;
	g_fight.defense_type = g_armygroup[group_index].to_type;
	g_fight.defense_index = g_armygroup[group_index].to_index;

	fight_debug( "\n\n============================================== FIGHT GROUP START ==============================================" );
	int result = 0;
	// 攻击方
	for ( int tmpi = 0; tmpi < ARMYGROUP_MAXCOUNT; tmpi++ )
	{
		int army_index = g_armygroup[group_index].attack_armyindex[tmpi];
		if ( army_index < 0 || army_index >= g_army_maxcount )
			continue;
		if ( g_army[army_index].from_type == MAPUNIT_TYPE_CITY )
		{ // 攻击方为玩家
			City *pCity = army_getcityptr( army_index );
			if ( pCity )
			{
				for ( int tmpi = 0; tmpi < 4; tmpi++ )
				{
					short herokind = g_army[army_index].herokind[tmpi];
					if ( herokind <= 0 )
						continue;
					int hero_index = city_hero_getindex( pCity->index, herokind );
					if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
						continue;
					Hero *pHero = &pCity->hero[hero_index];
					HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
					if ( !config )
						continue;
					fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_HERO, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
						pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );
				}
				pCity->temp_silver = 0;
				pCity->temp_wood = 0;
				pCity->temp_food = 0;
				pCity->temp_wounded_soldiers[0] = 0;
				pCity->temp_wounded_soldiers[1] = 0;
				pCity->temp_wounded_soldiers[2] = 0;
			}
		}
		else if ( g_army[army_index].from_type == MAPUNIT_TYPE_TOWN )
		{ // 攻击方为城镇
			MapTown *pTown = map_town_getptr( g_armygroup[group_index].from_id );
			if ( pTown )
			{
				int level = pTown->dev_level;
				if ( level < 0 )
					level = 0;
				else if ( level > 2 )
					level = 2;
				for ( int tmpi = 0; tmpi < 8; tmpi++ )
				{
					int monsterid = g_map_town_attackmonster[level][tmpi];
					if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
						continue;
					MonsterInfo *pMonster = &g_monster[monsterid];
					if ( !pMonster )
						continue;
					fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_TOWN, pTown->townid, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
						pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );
				}
			}
		}
	}

	// 防御方为玩家城池
	if ( g_fight.defense_type == MAPUNIT_TYPE_CITY )
	{
		g_fight.type = FIGHTTYPE_CITY;
		if ( g_fight.defense_index < 0 || g_fight.defense_index >= g_city_maxcount )
			return -1;
		City *pCity = &g_city[g_fight.defense_index];
		if ( !pCity )
			return -1;

		// 协防部队
		for ( int tmpi = 0; tmpi < ARMYGROUP_MAXCOUNT; tmpi++ )
		{
			int army_index = g_armygroup[group_index].defense_armyindex[tmpi];
			if ( army_index < 0 || army_index >= g_army_maxcount )
				continue;
			City *pCity = army_getcityptr( army_index );
			if ( !pCity )
				continue;
			for ( int tmpi = 0; tmpi < 4; tmpi++ )
			{
				short herokind = g_army[army_index].herokind[tmpi];
				if ( herokind <= 0 )
					continue;
				int hero_index = city_hero_getindex( pCity->index, herokind );
				if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
					continue;
				Hero *pHero = &pCity->hero[hero_index];
				HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
				if ( !config )
					continue;
				fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_HERO, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
					pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );

			}
		}

		// 玩家主力部队
		for ( int tmpi = 0; tmpi < 4; tmpi++ )
		{
			Hero *pHero = &pCity->hero[tmpi];
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			if ( pHero->state > 0 )
				continue;
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_CITY, pCity->index, FIGHT_UNITTYPE_LEADER_HERO, tmpi, pHero->kind, pHero->kind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );
		}

		// 羽林卫部队
		for ( int tmpi = 8; tmpi < 12; tmpi++ )
		{
			Hero *pHero = &pCity->hero[tmpi];
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			if ( pHero->soldiers < pHero->troops )
				continue;
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_CITY, pCity->index, FIGHT_UNITTYPE_HERO, tmpi, pHero->kind, pHero->kind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );
		}

		// 城墙部队
		for ( int tmpi = 0; tmpi < CITY_GUARD_MAX; tmpi++ )
		{
			int monsterid = pCity->guard[tmpi].monsterid;
			if ( monsterid <= 0 )
				continue;
			CityGuardInfoConfig *config = city_guard_config( monsterid, pCity->guard[tmpi].color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_CITY, pCity->index, FIGHT_UNITTYPE_GUARD, tmpi, monsterid, pCity->guard[tmpi].shape, pCity->guard[tmpi].level, pCity->guard[tmpi].color, (char)pCity->guard[tmpi].corps,
				config->attack, config->defense, pCity->guard[tmpi].soldiers, config->troops, config->attack_increase, config->defense_increase, config->assault, config->defend, (char)config->line, 0, 0 );
		}

		// 加上驻防的部队
		for ( int index = 0; index < CITY_HELPDEFENSE_MAX; index++ )
		{
			int army_index = pCity->help_armyindex[index];
			if ( army_index < 0 )
				continue;
			if ( g_army[army_index].state != ARMY_STATE_HELP )
				continue;
			City *pCity = army_getcityptr( army_index );
			if ( !pCity )
				continue;
			for ( int tmpi = 0; tmpi < 4; tmpi++ )
			{
				short herokind = g_army[army_index].herokind[tmpi];
				if ( herokind <= 0 )
					continue;
				int hero_index = city_hero_getindex( pCity->index, herokind );
				if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
					continue;
				Hero *pHero = &pCity->hero[hero_index];
				HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
				if ( !config )
					continue;
				fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_HERO, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
					pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );

			}
		}
	}
	// 防御方为城镇
	else if ( g_fight.defense_type == MAPUNIT_TYPE_TOWN )
	{
		g_fight.type = FIGHTTYPE_NATION;
		// 守军
		MapTown *pTown = map_town_getptr( g_armygroup[group_index].to_id );
		if ( pTown )
		{
			for ( int tmpi = 0; tmpi < MAP_TOWN_MONSTER_MAX; tmpi++ )
			{
				int monsterid = pTown->monster[tmpi];
				if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
					continue;
				int soldier = pTown->soldier[tmpi];
				if ( g_test_mod == 1 )
					soldier /= 100;

				if ( soldier <= 0 )
					continue;
				MonsterInfo *pMonster = &g_monster[monsterid];
				if ( !pMonster )
					continue;
				fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_TOWN, pTown->townid, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
					pMonster->attack, pMonster->defense, soldier, soldier, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );

				g_fight.town_total_maxhp += soldier;
			}
		}
		// 协防部队
		for ( int tmpi = 0; tmpi < ARMYGROUP_MAXCOUNT; tmpi++ )
		{
			int army_index = g_armygroup[group_index].defense_armyindex[tmpi];
			if ( army_index < 0 || army_index >= g_army_maxcount )
				continue;
			City *pCity = army_getcityptr( army_index );
			if ( !pCity )
				continue;
			for ( int tmpi = 0; tmpi < 4; tmpi++ )
			{
				short herokind = g_army[army_index].herokind[tmpi];
				if ( herokind <= 0 )
					continue;
				int hero_index = city_hero_getindex( pCity->index, herokind );
				if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
					continue;
				Hero *pHero = &pCity->hero[hero_index];
				HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
				if ( !config )
					continue;
				fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_ARMY, army_index, FIGHT_UNITTYPE_HERO, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
					pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );

			}
		}
	}

	// 战斗回合
	for ( int tmpi = 0; tmpi < FIGHT_TURNS_MAX; tmpi++ )
	{
		result = fight_oneturn();
		if ( result > 0 )
		{
			break;
		}
	}
	if ( result == 0 )
	{
		//  超过%回合
		fight_debug( "[pass turns]" );
		g_fight.result = FIGHT_LOSE;
	}
	else
	{
		if ( result == FIGHT_WIN )
		{
			fight_debug( "[ATK WIN]" );
			g_fight.result = FIGHT_WIN;
		}
		else if ( result == FIGHT_LOSE )
		{
			fight_debug( "[DEF WIN]" );
			g_fight.result = FIGHT_LOSE;
		}
	}

	// 信息转json
	fight_unit2json();
	return 0;
}

// 战斗启动-副本战斗
int fight_start_bystory( int actor_index, SLK_NetC_StoryBattle *pValue )
{
	g_gm_isout = 0;
	g_gm_outresult[0] = '\0';
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;

	memset( &g_fight, 0, sizeof( Fight ) );
	g_fight.attack_armyindex = -1;
	g_fight.defense_index = -1;
	// 为这场战斗创建一个随机种子，随机要根据这个值，保证客户端服务器同步
	g_fight.randspeed = (int)time( NULL ) / 7;
	g_fight.randspeed_init = g_fight.randspeed;

	fight_debug( "\n\n============================================== STORY FIGHT START ==============================================" );
	int result = 0;

	if ( pValue->m_storyid < 10 )
	{
		g_fight.type = FIGHTTYPE_QUEST;
	}
	else
	{
		g_fight.type = FIGHTTYPE_STORY;
	}

	// 玩家出战英雄
	for ( int tmpi = 0; tmpi < 4; tmpi++ )
	{
		short herokind = pValue->m_herokind[tmpi];
		if ( herokind > 0 )
		{
			Hero *pHero = hero_getptr( actor_index, herokind );
			if ( !pHero )
				continue;
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_CITY, pCity->index, FIGHT_UNITTYPE_LEADER_HERO, -1, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->troops, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );
		}
	}

	// 副本英雄
	for ( int tmpi = 0; tmpi < 4; tmpi++ )
	{
		int monsterid = g_storyinfo[pValue->m_storyid].monsterid[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;
		MonsterInfo *pMonster = &g_monster[monsterid];
		if ( !pMonster )
			continue;
		fight_add_hero( FIGHT_DEFENSE, 0, -1, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
			pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );
	}

	// 战斗回合
	for ( int tmpi = 0; tmpi < FIGHT_TURNS_MAX; tmpi++ )
	{
		result = fight_oneturn();
		if ( result > 0 )
		{
			break;
		}
	}
	if ( result == 0 )
	{
		//  超过%回合
		fight_debug( "[pass turns]" );
		g_fight.result = FIGHT_LOSE;
	}
	else
	{
		if ( result == FIGHT_WIN )
		{
			fight_debug( "[ATK WIN]" );
			g_fight.result = FIGHT_WIN;
		}
		else if ( result == FIGHT_LOSE )
		{
			fight_debug( "[DEF WIN]" );
			g_fight.result = FIGHT_LOSE;
		}
	}
	// 信息转json
	fight_unit2json();
	return 0;
}

// 战斗启动-世界boss
int fight_start_byworldboss( int actor_index, SLK_NetC_WorldBossBattle *pValue )
{
	g_gm_isout = 0;
	g_gm_outresult[0] = '\0';
	ACTOR_CHECK_INDEX( actor_index );
	City *pCity = city_getptr( actor_index );
	if ( !pCity )
		return -1;
	int bossid = pValue->m_bossid;
	if ( bossid <= 0 || bossid >= g_world_boss_maxcount )
		return -1;

	memset( &g_fight, 0, sizeof( Fight ) );
	g_fight.attack_armyindex = -1;
	g_fight.defense_index = -1;
	// 为这场战斗创建一个随机种子，随机要根据这个值，保证客户端服务器同步
	g_fight.randspeed = (int)time( NULL ) / 7;
	g_fight.randspeed_init = g_fight.randspeed;

	fight_debug( "\n\n============================================== WORLDBOSS FIGHT START ==============================================" );
	int result = 0;
	g_fight.type = FIGHTTYPE_WORLDBOSS;
	// 玩家出战英雄
	for ( int tmpi = 0; tmpi < 4; tmpi++ )
	{
		short herokind = pValue->m_herokind[tmpi];
		if ( herokind > 0 )
		{
			Hero *pHero = hero_getptr( actor_index, herokind );
			if ( !pHero )
				continue;
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_CITY, pCity->index, FIGHT_UNITTYPE_LEADER_HERO, -1, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->troops, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity, HERO_STATE_FIGHT ), (char)config->skillid, pHero->exp );
		}
	}

	// 世界boss
	for ( int tmpi = 0; tmpi < WORLDBOSS_MONSTER_MAX; tmpi++ )
	{
		int monsterid = g_world_boss[bossid].monster[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			break;
		MonsterInfo *pMonster = &g_monster[monsterid];
		if ( !pMonster )
			continue;
		fight_add_hero( FIGHT_DEFENSE, 0, -1, FIGHT_UNITTYPE_MONSTER, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
			pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill, 0 );
	}

	// 战斗回合
	for ( int tmpi = 0; tmpi < FIGHT_TURNS_MAX; tmpi++ )
	{
		result = fight_oneturn();
		if ( result > 0 )
		{
			break;
		}
	}
	if ( result == 0 )
	{
		//  超过%回合
		fight_debug( "[pass turns]" );
		g_fight.result = FIGHT_LOSE;
	}
	else
	{
		if ( result == FIGHT_WIN )
		{
			fight_debug( "[ATK WIN]" );
			g_fight.result = FIGHT_WIN;
		}
		else if ( result == FIGHT_LOSE )
		{
			fight_debug( "[DEF WIN]" );
			g_fight.result = FIGHT_LOSE;
		}
	}
	// 信息转json
	fight_unit2json();
	return 0;
}

// 战斗每一回合
int fight_oneturn()
{
	int attack_damage = 0;
	int defense_damage = 0;
	int result = 0;
	g_fight.turns += 1;
	fight_debug( "--------------------------- [turns-%d] ---------------------------", g_fight.turns );

	// 攻击方当前出手英雄
	FightUnit *pAttackUnit = fight_nextptr( FIGHT_ATTACK );
	if ( !pAttackUnit )
		return FIGHT_LOSE;

	// 防守方当前出手英雄
	FightUnit *pDefenseUnit = fight_nextptr( FIGHT_DEFENSE );
	if ( !pDefenseUnit )
		return FIGHT_WIN;


	// 双方使用出场技能
	attack_damage = fight_useskill( FIGHT_ATTACK, pAttackUnit, pDefenseUnit );
	defense_damage = fight_useskill( FIGHT_DEFENSE, pDefenseUnit, pAttackUnit );
	if ( attack_damage > 0 )
	{
		result = fight_changehp( FIGHT_ATTACK, pDefenseUnit, attack_damage );
		if ( result > 0 )
			return result;
	}
	if ( defense_damage > 0 )
	{
		result = fight_changehp( FIGHT_DEFENSE, pAttackUnit, defense_damage );
		if ( result > 0 )
			return result;
	}

	// 双方出手攻击
	attack_damage = fight_damage( FIGHT_ATTACK, pAttackUnit, pDefenseUnit );
	defense_damage = fight_damage( FIGHT_DEFENSE, pDefenseUnit, pAttackUnit );
	if ( attack_damage > 0 )
	{
		result = fight_changehp( FIGHT_ATTACK, pDefenseUnit, attack_damage );
		if ( result > 0 )
			return result;
	}
	if ( defense_damage > 0 )
	{
		result = fight_changehp( FIGHT_DEFENSE, pAttackUnit, defense_damage );
		if ( result > 0 )
			return result;
	}

	return 0;
}

// 兵种相克系数
static int _corpsmul( int corps, int target_corps )
{
	if ( corps < 0 || corps >= g_hero_corpsmul_maxnum )
		return FIGHT_INT;
	if ( target_corps < 0 || target_corps >= g_hero_corpsmul_maxnum )
		return FIGHT_INT;
	return g_hero_corpsmul[corps].target_corps[target_corps];
}

// 使用出场技能
int fight_useskill( int pos, FightUnit *pUnit, FightUnit *pTargetUnit )
{
	int true_damage = 0;
	int damage = 0;
	int skillid = pUnit->skillid;
	if ( skillid > 0 && skillid < g_hero_skill_maxnum )
	{ // 攻击方释放武将技
		int random = random_custom( g_hero_skill[skillid].randmin, g_hero_skill[skillid].randmax, &g_fight.randspeed );
		damage = (int)ceil( ( pUnit->hp * (g_hero_skill[skillid].value / FIGHT_FLOAT) * (random / FIGHT_FLOAT)) );
		true_damage = damage;
		damage = min( damage, pTargetUnit->line_hp );
		fight_debug( "[%s](skill) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pUnit->offset, pUnit->kind, damage, true_damage, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp, damage, pTargetUnit->line_hp - damage );
		pUnit->skillid = 0;
		pUnit->damage += damage;
		if ( pTargetUnit->unit_type == MAPUNIT_TYPE_TOWN )
		{ // 对守军造成伤害
			pUnit->town_damage += damage;
		}
	}
	return damage;
}

// 普通攻击
int fight_damage( int pos, FightUnit *pUnit, FightUnit *pTargetUnit )
{
	int true_damage = 0;
	int damage = 0;
	// 1.首先判断是否闪避
	int dodge = random_custom( 1, 100, &g_fight.randspeed );
	if ( dodge <= global.fight_dodge )
	{ // 闪避了
		fight_debug( "[%s](miss) idx:%d,kind:%d,damage:%d,target_idx:%d,target_kind:%d,line_left:%d,line_hp:%d", s_fight_posname[pos], pUnit->offset, pUnit->kind, 0, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp );
	}
	else
	{
		// 2.计算基础伤害
		// 基础伤害=（攻方攻击力-防方防御力）*（0.5+0.5*攻方当前兵力/防方当前兵力）*兵种克制系数*战斗节奏控制系数+攻方强攻-防方强防+攻方攻城-防方守城
		damage = (int)ceil( ( 
			(pUnit->attack - pTargetUnit->defense) 
			* ((global.fight_v1 / FIGHT_FLOAT) + (global.fight_v2 / FIGHT_FLOAT) * pUnit->line_hp / (float)pTargetUnit->line_hp) 
			+ pUnit->attack_increase - pTargetUnit->defense_increase 
			+ pUnit->assault - pTargetUnit->defend) 
			* (_corpsmul( pUnit->corps, pTargetUnit->corps ) / FIGHT_FLOAT) 
			* (global.fight_control_value / FIGHT_FLOAT) );
		
		// 3.设定保底伤害
		// 基础保底伤害 = Max（攻方攻击 * 5 % ，基础伤害）
		damage = max( (int)ceil( pUnit->attack * (global.fight_attackmin_value / FIGHT_FLOAT) ), damage );

		// 4.计算暴击伤害
		int random = random_custom( global.fight_damage_randmin, global.fight_damage_randmax, &g_fight.randspeed );
		int crit = random_custom( 1, 100, &g_fight.randspeed );
		if ( crit <= global.fight_crit_odds )
		{
			damage = (int)ceil( damage * (global.fight_crit_damage / FIGHT_FLOAT) * (random / FIGHT_FLOAT) );
			true_damage = damage;
			damage = min( damage, pTargetUnit->line_hp );
			fight_debug( "[%s](crit) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pUnit->offset, pUnit->kind, damage, true_damage, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp, damage, pTargetUnit->line_hp - damage );
		}
		else
		{// 没暴击
			damage = (int)ceil( damage * (random / FIGHT_FLOAT) );
			true_damage = damage;
			damage = min( damage, pTargetUnit->line_hp );
			fight_debug( "[%s](default) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pUnit->offset, pUnit->kind, damage, true_damage, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp, damage, pTargetUnit->line_hp - damage );
		}
		pUnit->damage += damage;
		if ( pTargetUnit->unit_type == MAPUNIT_TYPE_TOWN )
		{ // 对守军造成伤害
			pUnit->town_damage += damage;
		}
	}
	return damage;
}

// 减血
int fight_changehp( int pos, FightUnit *pTargetUnit, int damage )
{
	// 总击杀和总死亡
	if ( pos == FIGHT_ATTACK )
	{
		g_fight.defense_total_hp -= damage;
		g_fight.attack_total_damage += damage;
	}
	else
	{
		g_fight.attack_total_hp -= damage;
		g_fight.defense_total_damage += damage;
	}

	pTargetUnit->hp -= damage;
	if ( pTargetUnit->hp < 0 )
		pTargetUnit->hp = 0;
	pTargetUnit->line_hp -= damage;
	if ( pTargetUnit->line_hp <= 0 )
	{
		pTargetUnit->line_left -= 1;
		if ( pTargetUnit->line_left > 0 )
		{ // 减少一排

			// 战斗中武将每排兵力=武将兵力属性值/武将总带兵排数,结果向下取整
			int line_troops = pTargetUnit->troops / pTargetUnit->line;	
			if ( pTargetUnit->line_left == 1 )
			{ // 最后一排兵力=（可带兵力-实际参战兵力）% 每排兵力
				if ( pTargetUnit->troops == pTargetUnit->maxhp )
					pTargetUnit->line_hp = line_troops;
				else if ( pTargetUnit->troops - pTargetUnit->maxhp >= line_troops )
					pTargetUnit->line_hp = line_troops;
				else
					pTargetUnit->line_hp = (pTargetUnit->troops - pTargetUnit->maxhp) % line_troops;
			}
			else
			{
				// 其余排的兵力都等于每排兵力
				pTargetUnit->line_hp = line_troops;
			}
		}
		else
		{
			pTargetUnit->hp = 0;
			if ( pos == FIGHT_ATTACK )
			{
				pTargetUnit = fight_nextptr( FIGHT_DEFENSE );
				if ( !pTargetUnit )
					return FIGHT_WIN;
				fight_debug( "[%s](up) idx:%d,kind:%d", s_fight_posname[FIGHT_DEFENSE], pTargetUnit->offset, pTargetUnit->kind );
			}
			else
			{
				pTargetUnit = fight_nextptr( FIGHT_ATTACK );
				if ( !pTargetUnit )
					return FIGHT_LOSE;
				fight_debug( "[%s](up) idx:%d,kind:%d", s_fight_posname[FIGHT_ATTACK], pTargetUnit->offset, pTargetUnit->kind );
			}
		}
	}
	return 0;
}

// 出阵英雄
FightUnit *fight_nextptr( int pos )
{
	if ( pos == FIGHT_ATTACK )
	{
		if ( g_fight.attack_unit_index >= 0 && g_fight.attack_unit_index < FIGHT_UNIT_MAX )
		{
			for ( int tmpi = g_fight.attack_unit_index; tmpi < g_fight.attack_unit_num; tmpi++ )
			{
				if ( g_fight.attack_unit[tmpi].hp > 0 )
				{
					g_fight.attack_unit_index = tmpi;
					return &g_fight.attack_unit[tmpi];
				}
			}
		}
	}
	else
	{
		if ( g_fight.defense_unit_index >= 0 && g_fight.defense_unit_index < FIGHT_UNIT_MAX )
		{
			for ( int tmpi = g_fight.defense_unit_index; tmpi < g_fight.defense_unit_num; tmpi++ )
			{
				if ( g_fight.defense_unit[tmpi].hp > 0 )
				{
					g_fight.defense_unit_index = tmpi;
					return &g_fight.defense_unit[tmpi];
				}
			}
		}
	}
	return NULL;
}

// 获取双方城池指针
City *fight_getcityptr( int pos )
{
	City *pCity = NULL;
	if ( pos == FIGHT_ATTACK )
	{
		if ( g_fight.type == FIGHTTYPE_STORY )
		{
			if ( g_fight.attack_armyindex < 0 || g_fight.attack_armyindex >= g_city_maxcount )
				return NULL;
			pCity = &g_city[g_fight.attack_armyindex];
		}
		else if ( g_fight.type == FIGHTTYPE_CITY )
		{
			if ( g_fight.attack_armyindex < 0 || g_fight.attack_armyindex >= g_city_maxcount )
				return NULL;
			pCity = &g_city[g_fight.attack_armyindex];
		}
		else if ( g_fight.type == FIGHTTYPE_NATION )
		{
			if ( g_fight.attack_type == MAPUNIT_TYPE_CITY )
			{
				if ( g_fight.attack_armyindex < 0 || g_fight.attack_armyindex >= g_city_maxcount )
					return NULL;
				pCity = &g_city[g_fight.attack_armyindex];
			}
		}
		else if ( g_fight.type == FIGHTTYPE_ENEMY || g_fight.type == FIGHTTYPE_RES )
		{
			if ( g_fight.attack_armyindex < 0 || g_fight.attack_armyindex >= g_army_maxcount )
				return NULL;
			if ( g_army[g_fight.attack_armyindex].from_type != MAPUNIT_TYPE_CITY )
				return NULL;
			int city_index = g_army[g_fight.attack_armyindex].from_index;
			if ( city_index < 0 )
				return NULL;
			pCity = &g_city[city_index];
		}
	}
	else
	{
		// 只有防御方为城池和驻军才有城池
		if ( g_fight.defense_type == MAPUNIT_TYPE_CITY )
		{
			if ( g_fight.defense_index < 0 || g_fight.defense_index >= g_city_maxcount )
				return NULL;
			pCity = &g_city[g_fight.defense_index];
		}
		else if ( g_fight.defense_type == MAPUNIT_TYPE_ARMY )
		{
			if ( g_fight.defense_index < 0 || g_fight.defense_index >= g_army_maxcount )
				return NULL;
			if ( g_army[g_fight.defense_index].from_type != MAPUNIT_TYPE_CITY )
				return NULL;
			int city_index = g_army[g_fight.defense_index].from_index;
			if ( city_index < 0 )
				return NULL;
			pCity = &g_city[city_index];
		}
		else if ( g_fight.defense_type == MAPUNIT_TYPE_RES )
		{
			int army_index = map_res_getarmy( g_fight.defense_index );
			if ( army_index < 0 || army_index >= g_army_maxcount )
				return NULL;
			pCity = army_getcityptr( army_index );
		}
		else if ( g_fight.defense_type == MAPUNIT_TYPE_TOWN )
		{
			
		}
	}
	return pCity;
}

// 战斗结算
int fight_lost_calc_single( FightUnit *pUnit )
{
	if ( pUnit->unit_type == MAPUNIT_TYPE_ARMY )
	{// 战斗单元属于一个部队
		int army_index = pUnit->unit_index;
		if ( army_index >= 0 && army_index < g_army_maxcount )
		{
			City *pCity = army_getcityptr( army_index );
			if ( !pCity )
				return -1;
			int hero_index = city_hero_getindex( pCity->index, pUnit->kind );
			if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
				return -1;
			hero_changesoldiers( pCity, &pCity->hero[hero_index], -(pUnit->maxhp - pUnit->hp), PATH_FIGHT );
			g_army[army_index].totals -= (pUnit->maxhp - pUnit->hp);
			g_army[army_index].damage += pUnit->damage;

			// 武将经验
			if ( pUnit->exp > 0 )
			{
				hero_addexp( pCity, &pCity->hero[hero_index], pUnit->exp, PATH_FIGHT );
			}

			// 部队添加携带威望
			if ( pUnit->prestige > 0 )
			{
				city_changeprestige( pCity->index, pUnit->prestige, PATH_FIGHT );
				//army_carry_additem( army_index, AWARDKIND_PRESTIGE, pUnit->prestige );
			}

			// 伤兵恢复
			if ( pUnit->wounded_soldiers > 0 )
			{
				city_changesoldiers( pCity->index, pUnit->corps, pUnit->wounded_soldiers, PATH_WOUNDED_SOLDIERS );
				if ( pUnit->corps >= 0 && pUnit->corps < 3 )
					pCity->temp_wounded_soldiers[pUnit->corps] += pUnit->wounded_soldiers;
			}

			// 女将亲昵度
			if ( pCity->hero[hero_index].girlkind > 0 )
			{
				if ( g_fight.type == FIGHTTYPE_ENEMY )
				{ // 流寇
					girl_addloveexp_killenemy( pCity, pCity->hero[hero_index].kind, pCity->hero[hero_index].girlkind );
				}
				else if ( g_fight.type == FIGHTTYPE_CITY && g_army[army_index].action == ARMY_ACTION_GROUP_ATTACK )
				{ // 城战
					girl_addloveexp_citywar( pCity, pCity->hero[hero_index].kind, pCity->hero[hero_index].girlkind );
				}
				else if ( g_fight.type == FIGHTTYPE_NATION )
				{ // 国战
					girl_addloveexp_nationwar( pCity, pCity->hero[hero_index].kind, pCity->hero[hero_index].girlkind );
				}
			}

			// 对守军造成的伤害
			if ( g_fight.defense_type == MAPUNIT_TYPE_TOWN )
			{
				if ( pUnit->town_damage > 0 )
				{
					if ( g_fight.defense_index > 0 && g_fight.defense_index < g_map_town_maxcount )
					{
						float v = pUnit->town_damage / (float)g_fight.town_total_maxhp;
						int silver = (int)ceil( v * g_towninfo[g_fight.defense_index].fight_silver );
						int wood = (int)ceil( v * g_towninfo[g_fight.defense_index].fight_wood );
						int food = (int)ceil( v * g_towninfo[g_fight.defense_index].fight_food );
						g_army[army_index].silver += silver;
						g_army[army_index].wood += wood;
						g_army[army_index].food += food;

						pCity->temp_silver += silver;
						pCity->temp_wood += wood;
						pCity->temp_food += food;
					}
				}
			}
		}
	}
	else if ( pUnit->unit_type == MAPUNIT_TYPE_CITY )
	{// 战斗单元属于城池
		int city_index = pUnit->unit_index;
		if ( city_index >= 0 && city_index < g_city_maxcount )
		{ 
			if ( pUnit->type == FIGHT_UNITTYPE_GUARD )
			{ // 城墙守卫
				city_guard_subsoldiers( city_index, pUnit->index, (pUnit->maxhp - pUnit->hp) );
			}
			else if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO || pUnit->type == FIGHT_UNITTYPE_HERO )
			{ // 城池武将
				City *pCity = &g_city[city_index];
				if ( !pCity )
					return -1;
				int hero_index = city_hero_getindex( city_index, pUnit->kind );
				if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
					return -1;
				hero_changesoldiers( pCity, &pCity->hero[hero_index], -(pUnit->maxhp - pUnit->hp), PATH_FIGHT );

				// 武将经验
				if ( pUnit->exp > 0 )
				{
					hero_addexp( pCity, &pCity->hero[hero_index], pUnit->exp, PATH_FIGHT );
				}

				// 威望
				if ( pUnit->prestige > 0 )
				{
					city_changeprestige( city_index, pUnit->prestige, PATH_FIGHT );
				}

				// 伤兵恢复
				if ( pUnit->wounded_soldiers > 0 )
				{
					city_changesoldiers( city_index, pUnit->corps, pUnit->wounded_soldiers, PATH_WOUNDED_SOLDIERS );
					if ( pUnit->corps >= 0 && pUnit->corps < 3 )
						pCity->temp_wounded_soldiers[pUnit->corps] += pUnit->wounded_soldiers;
				}
			}
		}
	}
	else if ( pUnit->unit_type == MAPUNIT_TYPE_TOWN )
	{// 战斗单元属于城镇
		int townid = pUnit->unit_index;
		if ( townid > 0 && townid < g_map_town_maxcount )
		{
			if ( g_map_town[townid].nation > 0 && pUnit->index >= 0 && pUnit->index < MAP_TOWN_MONSTER_MAX )
			{ // 群雄守军不掉血
				g_map_town[townid].soldier[pUnit->index] = pUnit->hp;
				if ( g_map_town[townid].soldier[pUnit->index] < 0 )
				{
					g_map_town[townid].soldier[pUnit->index] = 0;
				}
			}
		}
	}
	else
		return 0;

	return 0;
}
int fight_lost_calc()
{
	if ( g_fight.type == FIGHTTYPE_STORY || g_fight.type == FIGHTTYPE_WORLDBOSS )
		return -1;
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		if ( g_fight.attack_unit[tmpi].offset < 0 )
			continue;
		fight_lost_calc_single( &g_fight.attack_unit[tmpi] );
	}
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		if ( g_fight.defense_unit[tmpi].offset < 0 )
			continue;
		fight_lost_calc_single( &g_fight.defense_unit[tmpi] );
	}
	return 0;
}

// 战斗信息
int fight_unit2json()
{
	g_fight.unit_json[0] = 0;
	char szTmp[512] = { 0 };
	
	// 攻击方基础信息
	short AttackShape = 0;
	short AttackLevel = 0;
	char AttackNation = 0;
	char AttackName[64] = { 0 };
	City *pAttackCity = fight_getcityptr( FIGHT_ATTACK );
	if ( pAttackCity )
	{
		AttackShape = pAttackCity->shape;
		AttackLevel = pAttackCity->level;
		AttackNation = pAttackCity->nation;
		sprintf( AttackName, "%s", pAttackCity->name );
	}
	else if ( g_fight.attack_type == MAPUNIT_TYPE_TOWN )
	{
		FightUnit *pUnit = &g_fight.attack_unit[0];

		short monsterid = pUnit->kind;
		if ( monsterid > 0 && monsterid < g_monster_maxnum )
		{
			MonsterInfo *pMonster = &g_monster[monsterid];
			AttackShape = pMonster->shape;
		}
		AttackLevel = pUnit->level;
		sprintf( AttackName, "%d", pUnit->kind );

		int townid = g_fight.attack_armyindex;
		if ( townid > 0 && townid < g_map_town_maxcount )
		{
			AttackNation = g_map_town[townid].nation;
		}
	}

	sprintf( szTmp, "{\"ft\":%d,\"fr\":%d,\"randspeed\":%d,\"a_name\":\"%s\",\"a_type\":%d,\"a_shape\":%d,\"a_nation\":%d,\"a_lv\":%d,\"a_maxhp\":%d,\"a_hp\":%d,\"a_unit\":[", 
		g_fight.type, g_fight.result, g_fight.randspeed_init, AttackName, g_fight.attack_type, AttackShape, AttackNation, AttackLevel, g_fight.attack_total_maxhp, g_fight.attack_total_hp );
	strcat( g_fight.unit_json, szTmp );

	// 攻击方每一个战斗单元信息
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		FightUnit *pUnit = &g_fight.attack_unit[tmpi];
		if ( pUnit->type == 0 )
			continue;
		char nation = 0;
		char name[64] = { 0 };
		char sflag = ',';
		if ( tmpi == 0 )
			sflag = ' ';
		
		if ( g_fight.type != FIGHTTYPE_ENEMY && g_fight.type != FIGHTTYPE_STORY && g_fight.type != FIGHTTYPE_WORLDBOSS )
		{ // 对阵流寇的战斗，每一个单元的玩家名称就不用了
			if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO || pUnit->type == FIGHT_UNITTYPE_HERO )
			{
				if ( pUnit->unit_type == MAPUNIT_TYPE_CITY )
				{
					if ( pUnit->unit_index >= 0 && pUnit->unit_index < g_city_maxcount )
					{
						sprintf( name, "%s", g_city[pUnit->unit_index].name );
						nation = g_city[pUnit->unit_index].nation;
					}
				}
				else if ( pUnit->unit_type == MAPUNIT_TYPE_ARMY )
				{
					City *pTmp = army_getcityptr( pUnit->unit_index );
					if ( pTmp )
					{
						sprintf( name, "%s", pTmp->name );
						nation = pTmp->nation;
					}
				}
			}
		}

		char expstr[128] = { 0 };
		char vwstr[64] = { 0 };
		if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO || pUnit->type == FIGHT_UNITTYPE_HERO )
		{
			// 计算经验，武将获得经验=Int(0.4*该武将击杀兵力+0.6*该武将损失兵力)
			pUnit->exp = (int)ceil( 0.4*(float)pUnit->damage + 0.6*(float)(pUnit->maxhp - pUnit->hp) );
			
			// 队长的武将格式化经验即可
			if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO )
			{
				sprintf( expstr, ",\"exp\":%d,\"mexp\":%d", pUnit->exp, pUnit->expmax );
			}

			// 计算威望
			if ( g_fight.type == FIGHTTYPE_CITY || g_fight.type == FIGHTTYPE_RES )
			{
				pUnit->prestige = (int)ceil( 0.8*(float)pUnit->damage + 0.2*(float)(pUnit->maxhp - pUnit->hp) );
			}
			else if ( g_fight.type == FIGHTTYPE_NATION )
			{
				pUnit->prestige = pUnit->maxhp - pUnit->hp;
			}
			sprintf( vwstr, ",\"vw\":%d", pUnit->prestige );

			// 伤兵恢复
			if ( pUnit->buff_forest == 1 )
			{
				pUnit->wounded_soldiers = (int)((pUnit->maxhp - pUnit->hp)*global.buff_forest / 100.0f);
			}
		}

		sprintf( szTmp, "%c{ \"i\":%d,\"t\":%d,\"n\":%d,\"na\":\"%s\",\"kd\":%d,\"sp\":%d,\"lv\":%d,\"cr\":%d,\"cs\":%d,\"mhp\":%d,\"hp\":%d,\"dmg\":%d%s%s,"
			"\"a1\":%d,\"a2\":%d,\"a3\":%d,\"a4\":%d,\"a5\":%d,\"a6\":%d,\"a7\":%d,\"a8\":%d,\"a9\":%d}", 
			sflag, pUnit->offset, pUnit->type, nation, name, pUnit->kind, pUnit->shape, pUnit->level, pUnit->color, pUnit->corps, pUnit->maxhp, pUnit->hp, pUnit->damage, expstr, vwstr,
			pUnit->attack, pUnit->defense, pUnit->troops, pUnit->attack_increase, pUnit->defense_increase, pUnit->assault, pUnit->defend, pUnit->line, pUnit->skillid_init );
		strcat( g_fight.unit_json, szTmp );
	}
	sprintf( szTmp, "]," );
	strcat( g_fight.unit_json, szTmp );

	// 防御方基础信息
	short DefenseShape = 0;
	short DefenseLevel = 0;
	char DefenseNation = 0;
	char DefenseName[64] = { 0 };
	City *pDefenseCity = fight_getcityptr( FIGHT_DEFENSE );
	if ( pDefenseCity )
	{
		DefenseShape = pDefenseCity->shape;
		DefenseLevel = pDefenseCity->level;
		DefenseNation = pDefenseCity->nation;
		sprintf( DefenseName, "%s", pDefenseCity->name );
	}
	else if ( g_fight.defense_type == MAPUNIT_TYPE_TOWN )
	{
		FightUnit *pUnit = &g_fight.defense_unit[0];

		short monsterid = pUnit->kind;
		if ( monsterid > 0 && monsterid < g_monster_maxnum )
		{
			MonsterInfo *pMonster = &g_monster[monsterid];
			DefenseShape = pMonster->shape;
		}
		DefenseLevel = pUnit->level;
		sprintf( DefenseName, "%d", pUnit->kind );

		int townid = g_fight.defense_index;
		if ( townid > 0 && townid < g_map_town_maxcount )
		{
			DefenseNation = g_map_town[townid].nation;
		}
	}
	else if ( g_fight.defense_type == MAPUNIT_TYPE_ENEMY || g_fight.defense_type == MAPUNIT_TYPE_NATIONHERO )
	{
		FightUnit *pUnit = &g_fight.defense_unit[0];

		short monsterid = pUnit->kind;
		if ( monsterid > 0 && monsterid < g_monster_maxnum )
		{
			MonsterInfo *pMonster = &g_monster[monsterid];
			DefenseShape = pMonster->shape;
		}
		DefenseLevel = pUnit->level;
		sprintf( DefenseName, "%d", pUnit->kind );
		DefenseNation = -1;
	}

	sprintf( szTmp, "\"d_name\":\"%s\",\"d_type\":%d,\"d_shape\":%d,\"d_nation\":%d,\"d_lv\":%d,\"d_maxhp\":%d,\"d_hp\":%d,\"d_unit\":[",
		DefenseName, g_fight.defense_type, DefenseShape, DefenseNation, DefenseLevel, g_fight.defense_total_maxhp, g_fight.defense_total_hp );
	strcat( g_fight.unit_json, szTmp );

	// 防御方每一个战斗单元信息
	for ( int tmpi = 0; tmpi < FIGHT_UNIT_MAX; tmpi++ )
	{
		FightUnit *pUnit = &g_fight.defense_unit[tmpi];
		if ( pUnit->type == 0 )
			continue;
		char nation = 0;
		char name[64] = { 0 };
		char sflag = ',';
		if ( tmpi == 0 )
			sflag = ' ';

		if ( g_fight.type != FIGHTTYPE_ENEMY && g_fight.type != FIGHTTYPE_STORY && g_fight.type != FIGHTTYPE_WORLDBOSS )
		{ // 对阵流寇的战斗，每一个单元的玩家名称就不用了
			if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO || pUnit->type == FIGHT_UNITTYPE_HERO )
			{
				if ( pUnit->unit_type == MAPUNIT_TYPE_CITY )
				{
					if ( pUnit->unit_index >= 0 && pUnit->unit_index < g_city_maxcount )
					{
						sprintf( name, "%s", g_city[pUnit->unit_index].name );
						nation = g_city[pUnit->unit_index].nation;
					}
				}
				else if ( pUnit->unit_type == MAPUNIT_TYPE_ARMY )
				{
					City *pTmp = army_getcityptr( pUnit->unit_index );
					if ( pTmp )
					{
						sprintf( name, "%s", pTmp->name );
						nation = pTmp->nation;
					}
				}
			}
		}

		char expstr[128] = { 0 };
		char vwstr[64] = { 0 };
		if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO || pUnit->type == FIGHT_UNITTYPE_HERO )
		{
			// 计算经验，武将获得经验=Int(0.4*该武将击杀兵力+0.6*该武将损失兵力)
			pUnit->exp = (int)ceil( 0.4*(float)pUnit->damage + 0.6*(float)(pUnit->maxhp - pUnit->hp) );

			// 队长的武将格式化经验即可
			if ( pUnit->type == FIGHT_UNITTYPE_LEADER_HERO )
			{
				sprintf( expstr, ",\"exp\":%d,\"mexp\":%d", pUnit->exp, pUnit->expmax );
			}

			// 计算威望
			if ( g_fight.type == FIGHTTYPE_CITY || g_fight.type == FIGHTTYPE_RES )
			{
				pUnit->prestige = (int)ceil( 0.8*(float)pUnit->damage + 0.2*(float)(pUnit->maxhp - pUnit->hp) );
			}
			else if ( g_fight.type == FIGHTTYPE_NATION )
			{
				pUnit->prestige = pUnit->maxhp - pUnit->hp;
			}
			sprintf( vwstr, ",\"vw\":%d", pUnit->prestige );

			// 伤兵恢复
			if ( pUnit->buff_forest == 1 )
			{
				pUnit->wounded_soldiers = (int)((pUnit->maxhp - pUnit->hp)*global.buff_forest / 100.0f);
			}
		}

		sprintf( szTmp, "%c{ \"i\":%d,\"t\":%d,\"n\":%d,\"na\":\"%s\",\"kd\":%d,\"sp\":%d,\"lv\":%d,\"cr\":%d,\"cs\":%d,\"mhp\":%d,\"hp\":%d,\"dmg\":%d%s%s,"
			"\"a1\":%d,\"a2\":%d,\"a3\":%d,\"a4\":%d,\"a5\":%d,\"a6\":%d,\"a7\":%d,\"a8\":%d,\"a9\":%d}",
			sflag, pUnit->offset, pUnit->type, nation, name, pUnit->kind, pUnit->shape, pUnit->level, pUnit->color, pUnit->corps, pUnit->maxhp, pUnit->hp, pUnit->damage, expstr, vwstr,
			pUnit->attack, pUnit->defense, pUnit->troops, pUnit->attack_increase, pUnit->defense_increase, pUnit->assault, pUnit->defend, pUnit->line, pUnit->skillid_init );
		strcat( g_fight.unit_json, szTmp );
	}
	sprintf( szTmp, "]}" );
	strcat( g_fight.unit_json, szTmp );
	return 0;
}

// 播放战斗
int fight_play( int actor_index, char *content, char *info )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	if ( !content )
		return -1;
	SLK_NetS_FightPlay pValue = { 0 };

	// 发送开始
	pValue.m_flag = 0;
	if ( !info )
	{
		pValue.m_content_length = 0;
	}
	else
	{
		strncpy( pValue.m_content, info, sizeof( char ) * 1024 );
		pValue.m_content_length = strlen( pValue.m_content );
	}
	netsend_fightplay_S( actor_index, SENDTYPE_ACTOR, &pValue );

	// 发内容过程
	pValue.m_flag = 1;
	int total_length = strlen( content );
	int offset = 0;
	while ( total_length > 0 )
	{
		int length = strlen( content + offset );
		if ( length > 1600 )
			length = 1600;
		pValue.m_content_length = length;
		memcpy( pValue.m_content, content + offset, sizeof( char )*length );
		offset += length;
		total_length -= length;
		netsend_fightplay_S( actor_index, SENDTYPE_ACTOR, &pValue );
	}

	// 发送完毕
	pValue.m_flag = 2;
	pValue.m_content_length = 0;
	netsend_fightplay_S( actor_index, SENDTYPE_ACTOR, &pValue );
	return 0;
}
