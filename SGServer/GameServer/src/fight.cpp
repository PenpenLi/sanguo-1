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
int fight_add_hero( int pos, char type, int index, short herokind, short level, char color, char corps, int attack, int defense, int hp, int troops, short attack_increase, short defense_increase, short assault, short defend, char line, char skillid )
{
	FightHero *pHero = NULL;
	if ( pos == FIGHT_ATTACK )
	{
		if ( g_fight.attack_hero_num < FIGHT_HERO_MAX - 1 )
		{
			pHero = &g_fight.attack_hero[g_fight.attack_hero_num];
			pHero->offset = g_fight.attack_hero_num;
			g_fight.attack_hero_num += 1;
			g_fight.attack_total_hp += hp;
			g_fight.attack_total_maxhp += hp;
		}
	}
	else
	{
		if ( g_fight.defense_hero_num < FIGHT_HERO_MAX - 1 )
		{
			pHero = &g_fight.defense_hero[g_fight.defense_hero_num];
			pHero->offset = g_fight.defense_hero_num;
			g_fight.defense_hero_num += 1;
			g_fight.defense_total_hp += hp;
			g_fight.defense_total_maxhp += hp;
		}
	}
	if ( !pHero )
		return -1;

	pHero->type = type;
	pHero->index = index;
	pHero->herokind = herokind;
	pHero->level = level;
	pHero->color = color;
	pHero->corps = corps;
	pHero->attack = attack;
	pHero->defense = defense;
	pHero->hp = hp;
	pHero->maxhp = hp;
	pHero->troops = troops;
	pHero->attack_increase = attack_increase;
	pHero->defense_increase = defense_increase;
	pHero->assault = assault;
	pHero->defend = defend;	
	pHero->line = line;
	pHero->skillid = skillid;
	pHero->line_left = line;
	pHero->line_hp = (int)ceil( hp / (float)line);
	pHero->damage = 0;
	fight_debug( "[%s] idx:%d,kind:%d,level:%d,color:%d,corps:%d,attack:%d,defense:%d,hp:%d,troops:%d,attack_inc:%d,defense_inc:%d,assault:%d,defend:%d,line:%d,linehp:%d,skill:%d", 
		s_fight_posname[pos], pHero->offset, herokind, level, color, corps, attack, defense, hp, troops, attack_increase, defense_increase, assault, defend, line, pHero->line_hp, skillid );
	return 0;
}

