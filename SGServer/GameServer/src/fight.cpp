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
#include "server_netsend_auto.h"
#include "system.h"
#include "item.h"
#include "actor_notify.h"
#include "fight.h"

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

extern Map g_map;

Fight g_fight;
extern char g_gm_outresult[MAX_OUTRESULT_LEN];
char g_gm_isout = 0;

static char *s_fight_posname[] = { "", "attack", "defense" };

// �������
#define FIGHT_DEBUG
int fight_debug( const char *format, ... )
{
#ifdef FIGHT_DEBUG
	int rtn = 0;
	va_list arg_ptr;

	// ��¼����log
	va_start( arg_ptr, format );
	rtn = u_log( 1, format, arg_ptr );
	va_end( arg_ptr );

	// GMƽ̨����
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

// ��ս�������һ��Ӣ��
int fight_add_hero( int pos, int army_index, char type, int city_index, int index, int kind, short shape, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid )
{
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

	pUnit->type = type;
	pUnit->army_index = army_index;
	pUnit->city_index = city_index;
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
	pUnit->assault = assault;
	pUnit->defend = defend;
	pUnit->line = line;
	pUnit->skillid = skillid;
	pUnit->line_left = line;
	pUnit->line_hp = (int)ceil( hp / (float)line );
	pUnit->damage = 0;

	char name[64] = { 0 };
	if ( type == FIGHT_UNITTYPE_HERO )
	{
		if ( city_index >= 0 && city_index < g_city_maxcount )
		{
			sprintf( name, "%s", g_city[city_index].name );
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
		g_fight.attack_unit[tmpi].army_index = -1;
		g_fight.attack_unit[tmpi].city_index = -1;
		g_fight.attack_unit[tmpi].index = -1;

		g_fight.defense_unit[tmpi].offset = -1;
		g_fight.defense_unit[tmpi].army_index = -1;
		g_fight.defense_unit[tmpi].city_index = -1;
		g_fight.defense_unit[tmpi].index = -1;
	}
	g_fight.attack_armyindex = -1;
	g_fight.defense_index = -1;
	// Ϊ�ⳡս������һ��������ӣ����Ҫ�������ֵ����֤�ͻ��˷�����ͬ��
	g_fight.randspeed = (int)time( NULL );

	g_fight.attack_armyindex = attack_armyindex;
	g_fight.attack_type = g_army[attack_armyindex].from_type;
	g_fight.defense_type = defense_type;
	g_fight.defense_index = defense_index;

	fight_debug( "\n\n============================================== FIGHT START ==============================================" );
	int result = 0;

	// ������Ϊ���
	if ( g_army[attack_armyindex].from_type == MAPUNIT_TYPE_CITY )
	{
		// ��������սӢ��
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
			fight_add_hero( FIGHT_ATTACK, attack_armyindex, FIGHT_UNITTYPE_HERO, pCity->index, tmpi, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity ), (char)config->skillid );

		}
	}
	

	// ������Ϊ��ҳǳ�
	if ( defense_type == MAPUNIT_TYPE_CITY )
	{
		if ( defense_index < 0 || defense_index >= g_city_maxcount )
			return -1;
		City *pCity = &g_city[defense_index];
		if ( !pCity )
			return -1;

		// ���ϳ�ǽ����
		for ( int tmpi = 0; tmpi < CITY_GUARD_MAX; tmpi++ )
		{
			int monsterid = pCity->guard[tmpi].monsterid;
			if ( monsterid <= 0 )
				continue;
			CityGuardInfoConfig *config = city_guard_config( monsterid, pCity->guard[tmpi].color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_DEFENSE, -1, FIGHT_UNITTYPE_GUARD, pCity->index, tmpi, monsterid, pCity->guard[tmpi].shape, pCity->guard[tmpi].level, pCity->guard[tmpi].color, (char)pCity->guard[tmpi].corps,
				config->attack, config->defense, pCity->guard[tmpi].soldiers, config->troops, config->attack_increase, config->defense_increase, config->assault, config->defend, (char)config->line, 0 );
		}
		// �����������
		for ( int tmpi = 0; tmpi < 4; tmpi++ )
		{
			City *pCity = army_getcityptr_target( attack_armyindex );
			if ( !pCity )
				continue;
			Hero *pHero = &pCity->hero[tmpi];
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_DEFENSE, -1, FIGHT_UNITTYPE_HERO, pCity->index, tmpi, pHero->kind, pHero->kind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity ), (char)config->skillid );
		}
		// ����פ���Ĳ���
		for ( int index = 0; index < CITY_HELPDEFENSE_MAX; index++ )
		{
			int army_index = pCity->help_armyindex[index];
			if ( army_index < 0 )
				continue;
			if ( g_army[army_index].state != ARMY_STATE_HELP )
				continue;
			
		}
		g_fight.type = FIGHTTYPE_CITY;
	}
	// ������Ϊפ���Ĳ���
	else if ( defense_type == MAPUNIT_TYPE_ARMY )
	{
	}
	// ������Ϊ����
	else if ( defense_type == MAPUNIT_TYPE_TOWN )
	{
		g_fight.type = FIGHTTYPE_NATION;
	}
	// ������Ϊ����
	else if ( defense_type == MAPUNIT_TYPE_ENEMY )
	{
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
			fight_add_hero( FIGHT_DEFENSE, -1, FIGHT_UNITTYPE_MONSTER, -1, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
				pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill );
		}
		g_fight.type = FIGHTTYPE_ENEMY;
	}
	// ������Ϊ��Դ��Ĳ���
	else if ( defense_type == MAPUNIT_TYPE_RES )
	{
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
		fight_add_hero( FIGHT_DEFENSE, army_index, FIGHT_UNITTYPE_HERO, pCity->index, 0, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
			pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity ), (char)config->skillid );
		g_fight.type = FIGHTTYPE_RES;

	}
	else
	{
		return -1;
	}
	
	// ս���غ�
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
		//  ����%�غ�
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

	// ��Ϣתjson
	fight_unit2json();
	return 0;
}

