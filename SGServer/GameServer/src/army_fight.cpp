#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "db.h"
#include "define.h"
#include "dserver.h"
#include "building.h"
#include "actor.h"
#include "hero.h"
#include "area.h"
#include "actor_send.h"
#include "actor_times.h"
#include "server_netsend_auto.h"
#include "mapunit.h"
#include "fight.h"
#include "actor_notify.h"
#include "item.h"
#include "award.h"
#include "global.h"
#include "quest.h"
#include "activity.h"
#include "system.h"
#include "army.h"
#include "army_march.h"
#include "army_fight.h"
#include "city.h"
#include "map_town.h"
#include "map_enemy.h"
#include "map_res.h"
#include "map.h"

extern SConfig g_Config;
extern MYSQL *myGame;
extern MYSQL *myData;
extern Global global;

extern Actor *g_actors;
extern int g_maxactornum;

extern HeroInfo *g_HeroInfo;
extern short g_HeroCount;

extern City * g_city;
extern int g_city_maxcount;
extern int g_city_maxindex;

extern MapUnit *g_mapunit;
extern int g_mapunit_maxcount;

extern ItemKind *g_itemkind;
extern int g_itemkindnum;

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

extern Army *g_army;
extern int g_army_maxcount;
extern int g_army_count;
extern int g_army_maxindex;

// ������ս�����
int army_vs_enemy( int army_index )
{
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	MapMonsterConfig *config = map_monster_getconfig( g_army[army_index].target_index );
	if ( !config )
		return -1;
	if ( g_fight.result == FIGHT_WIN )
	{
		// ������������
		map_monster_action( g_army[army_index].target_index, MONSTER_ACTION_DEAD );

		// ���������ǳ�
		City *pCity = army_getcityptr( army_index );
		if ( pCity )
		{
			// ��õĽ���
			AwardGetInfo awardinfo = { 0 };
			AwardGetInfo fristawardinfo = { 0 };

			// ��ɱ
			char first = 0;
			if ( pCity->monster_killlevel < config->level )
			{
				pCity->monster_killlevel = config->level;
				first = 1;

				// ��ȡ��������
				awardgroup_withid( pCity->laird_actorid, config->awardgroup, PATH_FIGHT, &awardinfo );

				// ��ȡ��ɱ����
				awardgroup_withid( pCity->laird_actorid, config->first_awardgroup, PATH_FIGHT, &fristawardinfo );

				// ֪ͨ�ͻ��˸��»�ɱ�ȼ�
				int value[2] = { 0 };
				value[0] = 2;
				value[1] = pCity->monster_killlevel;
				actor_notify_value( pCity->actor_index, NOTIFY_WORLDMAP, 2, value, NULL );
			}
			else
			{
				// ��ȡ��������
				awardgroup_withid( pCity->laird_actorid, config->awardgroup, PATH_FIGHT, &awardinfo );
			}

			// �����տ񻶻��
			if ( activity_intime( ACTIVITY_SUMMER ) == 1 )
			{
				awardgroup_withid( pCity->laird_actorid, 1791, PATH_FIGHT, &fristawardinfo );
			}

			// ����ʤ���ʼ�
			army_mail_fightmonster( army_index, FIGHT_WIN, first, &g_fight, &awardinfo, &fristawardinfo );

			// ������ֵ
			quest_addvalue( pCity, QUEST_DATAINDEX_KILLMONSTER, 0, 1 );
			quest_addvalue( pCity, QUEST_DATAINDEX_KILLMONSTER_LEVEL, config->level, 1 );

			// ��������
			club_quest_addvalue( pCity->club_index, pCity, CLUB_QUESTTYPE_KILLMONSTER, config->monsterid, config->level, 1 );

			// ��Ծ����ֵ
			actor_liveness_setdata( pCity, 11, 1 );

			// ��ʱ�
			amatch_actor_killmonster( pCity, config->am_point );

			// ͳ��
			data_record_addvalue( pCity, DATA_RECORD_KILLMONSTER, 1 );
		}
	}
	else
	{
		// ��ѡ���������
		map_monster_subselected( g_army[army_index].target_index );

		// ���Ŵ�������
		map_monster_action( g_army[army_index].target_index, MONSTER_ACTION_IDLE );

		// ����ʧ���ʼ�
		army_mail_fightmonster( army_index, FIGHT_LOSE, 0, &g_fight, NULL, NULL );

		// ��������
		city_change_body( army_getcityptr( army_index ), global.fight_monster_body, PATH_FIGHT );
	}
	return 0;
}

// ��ɼ���Դ�Ĳ���ս�����
int army_vs_res( int army_index )
{
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	int gather_army_index = map_res_getarmy( g_army[army_index].target_index );
	if ( gather_army_index < 0 || gather_army_index >= g_army_maxcount )
		return -1;

	// ������ս�����ӻ�ԭ��������army��
	army_fightresult_toarmy( gather_army_index, 0 );
	army_mail_fightarmy( army_index, army_getcityptr( army_index ), army_getcityptr( gather_army_index ), &g_fight );

	// �����¼�
	club_setevent_vsres( army_index, gather_army_index, g_fight.result );

	if ( g_fight.result == FIGHT_WIN )
	{
		City *pCity = army_getcityptr( gather_army_index );
		if ( pCity )
		{
			Hero *pHero = hero_getptr( pCity, g_fight.defense_hero );
			if ( pHero )
				pHero->state = HERO_STATE_DIE;
		}
		// ����ͬʱɾ�����Լ��ı�������Ϣ��֮��ɾ�����Ҳ���������
		city_underfire_del_equal( army_getcityptr( gather_army_index ), gather_army_index );
		club_war_del_equal( army_getclubindex( gather_army_index ), gather_army_index );

		// ֱ�ӻ���ʤ���߲ɼ���
		map_res_setarmy( g_army[army_index].target_index, army_index );
		army_setstate( army_index, ARMY_STATE_GATHER );
		g_army[army_index].action = ARMY_ACTION_GATHER;

		// ����Ƿ�ȫ����û
		if ( army_fightresult_checkalldead( gather_army_index ) < 0 )
		{
			army_delete( gather_army_index );
		}
		else
		{
			army_setstate( gather_army_index, ARMY_STATE_REBACK );
		}
	}
	else
	{
		City *pCity = army_getcityptr( army_index );
		if ( pCity )
		{
			Hero *pHero = hero_getptr( pCity, g_fight.attack_hero );
			if ( pHero )
				pHero->state = HERO_STATE_DIE;
		}

		// ��Ϊʿ�����б仯������Ҫ���¼�����ԴЯ����
		army_setstate( gather_army_index, ARMY_STATE_GATHER );
	}
	return 0;
}