int fight_start( int attack_armyindex, char defense_type, int defense_index )
{
	g_gm_isout = 0;
	g_gm_outresult[0] = '\0';
	if ( attack_armyindex < 0 || attack_armyindex >= g_army_maxcount )
		return -1;

	memset( &g_fight, 0, sizeof( Fight ) );
	g_fight.attack_armyindex = -1;
	g_fight.defense_index = -1;
	// Ϊ�ⳡս������һ��������ӣ����Ҫ�������ֵ����֤�ͻ��˷�����ͬ��
	g_fight.randspeed = (int)time( NULL );

	g_fight.attack_armyindex = attack_armyindex;
	g_fight.defense_type = defense_type;
	g_fight.defense_index = defense_index;

	fight_debug( "\n\n============================================== FIGHT START ==============================================" );
	int result = 0;

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
			int hero_index = city_hero_getindex( pCity->index, g_army[attack_armyindex].herokind[0] );
			if ( hero_index < 0 || hero_index >= HERO_CITY_MAX )
				continue;
			Hero *pHero = &pCity->hero[hero_index];
			HeroInfoConfig *config = hero_getconfig( pHero->kind, pHero->color );
			if ( !config )
				continue;
			fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_CITY, pCity->index, herokind, pHero->level, pHero->color, (char)config->corps,
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
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_CITY, pCity->index, 10000 + monsterid, pCity->guard[tmpi].level, pCity->guard[tmpi].color, (char)pCity->guard[tmpi].corps,
				config->attack, config->defense, pCity->guard[tmpi].soldiers, config->troops, config->attack_increase, config->defense_increase, config->assault, config->defend, config->line, 0 );
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
			fight_add_hero( FIGHT_DEFENSE, MAPUNIT_TYPE_CITY, pCity->index, pHero->kind, pHero->level, pHero->color, (char)config->corps,
				pHero->attack, pHero->defense, pHero->soldiers, pHero->troops, pHero->attack_increase, pHero->defense_increase, pHero->assault, pHero->defend, hero_getline( pCity ), (char)config->skillid );
		}
		// ����Э���Ĳ���
		for ( int index = 0; index < CITY_HELPDEFENSE_MAX; index++ )
		{
			int army_index = pCity->help_armyindex[index];
			if ( army_index < 0 )
				continue;
			if ( g_army[army_index].state != ARMY_STATE_HELP )
				continue;
			
		}

	}
	// ������Ϊפ���Ĳ���
	else if ( defense_type == MAPUNIT_TYPE_ARMY )
	{
	}
	// ������Ϊ����
	else if ( defense_type == MAPUNIT_TYPE_TOWN )
	{
	}
	// ������Ϊ����
	else if ( defense_type == MAPUNIT_TYPE_ENEMY )
	{
		if ( defense_index < 0 || defense_index >= g_map_res_maxcount )
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
			fight_add_hero( FIGHT_DEFENSE, 0, -1, -pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
				pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill );
		}
	}
	// ������Ϊ��Դ��Ĳ���
	else if ( defense_type == MAPUNIT_TYPE_RES )
	{
		int army_index = map_res_getarmy( defense_index );
		if ( army_index < 0 || army_index >= g_army_maxcount )
			return -1;
		Army *pArmy = &g_army[army_index];
		if ( !pArmy )
			return -1;

	}
	// ������ΪҰ��
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
			fight_add_hero( FIGHT_ATTACK, MAPUNIT_TYPE_CITY, pCity->index, herokind, pHero->level, pHero->color, (char)config->corps,
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
		fight_add_hero( FIGHT_DEFENSE, 0, -1, -pMonster->shape, pMonster->level, (char)pMonster->color, (char)pMonster->corps,
			pMonster->attack, pMonster->defense, pMonster->troops, pMonster->troops, pMonster->attack_increase, pMonster->defense_increase, pMonster->assault, pMonster->defend, (char)pMonster->line, (char)pMonster->skill );
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
	FightHero *pAttackHero = fight_nextptr( FIGHT_ATTACK );
	if ( !pAttackHero )
		return FIGHT_LOSE;

	// ���ط���ǰ����Ӣ��
	FightHero *pDefenseHero = fight_nextptr( FIGHT_DEFENSE );
	if ( !pDefenseHero )
		return FIGHT_WIN;


	// ˫��ʹ�ó�������
	attack_damage = fight_useskill( FIGHT_ATTACK, pAttackHero, pDefenseHero );
	defense_damage = fight_useskill( FIGHT_DEFENSE, pDefenseHero, pAttackHero );
	if ( attack_damage > 0 )
	{
		result = fight_changehp( FIGHT_ATTACK, pDefenseHero, attack_damage );
		if ( result > 0 )
			return result;
	}
	if ( defense_damage > 0 )
	{
		result = fight_changehp( FIGHT_DEFENSE, pAttackHero, defense_damage );
		if ( result > 0 )
			return result;
	}

	// ˫�����ֹ���
	attack_damage = fight_damage( FIGHT_ATTACK, pAttackHero, pDefenseHero );
	attack_damage = fight_damage( FIGHT_DEFENSE, pDefenseHero, pAttackHero );
	if ( attack_damage > 0 )
	{
		result = fight_changehp( FIGHT_ATTACK, pDefenseHero, attack_damage );
		if ( result > 0 )
			return result;
	}
	if ( defense_damage > 0 )
	{
		result = fight_changehp( FIGHT_DEFENSE, pAttackHero, defense_damage );
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
int fight_useskill( int pos, FightHero *pHero, FightHero *pTargetHero )
{
	int true_damage = 0;
	int damage = 0;
	int skillid = pHero->skillid;
	if ( skillid > 0 && skillid < g_hero_skill_maxnum )
	{ // �������ͷ��佫��
		int random = random_custom( g_hero_skill[skillid].randmin, g_hero_skill[skillid].randmax, &g_fight.randspeed );
		damage = (int)ceil( ( pHero->hp * (g_hero_skill[skillid].value / FIGHT_FLOAT) * (random / FIGHT_FLOAT) ) );
		true_damage = damage;
		damage = min( damage, pTargetHero->line_hp );
		fight_debug( "[%s](skill) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pHero->offset, pHero->herokind, damage, true_damage, pTargetHero->offset, pTargetHero->herokind, pTargetHero->line_left, pTargetHero->line_hp, damage, pTargetHero->line_hp - damage );
		pHero->skillid = 0;
		pHero->damage += damage;	
	}
	return damage;
}

// ��ͨ����
int fight_damage( int pos, FightHero *pHero, FightHero *pTargetHero )
{
	int true_damage = 0;
	int damage = 0;
	// 1.�����ж��Ƿ�����
	int dodge = random_custom( 1, 100, &g_fight.randspeed );
	if ( dodge <= global.fight_dodge )
	{ // ������
		fight_debug( "[%s](miss) idx:%d,kind:%d,damage:%d,target_idx:%d,target_kind:%d,line_left:%d,line_hp:%d", s_fight_posname[pos], pHero->offset, pHero->herokind, 0, pTargetHero->offset, pTargetHero->herokind, pTargetHero->line_left, pTargetHero->line_hp );
	}
	else
	{
		// 2.��������˺�
		// �����˺�=������������-������������*��0.5+0.5*������ǰ����/������ǰ������*���ֿ���ϵ��*ս���������ϵ��+����ǿ��-����ǿ��+��������-�����س�
		damage = (int)ceil( (pHero->attack - pTargetHero->defense) * ((global.fight_v1 / FIGHT_FLOAT) + (global.fight_v2 / FIGHT_FLOAT) * pHero->line_hp / (float)pTargetHero->line_hp) * (_corpsmul( pHero->corps, pTargetHero->corps ) / FIGHT_FLOAT) * (global.fight_control_value / FIGHT_FLOAT) );
		damage += (pHero->attack_increase - pTargetHero->defense_increase);
		damage += (pHero->assault - pTargetHero->defend);

		// 3.�趨�����˺�
		// ���������˺� = Max���������� * 5 % �������˺���
		damage = max( (int)ceil( pHero->attack * (global.fight_attackmin_value / FIGHT_FLOAT) ), damage );

		// 4.���㱩���˺�
		int random = random_custom( global.fight_damage_randmin, global.fight_damage_randmax, &g_fight.randspeed );
		int crit = random_custom( 1, 100, &g_fight.randspeed );
		if ( crit <= global.fight_crit_odds )
		{
			damage = (int)ceil( damage * (global.fight_crit_damage / FIGHT_FLOAT) * (random / FIGHT_FLOAT) );
			true_damage = damage;
			damage = min( damage, pTargetHero->line_hp );
			fight_debug( "[%s](crit) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pHero->offset, pHero->herokind, damage, true_damage, pTargetHero->offset, pTargetHero->herokind, pTargetHero->line_left, pTargetHero->line_hp, damage, pTargetHero->line_hp - damage );
		}
		else
		{// û����
			damage = (int)ceil( damage * (random / FIGHT_FLOAT) );
			true_damage = damage;
			damage = min( damage, pTargetHero->line_hp );
			fight_debug( "[%s](default) idx:%d,kind:%d,damage:%d(%d),target_idx:%d,target_kind:%d,line_left:%d,line_hp:(%d-%d=%d)", s_fight_posname[pos], pHero->offset, pHero->herokind, damage, true_damage, pTargetHero->offset, pTargetHero->herokind, pTargetHero->line_left, pTargetHero->line_hp, damage, pTargetHero->line_hp - damage );
		}
		pHero->damage += damage;
	}
	return damage;
}

// ��Ѫ
int fight_changehp( int pos, FightHero *pTargetHero, int damage )
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

	pTargetHero->hp -= damage;
	pTargetHero->line_hp -= damage;
	if ( pTargetHero->line_hp <= 0 )
	{
		pTargetHero->line_left -= 1;
		if ( pTargetHero->line_left > 0 )
		{ // ����һ��
			pTargetHero->line_hp = (int)ceil( pTargetHero->maxhp / (float)pTargetHero->line );
		}
		else
		{
			pTargetHero->hp = 0;
			if ( pos == FIGHT_ATTACK )
			{
				pTargetHero = fight_nextptr( FIGHT_DEFENSE );
				if ( !pTargetHero )
					return FIGHT_WIN;
				fight_debug( "[%s](up) idx:%d,kind:%d", s_fight_posname[FIGHT_DEFENSE], pTargetHero->offset, pTargetHero->herokind );
			}
			else
			{
				pTargetHero = fight_nextptr( FIGHT_ATTACK );
				if ( !pTargetHero )
					return FIGHT_LOSE;
				fight_debug( "[%s](up) idx:%d,kind:%d", s_fight_posname[FIGHT_ATTACK], pTargetHero->offset, pTargetHero->herokind );
			}
		}
	}
	return 0;
}

// ����Ӣ��
FightHero *fight_nextptr( int pos )
{
	if ( pos == FIGHT_ATTACK )
	{
		if ( g_fight.attack_hero_index >= 0 && g_fight.attack_hero_index < FIGHT_HERO_MAX )
		{
			for ( int tmpi = g_fight.attack_hero_index; tmpi < g_fight.attack_hero_num; tmpi++ )
			{
				if ( g_fight.attack_hero[tmpi].hp > 0 )
				{
					g_fight.attack_hero_index = tmpi;
					return &g_fight.attack_hero[tmpi];
				}
			}
		}
	}
	else
	{
		if ( g_fight.defense_hero_index >= 0 && g_fight.defense_hero_index < FIGHT_HERO_MAX )
		{
			for ( int tmpi = g_fight.defense_hero_index; tmpi < g_fight.defense_hero_num; tmpi++ )
			{
				if ( g_fight.defense_hero[tmpi].hp > 0 )
				{
					g_fight.defense_hero_index = tmpi;
					return &g_fight.defense_hero[tmpi];
				}
			}
		}
	}
	return NULL;
}