// ս������-����ս��
int fight_start_bystory( int actor_index, SLK_NetC_StoryBattle *pValue, int chapter, int rank )
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
	// Ϊ�ⳡս������һ��������ӣ����Ҫ�������ֵ����֤�ͻ��˷�����ͬ��
	g_fight.randspeed = (int)time( NULL );

	fight_debug( "\n\n============================================== STORY FIGHT START ==============================================" );
	int result = 0;

	// ��ҳ�սӢ��
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
			fight_add_hero( FIGHT_ATTACK, -1, FIGHT_UNITTYPE_HERO, pCity->index, -1, herokind, herokind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity ), (char)config->skillid );
		}
	}

	// ����Ӣ��
	for ( int tmpi = 0; tmpi < 4; tmpi++ )
	{
		int monsterid = g_storyinfo[chapter].config[rank].monsterid[tmpi];
		if ( monsterid <= 0 || monsterid >= g_monster_maxnum )
			continue;
		MonsterInfo *pMonster = &g_monster[monsterid];
		if ( !pMonster )
			continue;
		fight_add_hero( FIGHT_DEFENSE, -1, FIGHT_UNITTYPE_MONSTER, -1, tmpi, monsterid, pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
			pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill );
	}
	g_fight.type = FIGHTTYPE_STORY;

	// ս���غ�
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
		//  ����%�غ�
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
	return 0;
}

