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
#include "mail.h"

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
int army_vs_enemy( int army_index, Fight *pFight )
{
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	MapEnemy *enemy = map_enemy_getptr( g_army[army_index].to_index );
	if ( !enemy )
		return -1;
	MapEnemyInfo *config = map_enemy_getconfig( enemy->kind );
	if ( !config )
		return -1;
	City *pCity = army_getcityptr( army_index );
	if ( !pCity )
		return -1;
	i64 mailid = 0;

	// ���ʤ��
	if ( pFight->result == FIGHT_WIN )
	{
		// ��õĽ���
		AwardGetInfo awardinfo = { 0 };

		// ��ɱ
		char first = 0;
		if ( pCity->mokilllv < config->level )
		{
			pCity->mokilllv = (char)config->level;
			first = 1;

			// ��ȡ��������
			awardgroup_withid( pCity->actorid, config->awardgroup, PATH_ENEMY, &awardinfo );

			// ��ȡ��ɱ����
			awardgroup_withid( pCity->actorid, config->first_awardgroup, PATH_ENEMY, &awardinfo );

			// ֪ͨ�ͻ��˸��»�ɱ�ȼ�
			int value[2] = { 0 };
			value[0] = 2;
			value[1] = pCity->mokilllv;
			actor_notify_value( pCity->actor_index, NOTIFY_WORLDMAP, 2, value, NULL );
		}
		else
		{
			// ��ȡ��������
			awardgroup_withid( pCity->actorid, config->awardgroup, PATH_ENEMY, &awardinfo );
		}

		// ����ʤ���ʼ�
		char title[MAIL_TITLE_MAXSIZE] = { 0 };
		sprintf( title, "%s%d", TAG_TEXTID, 5002 );

		// ����չʾ���Ǹ�����
		char attach[MAIL_ATTACH_MAXSIZE] = { 0 };
		if ( awardinfo.count > 0 )
		{
			for ( int tmpi = 0; tmpi < awardinfo.count; tmpi++ )
			{
				if ( awardinfo.kind[tmpi] <= 0 )
					continue;
				char tempitem[32] = { 0 };
				sprintf( tempitem, "%d,%d@", awardinfo.kind[tmpi], awardinfo.num[tmpi] );
				strcat( attach, tempitem );
			}
		}

		// ����
		char content[MAIL_CONTENT_MAXSIZE] = { 0 };
		sprintf( content, "{\"text\":\"%s%d\",\"win\":1,\"name\":\"%s\",\"lv\":%d,\"pos\":\"%d,%d\",\"tpos\":\"%d,%d\",\"award\":\"%s\"}",
			TAG_TEXTID, 5502, pCity->name, config->level, pCity->posx, pCity->posy, enemy->posx, enemy->posy, attach );

		mailid = mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_FIGHT_ENEMY, title, content, "", 0 );

		//// ������ֵ
		//quest_addvalue( pCity, QUEST_DATAINDEX_KILLMONSTER, 0, 1 );
		//quest_addvalue( pCity, QUEST_DATAINDEX_KILLMONSTER_LEVEL, config->level, 1 );

		// ɾ������
		map_enemy_delete( g_army[army_index].to_index );
	}
	else
	{
		// ��ѡ���������
		map_enemy_subselected( g_army[army_index].to_index );

		// ����ʧ���ʼ�
		char title[MAIL_TITLE_MAXSIZE] = { 0 };
		sprintf( title, "%s%d", TAG_TEXTID, 5003 );

		// ����
		char content[MAIL_CONTENT_MAXSIZE] = { 0 };
		sprintf( content, "{\"text\":\"%s%d\",\"win\":0,\"name\":\"%s\",\"lv\":%d,\"pos\":\"%d,%d\",\"tpos\":\"%d,%d\"}",
			TAG_TEXTID, 5503, pCity->name, config->level, pCity->posx, pCity->posy, enemy->posx, enemy->posy );

		mailid = mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_FIGHT_ENEMY, title, content, "", 0 );
	}

	// ����ս�������ʼ�
	if ( mailid > 0 )
	{
		mail_fight( mailid, pCity->actorid, pFight->unit_json );
	}
	return 0;
}

// ��ɼ���Դ�Ĳ���ս�����
int army_vs_res( int army_index, Fight *pFight )
{
	if ( army_index < 0 || army_index >= g_army_maxcount )
		return -1;
	int gather_army_index = map_res_getarmy( g_army[army_index].to_index );
	if ( gather_army_index < 0 || gather_army_index >= g_army_maxcount )
		return -1;

	City *pCity = army_getcityptr( army_index );
	if ( !pCity )
		return -1;

	City *pTargetCity = army_getcityptr( gather_army_index );
	if ( !pTargetCity )
		return -1;

	i64 mailid = 0;
	char title[MAIL_TITLE_MAXSIZE] = { 0 };
	char content[MAIL_CONTENT_MAXSIZE] = { 0 };

	if ( pFight->result == FIGHT_WIN )
	{
		// ������ϣ�λ�ò��ܻ�
		army_gather_calc( gather_army_index );

		// ֱ�ӻ���ʤ���߲ɼ���
		map_res_setarmy( g_army[army_index].to_index, army_index );
		army_setstate( army_index, ARMY_STATE_GATHER );
		g_army[army_index].action = ARMY_ACTION_GATHER;

		// ʧ���߷���
		g_army[gather_army_index].reback = ARMY_REBACK_FIGHTLOSE;
		army_setstate( gather_army_index, ARMY_STATE_REBACK );
		
		// �����ɹ��ʼ�
		sprintf( title, "%s%d", TAG_TEXTID, 5015 );// ����ɼ���ʤ��
		sprintf( content, "{\"my\":1,\"win\":1,\"na\":\"%s\",\"n\":%d,\"lv\":%d,\"pos\":\"%d,%d\",\"tna\":\"%s\",\"tn\":%d,\"tlv\":%d,\"tpos\":\"%d,%d\"}",
			pCity->name, pCity->nation, pCity->level, pCity->posx, pCity->posy, pTargetCity->name, pTargetCity->nation, pTargetCity->level, g_army[army_index].to_posx, g_army[army_index].to_posy );

		mailid = mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_GATHER_FIGHT, title, content, "", 0 );
		mail_fight( mailid, pCity->actorid, pFight->unit_json );

		// ����ʧ���ʼ�
		sprintf( title, "%s%d", TAG_TEXTID, 5018 );// ���زɼ���ʧ��
		sprintf( content, "{\"my\":2,\"win\":0,\"na\":\"%s\",\"n\":%d,\"lv\":%d,\"pos\":\"%d,%d\",\"tna\":\"%s\",\"tn\":%d,\"tlv\":%d,\"tpos\":\"%d,%d\"}",
			pTargetCity->name, pTargetCity->nation, pTargetCity->level, g_army[army_index].to_posx, g_army[army_index].to_posy, pCity->name, pCity->nation, pCity->level, pCity->posx, pCity->posy );

		mailid = mail( pTargetCity->actor_index, pTargetCity->actorid, MAIL_TYPE_GATHER_FIGHT, title, content, "", 0 );
		mail_fight( mailid, pTargetCity->actorid, pFight->unit_json );
	}
	else
	{
		// ����ʧ���ʼ�
		sprintf( title, "%s%d", TAG_TEXTID, 5016 ); // ����ɼ���ʧ��
		sprintf( content, "{\"my\":1,\"win\":0,\"na\":\"%s\",\"n\":%d,\"lv\":%d,\"pos\":\"%d,%d\",\"tna\":\"%s\",\"tn\":%d,\"tlv\":%d,\"tpos\":\"%d,%d\"}",
			pCity->name, pCity->nation, pCity->level, pCity->posx, pCity->posy, pTargetCity->name, pTargetCity->nation, pTargetCity->level, g_army[army_index].to_posx, g_army[army_index].to_posy );

		mailid = mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_GATHER_FIGHT, title, content, "", 0 );
		mail_fight( mailid, pCity->actorid, pFight->unit_json );

		// ���سɹ��ʼ�
		sprintf( title, "%s%d", TAG_TEXTID, 5017 );// ���زɼ���ʤ��
		sprintf( content, "{\"my\":2,\"win\":1,\"na\":\"%s\",\"n\":%d,\"lv\":%d,\"pos\":\"%d,%d\",\"tna\":\"%s\",\"tn\":%d,\"tlv\":%d,\"tpos\":\"%d,%d\"}",
			pTargetCity->name, pTargetCity->nation, pTargetCity->level, g_army[army_index].to_posx, g_army[army_index].to_posy, pCity->name, pCity->nation, pCity->level, pCity->posx, pCity->posy );

		mailid = mail( pTargetCity->actor_index, pTargetCity->actorid, MAIL_TYPE_GATHER_FIGHT, title, content, "", 0 );
		mail_fight( mailid, pTargetCity->actorid, pFight->unit_json );
	}
	return 0;
}