// ս��ÿһ�غ�
int fight_oneturn()
{
	int attack_damage = 0;
	int defense_damage = 0;
	int result = 0;
	g_fight.turns += 1;
	fight_debug( "--------------------------- [turns-%d] ---------------------------", g_fight.turns );

	// ��������ǰ����Ӣ��
	FightUnit *pAttackUnit = fight_nextptr( FIGHT_ATTACK );
	if ( !pAttackUnit )
		return FIGHT_LOSE;

	// ���ط���ǰ����Ӣ��
	FightUnit *pDefenseUnit = fight_nextptr( FIGHT_DEFENSE );
	if ( !pDefenseUnit )
		return FIGHT_WIN;


	// ˫��ʹ�ó�������
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

	// ˫�����ֹ���
	attack_damage = fight_damage( FIGHT_ATTACK, pAttackUnit, pDefenseUnit );
	attack_damage = fight_damage( FIGHT_DEFENSE, pDefenseUnit, pAttackUnit );
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

// �������ϵ��
static int _corpsmul( int corps, int target_corps )
{
	if ( corps < 0 || corps >= g_hero_corpsmul_maxnum )
		return FIGHT_INT;
	if ( target_corps < 0 || target_corps >= g_hero_corpsmul_maxnum )
		return FIGHT_INT;
	return g_hero_corpsmul[corps].target_corps[target_corps];
}

// ʹ�ó�������
int fight_useskill( int pos, FightUnit *pUnit, FightUnit *pTargetUnit )
{
	int true_damage = 0;
	int damage = 0;
	int skillid = pUnit->skillid;
	if ( skillid > 0 && skillid < g_hero_skill_maxnum )
	{ // �������ͷ��佫��
		int random = random_custom( g_hero_skill[skillid].randmin, g_hero_skill[skillid].randmax, &g_fight.randspeed );
		damage = (int)ceil( ( pUnit->hp * (g_hero_skill[skillid].value / FIGHT_FLOAT) * (random / FIGHT_FLOAT)) );
		true_damage = damage;
		damage = min( damage, pTargetUnit->line_hp );
		fight_debug( "[%s](skill) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pUnit->offset, pUnit->kind, damage, true_damage, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp, damage, pTargetUnit->line_hp - damage );
		pUnit->skillid = 0;
		pUnit->damage += damage;
	}
	return damage;
}

// ��ͨ����
int fight_damage( int pos, FightUnit *pUnit, FightUnit *pTargetUnit )
{
	int true_damage = 0;
	int damage = 0;
	// 1.�����ж��Ƿ�����
	int dodge = random_custom( 1, 100, &g_fight.randspeed );
	if ( dodge <= global.fight_dodge )
	{ // ������
		fight_debug( "[%s](miss) idx:%d,kind:%d,damage:%d,target_idx:%d,target_kind:%d,line_left:%d,line_hp:%d", s_fight_posname[pos], pUnit->offset, pUnit->kind, 0, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp );
	}
	else
	{
		// 2.��������˺�
		// �����˺�=������������-������������*��0.5+0.5*������ǰ����/������ǰ������*���ֿ���ϵ��*ս���������ϵ��+����ǿ��-����ǿ��+��������-�����س�
		damage = (int)ceil( (pUnit->attack - pTargetUnit->defense) * ((global.fight_v1 / FIGHT_FLOAT) + (global.fight_v2 / FIGHT_FLOAT) * pUnit->line_hp / (float)pTargetUnit->line_hp) * (_corpsmul( pUnit->corps, pTargetUnit->corps ) / FIGHT_FLOAT) * (global.fight_control_value / FIGHT_FLOAT) );
		damage += (pUnit->attack_increase - pTargetUnit->defense_increase);
		damage += (pUnit->assault - pTargetUnit->defend);

		// 3.�趨�����˺�
		// ���������˺� = Max���������� * 5 % �������˺���
		damage = max( (int)ceil( pUnit->attack * (global.fight_attackmin_value / FIGHT_FLOAT) ), damage );

		// 4.���㱩���˺�
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
		{// û����
			damage = (int)ceil( damage * (random / FIGHT_FLOAT) );
			true_damage = damage;
			damage = min( damage, pTargetUnit->line_hp );
			fight_debug( "[%s](default) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pUnit->offset, pUnit->kind, damage, true_damage, pTargetUnit->offset, pTargetUnit->kind, pTargetUnit->line_left, pTargetUnit->line_hp, damage, pTargetUnit->line_hp - damage );
		}
		pUnit->damage += damage;
	}
	return damage;
}

// ��Ѫ
int fight_changehp( int pos, FightUnit *pTargetUnit, int damage )
{
	// �ܻ�ɱ��������
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
	pTargetUnit->line_hp -= damage;
	if ( pTargetUnit->line_hp <= 0 )
	{
		pTargetUnit->line_left -= 1;
		if ( pTargetUnit->line_left > 0 )
		{ // ����һ��
			pTargetUnit->line_hp = (int)ceil( pTargetUnit->maxhp / (float)pTargetUnit->line );
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

// ����Ӣ��
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

// ��ȡ˫���ǳ�ָ��
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
		else if ( g_fight.type == FIGHTTYPE_CITY || g_fight.type == FIGHTTYPE_NATION || g_fight.type == FIGHTTYPE_ENEMY || g_fight.type == FIGHTTYPE_RES )
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
		// ֻ�з�����Ϊ�ǳغ�פ�����гǳ�
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

// ս������
int fight_lost_calc_single( FightUnit *pUnit )
{
	if ( pUnit->army_index >= 0 && pUnit->army_index < g_army_maxcount )
	{ // ս����Ԫ����һ������
		City *pCity = army_getcityptr( pUnit->army_index );
		if ( !pCity )
			return -1;
		int hero_index = city_hero_getindex( pCity->index, pUnit->kind );
		if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
			return -1;
		hero_changesoldiers( pCity, &pCity->hero[hero_index], (pUnit->maxhp - pUnit->hp), PATH_FIGHT );
	}
	else if ( pUnit->city_index >= 0 && pUnit->city_index < g_city_maxcount )
	{ // ս�����ڳǳ�

	}
	else
		return 0;


	return 0;
}
int fight_lost_calc()
{
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
		fight_lost_calc_single( &g_fight.attack_unit[tmpi] );
	}
	return 0;
}

// ս����Ϣ
int fight_unit2json()
{
	g_fight.unit_json[0] = 0;
	char szTmp[256] = { 0 };
	
	// ������������Ϣ
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

	}

	sprintf( szTmp, "{\"a_name\":\"%s\",\"a_type\":%d,\"a_shape\":%d,\"a_nation\":%d,\"a_lv\":%d,\"a_maxhp\":%d,\"a_hp\":%d,\"a_unit\":[", 
		AttackName, g_fight.attack_type, AttackShape, AttackNation, AttackLevel, g_fight.attack_total_maxhp, g_fight.attack_total_hp );
	strcat( g_fight.unit_json, szTmp );

	// ������ÿһ��ս����Ԫ��Ϣ
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
		
		if ( g_fight.type != FIGHTTYPE_ENEMY )
		{ // �������ܵ�ս����ÿһ����Ԫ��������ƾͲ�����
			if ( pUnit->type == FIGHT_UNITTYPE_HERO )
			{
				if ( pUnit->city_index >= 0 && pUnit->city_index < g_city_maxcount )
				{
					sprintf( name, "%s", g_city[pUnit->city_index].name );
					nation = g_city[pUnit->city_index].nation;
				}
			}
		}
		sprintf( szTmp, "%c{ \"i\":%d,\"t\":%d,\"n\":%d,\"na\":\"%s\",\"kd\":%d,\"sp\":%d,\"lv\":%d,\"cr\":%d,\"cs\":%d,\"mhp\":%d,\"hp\":%d,\"dmg\":%d,\"vw\":%d}", 
			sflag, pUnit->offset, pUnit->type, nation, name, pUnit->kind, pUnit->shape, pUnit->level, pUnit->color, pUnit->corps, pUnit->maxhp, pUnit->hp, pUnit->damage, 0 );
		strcat( g_fight.unit_json, szTmp );
	}
	sprintf( szTmp, "]," );
	strcat( g_fight.unit_json, szTmp );

	// ������������Ϣ
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

	}
	else if ( g_fight.defense_type == MAPUNIT_TYPE_ENEMY )
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

	// ������ÿһ��ս����Ԫ��Ϣ
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

		if ( g_fight.type != FIGHTTYPE_ENEMY )
		{ // �������ܵ�ս����ÿһ����Ԫ��������ƾͲ�����
			if ( pUnit->type == FIGHT_UNITTYPE_HERO )
			{
				if ( pUnit->city_index >= 0 && pUnit->city_index < g_city_maxcount )
				{
					sprintf( name, "%s", g_city[pUnit->city_index].name );
					nation = g_city[pUnit->city_index].nation;
				}
			}
		}
		sprintf( szTmp, "%c{ \"i\":%d,\"t\":%d,\"n\":%d,\"na\":\"%s\",\"kd\":%d,\"sp\":%d,\"lv\":%d,\"cr\":%d,\"cs\":%d,\"mhp\":%d,\"hp\":%d,\"dmg\":%d,\"vw\":%d}",
			sflag, pUnit->offset, pUnit->type, nation, name, pUnit->kind, pUnit->shape, pUnit->level, pUnit->color, pUnit->corps, pUnit->maxhp, pUnit->hp, pUnit->damage, 0 );
		strcat( g_fight.unit_json, szTmp );
	}
	sprintf( szTmp, "]}" );
	strcat( g_fight.unit_json, szTmp );
	return 0;
}
