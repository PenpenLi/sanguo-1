#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <mysql.h>
#include "db.h"
#include "actor.h"
#include "gmcmd.h"
#include "system.h"
#include "script.h"
#include "map.h"
#include "item.h"
#include "equip.h"
#include "award.h"
#include "global_netprocess.h"
#include "timegmcmd.h"
#include "global.h"
#include "login.h"
#include "actor_notify.h"
#include "gameproc.h"
#include "city.h"
#include "city_tech.h"
#include "chat.h"
#include "vip.h"
#include "hero.h"
#include "mail.h"
#include "building.h"
#include "map_town.h"
#include "quest.h"
#include "world_quest.h"
#include "world_boss.h"
#include "actor_times.h"
#include "king_war.h"
#include "pay.h"
#include "activity.h"
#include "nation.h"
#include "nation_hero.h"
#include "story.h"
#include "city_attr.h"

extern Global global;
extern MYSQL *myGame;
extern Actor *g_actors;
extern int g_actornum;
extern int g_maxactornum;
extern char g_bServerIsInit;
extern char g_test_mod;

int actor_command( int actor_index, short cmd, int *pValue, char *pMsg )
{
	if ( g_bServerIsInit == 0 )
		return -1;
	
	int tmpi;
	char szMsg[1024] = { 0 };
	int actorid = pValue[3];
	City *pCity = NULL;

	if ( cmd == GMC_PAYBAG || cmd == GMC_ACTIVITY || cmd == GMC_NATIONRANK || cmd == GMC_NATIONOF )
	{
		actorid = 0;
	}

	// ��Щָ������������
	if ( actorid > 0 && (cmd == GMC_SYSTALK) )
	{
		int target_index = actor_getindex_withid( actorid );
		if ( target_index < 0 )
		{
			return GMR_NOT_ONLINE;
		}
	}

	if ( actor_index >= 0 )
	{ // �ͻ���ʹ��GMָ�����
#ifndef	WIN32
		if ( g_actors[actor_index].admin < 100 )
		{
			system_talkto( actor_index, "Access denied!", 0 );
			return GMR_ACCESS_DENIED;
		}
#endif // DEBUG
		if ( pMsg )
			write_gamelog( "<GmProcess>cmd:%d value:%d,%d,%d,%d,%s [%s(%d)]", cmd, pValue[0], pValue[1], pValue[2], pValue[3], pMsg, g_actors[actor_index].name, g_actors[actor_index].actorid );
		else
			write_gamelog( "<GmProcess>cmd:%d value:%d,%d,%d,%d,NULL [%s(%d)]", cmd, pValue[0], pValue[1], pValue[2], pValue[3], g_actors[actor_index].name, g_actors[actor_index].actorid );

		if ( actorid > 0 )
			pCity = city_getptr_withactorid( actorid ); // ������ʹ��
		else
			pCity = city_getptr( actor_index ); // �Լ�ʹ��

		if ( !pCity )
			return GMR_ERROR;
		
	}
	else
	{ // GM����ʹ�����
		if ( pMsg )
			write_gamelog( "<GmTools>cmd:%d value:%d,%d,%d,%d,%s", cmd, pValue[0], pValue[1], pValue[2], pValue[3], pMsg );
		else
			write_gamelog( "<GmTools>cmd:%d value:%d,%d,%d,%d,NULL", cmd, pValue[0], pValue[1], pValue[2], pValue[3] );

		if ( actorid > 0 )
		{
			pCity = city_getptr_withactorid( actorid );
			if ( !pCity )
				return GMR_ERROR;
		}
	}

	switch ( cmd )
	{
	case GMC_TEST:
		if ( pValue[0] == 0 )
		{
			g_test_mod = 0;
		}
		else if ( pValue[0] == 1 )
		{
			g_test_mod = 1;
		}
		else if ( pValue[0] == 2 )
		{
			if ( pCity )
			{
				data_record_addvalue( pCity, DATA_RECORD_KILLENEMY, 1 );
				worldquest_checkcomplete( pCity->actor_index, 0 );
			}
		}
		else if ( pValue[0] == 3 )
		{
			map_town_attack_checkstart();
		}
		else if ( pValue[0] == 4 )
		{
			if ( pValue[1] == 0 )
			{
				time_t t;
				time( &t );
				t += 60;
				struct tm *nowtime = localtime( &t );
				global.kingwar_activity_week = nowtime->tm_wday;
				global.kingwar_activity_hour = nowtime->tm_hour;
				global.kingwar_activity_minute = nowtime->tm_min;
				kingwar_activity_sendinfo( -1 );
			}
			else if( pValue[1] == -1 )
			{
				extern int g_kingwar_activity_endstamp; // �����ʱ���
				g_kingwar_activity_endstamp = (int)time( NULL ) + 30;
				kingwar_activity_sendinfo( -1 );
			}	
			else if ( pValue[1] == -2 )
			{
				extern int g_kingwar_treasure_endstamp; // �ڱ�����ʱ���
				g_kingwar_treasure_endstamp = (int)time( NULL ) + 30;
				kingwar_treasure_sendinfo( -1 );
			}
		}
		else if ( pValue[0] == 5 )
		{
			if ( pCity )
			{
				pCity->mokilllv = pValue[1];
				// ֪ͨ�ͻ��˸��»�ɱ�ȼ�
				int value[2] = { 0 };
				value[0] = 2;
				value[1] = pCity->mokilllv;
				actor_notify_value( pCity->actor_index, NOTIFY_WORLDMAP, 2, value, NULL );
			}
		}
		else if ( pValue[0] == 6 )
		{
			char v1[32] = { 0 };
			sprintf( v1, "%d", global.kingwar_token_sneak );
			actor_notify_msgbox_v( actor_index, MSGBOX_CALLBACK_KINGWAR_SNEAK, 1, 2, 1411, v1, NULL );
		}
		else if ( pValue[0] == 7 )
		{
			worldquest_setvalue( pValue[1], 1 );
		}
		else if ( pValue[0] == 8 )
		{ // ��������ϵͳ
			weather_open();
		}
		break;
	case GMC_SC:
		sc_Script_Command( pValue[0], pValue[1], pValue[2], pValue[3], pMsg, actor_index );
		break;
	case GMC_LUA:// ����lua
		tmpi = lua_reload( -1 );
		mapzoneinfo_luatable_auto();
		sprintf( szMsg, "ThisTimer:%d", tmpi );
		if ( actor_index >= 0 )
			system_talkto( actor_index, szMsg, 0 );
		break;
	case GMC_RELOAD:// �ض����ݱ�
		break;
	case GMC_RESET:// ���õȼ�����
		break;
	case GMC_EXP:// ����
		if ( pCity )
		{
			city_actorexp( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_TOKEN:// ��ʯ
		if ( pCity )
		{
			if ( pCity->actor_index >= 0 )
				actor_change_token( actor_index, pValue[0], PATH_GM, 0 );
			else
				gift( pCity->actorid, AWARDKIND_TOKEN, pValue[0], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, PATH_GM );
		}
		break;
	case GMC_ITEM:// ����
		if ( pValue[0] == -100 )
		{
			item_gm_getall( actor_index );
			break;
		}
		else if ( pValue[0] == -1 && actor_index >= 0 )
		{
			int item_clear( int actorindex );
			item_clear( actor_index );
			break;
		}
		else if ( pValue[0] == 0 && actor_index >= 0 )
		{
			void item_searchname( int actor_index, char *pName, int totle );
			item_searchname( actor_index, pMsg, pValue[1] > 0 ? pValue[1] : 10 );
			break;
		}
		if ( pValue[1] == 0 )
			tmpi = 1;
		else
			tmpi = pValue[1];
		if ( tmpi < 0 && pCity )
		{
			if ( item_lost( pCity->actor_index, pValue[0], -tmpi, PATH_GM ) >= 0 )
			{
				if ( actor_index >= 0 )
					system_talkto( actor_index, "Actor lost item.", 0 );
			}
		}
		else if ( pCity )
		{
			if ( item_getitem( pCity->actor_index, pValue[0], tmpi, -1, PATH_GM ) >= 0 )
			{
				if ( actor_index >= 0 )
					system_talkto( actor_index, "Actor get item.", 0 );
			}
			else
			{
				if ( actor_index >= 0 )
					system_talkto( actor_index, "Actor not get item.", 0 );
			}
		}
		break;
	case GMC_EQUIP:// װ��
		if ( pCity && pValue[0] == -1 && actor_index >= 0 )
		{
			int equip_clear( int actorindex );
			equip_clear( pCity->actor_index );
			break;
		}
		else if ( pCity && pValue[0] == -100 )
		{
			equip_gm_getall( pCity->actor_index );
			break;
		}
		else if ( pCity && pValue[0] == -101 )
		{
			equip_gm_getherogod( pCity->actor_index );
			break;
		}

		if ( pCity )
		{
			if ( equip_getequip( pCity->actor_index, pValue[0], PATH_GM ) >= 0 )
			{
				if ( actor_index >= 0 )
					system_talkto( actor_index, "Actor get equip.", 0 );
			}
			else
			{
				if ( actor_index >= 0 )
					system_talkto( actor_index, "Actor not get equip.", 0 );
			}
		}
		break;
	case GMC_HERO:// Ӣ��
		if ( pCity )
		{
			if ( pValue[0] == -1 )
			{
				hero_gm_level( pCity, pValue[1] );
			}
			else if( pValue[0] == -2 )
			{
				hero_gm_soldiers( pCity );
			}
			else if ( pValue[0] == -100 )
			{
				hero_gm_getallhero( pCity );
			}
			else
				hero_gethero( pCity->actor_index, pValue[0], PATH_GM );
		}
		break;
	case GMC_SILVER:// ����
		if ( pCity )
		{
			city_changesilver( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_WOOD:// ľ��
		if ( pCity )
		{
			city_changewood( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_FOOD:// ��ʳ
		if ( pCity )
		{
			city_changefood( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_IRON:// ����
		if ( pCity )
		{
			city_changeiron( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_BODY:// ����
		if ( pCity )
		{
			city_changebody( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_LEVY:// �ո����
		if ( pCity )
		{
			city_changelevy( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_AWARDGROUP:// ����
		if ( pCity )
		{
			awardgroup_withid( pCity->actorid, pValue[0], PATH_GM, NULL );
		}
		break;
	case GMC_QUEST:// ����
		break;
	case GMC_ROLLMSG:// �����
		system_roll( pMsg );
		break;
	case GMC_MAIL:// �ʼ�
		if ( pCity )
		{
			char title[64] = { 0 };
			sprintf( title, "%s%d", TAG_TEXTID, 5001 );

			char content[128] = { 0 };
			sprintf( content, "{\"text\":\"%s%d\"}", TAG_TEXTID, 5501 );

			char attach[256] = { 0 };
			sprintf( attach, "3,1@5001,1000@5002,2000@50010,10000" );
			mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_SYSTEM, title, content, attach, 0, 0 );
		}
		break;
	case GMC_SYSTALK:// ϵͳ����
		system_talk( pMsg, 1 );
		break;
	case GMC_VIPEXP:// vip����
		if ( pCity )
		{
			vip_exp( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_ACTIVITY:// �
		activity_settime( pValue[0], 0, pValue[1], pValue[2], pValue[3], 0, 0, pMsg );
		break;
	case GMC_TECH:
		if ( pCity )
		{
			city_tech_get_gm( pCity, pValue[0] );
		}
		break;
	case GMC_BUILDING: // ����
		if ( pCity )
		{
			if ( pValue[0] > 0 )
				building_give( pCity->index, pValue[0], 1 );
			else if ( pValue[0] == -1 )
				building_gm( pCity );
		}
		break;
	case GMC_PEOPLE: // �˿�
		if ( pCity )
		{
			city_changepeople( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_MAT: // ��������
		if ( pCity )
		{
			city_material_gm( pCity, pValue[0] );
		}
		break;
	case GMC_FUN: // ��ȡ����
		if ( pCity )
		{
			city_function_open( pCity, pValue[0] );
		}
		break;
	case GMC_EVENT: // ��ͼ�¼�
		if ( pCity )
		{
			pCity->eventsec = 1;
		}
		break;
	case GMC_VW: // ����
		if ( pCity )
		{
			city_changeprestige( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_TOWNATTACK: // ���ǹ���
		map_town_attack( pValue[0] );
		break;
	case  GMC_WORLDBOSS:
		if ( pValue[0] == -1 )
		{
			if ( pCity )
			{
				actor_set_today_char_times( pCity->actor_index, TODAY_CHAR_WORLDBOSS, 0 );
			}
		}
		else if( pValue[0] > 0 )
		{
			worldboss_gm( pValue[0], pValue[1] );
		}
		break;
	case GMC_KWPOINT: // Ѫս����
		if ( pCity )
		{
			city_kingwarpoint( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_GIVERES: // ����һ��δ������Դ��
		if ( pCity )
		{
			building_giveres( pCity->index, pValue[0] );
		}
		break;
	case GMC_AUTOBUILD: // �Զ��������
		if ( pCity )
		{
			city_change_autobuild( pCity->index, pValue[0], PATH_GM );
		}
		break;
	case GMC_PAYBAG:
		if ( pValue[0] > 0 )
		{
			paybag_insert( pValue[0], pValue[1], pValue[2], pValue[3] );
		}
		else if ( pValue[0] < 0 )
		{
			paybag_delete( -pValue[0] );
		}
		break;
	case GMC_BUILDINGLEVEL: // �����ȼ�
		if ( pCity )
		{
			building_level_gm( pCity->index, pValue[0], pValue[1] );
		}
		break;
	case GMC_STORY: // ����
		if ( pCity )
		{
			story_gm( pCity->actor_index, pValue[0] );
		}
		break;
	case GMC_PRESTIGE: // ����
		if ( pCity )
		{
			city_changeprestige( pCity->actor_index, pValue[0], PATH_GM );
		}
		break;
	case GMC_NATIONMISSION:// ������������
		if ( pCity )
		{
			nation_mission_addvalue( pCity->nation, pValue[0], pValue[1] );
			// ������������
			nation_rank_addvalue( pCity, pValue[0], pValue[1] );
		}
		break;
	case GMC_NATIONQUEST:// ��������
		if ( pCity )
		{
			nation_quest_addvalue( pCity, pValue[0], pValue[1] );
		}
		break;
	case GMC_NATIONRANK:// ������������
		if ( pValue[0] == 0 )
			nation_rank_update();
		else if ( pValue[0] == 1 )
			nation_rank_calc();
		break;
	case GMC_NATIONEXP: // ���Ҿ���
		if ( pCity )
		{
			nation_exp( pCity->nation, pValue[0] );
		}
		break;
	case GMC_NATIONOF: // ���ҹ�Աϵͳ
		extern int g_nation_official_statetime;
		g_nation_official_statetime = (int)time( NULL ) + 30;
		world_data_set( WORLD_DATA_NATION_OFFICIAL_STATETIME, g_nation_official_statetime, NULL, NULL );
		break;
	case GMC_NHERO: // ��������
		if ( pCity )
		{
			extern NationHero *g_nation_hero;
			extern int g_nation_hero_maxcount;
			if ( pValue[0] == -1 )
			{ // ץ���뿪ʱ��
				for ( int tmpi = 0; tmpi < NATIONHERO_MAX; tmpi++ )
				{
					int kind = pCity->nation_hero[tmpi].kind;
					if ( kind <= 0 || kind >= g_nation_hero_maxcount )
						continue;
					if ( pCity->nation_hero[tmpi].state != NATIONHERO_STATE_CATCH )
						continue;
					g_nation_hero[kind].runsec = 30;
					nation_hero_cityinfo( pCity->actor_index, kind );
				}
			}
			else if ( pValue[0] == -2 )
			{ // �ҳ϶Ƚ���10
				for ( int tmpi = 0; tmpi < NATIONHERO_MAX; tmpi++ )
				{
					int kind = pCity->nation_hero[tmpi].kind;
					if ( kind <= 0 || kind >= g_nation_hero_maxcount )
						continue;
					if ( pCity->nation_hero[tmpi].state != NATIONHERO_STATE_EMPLOY )
						continue;
					pCity->nation_hero[tmpi].loyal -= 10;
					if ( pCity->nation_hero[tmpi].loyal < 0 )
						pCity->nation_hero[tmpi].loyal = 0;
					nation_hero_cityinfo( pCity->actor_index, kind );
				}
			}
		}
		break;
	case GMC_DB: // ���ݿ�����
		process_dbreload();
		break;
	case GMC_PAY:
	{
		if ( pMsg == NULL )
		{
			break;
		}
		char *pOrderID = NULL;
		char *pMoney;
		char *pCurrency;

		int tmpi = 0;
		char *strp;
		char *str = pMsg;
		char sign = '|';
		strp = str;
		while ( *str )
		{
			if ( *str == sign )
			{
				if ( tmpi == 0 )
					pOrderID = strp;
				else if ( tmpi == 1 )
					pMoney = strp;
				else if ( tmpi == 2 )
					pCurrency = strp;
				*str = 0;
				str++;
				strp = str;
				tmpi++;
				if ( tmpi >= 3 )
					break;
			}
			else
				str++;
		}
		if ( tmpi == 0 )
			pOrderID = strp;
		else if ( tmpi == 1 )
			pMoney = strp;
		else if ( tmpi == 2 )
			pCurrency = strp;
		tmpi++;
		if ( tmpi == 1 )
		{
			pMoney = strp;
			pCurrency = strp;
		}
		else if ( tmpi == 2 )
		{
			pCurrency = strp;
		}

		actor_pay( pValue[0], pValue[1], pOrderID, pMoney, pCurrency );
	}
	break;
	case GMC_BUFFCLEAR:
		if ( pCity )
		{
			short kind = pValue[0];
			if ( kind >= 0 && kind < CITY_BUFF_MAX )
			{
				if ( pValue[1] == 0 )
					pCity->buffsec[kind] = 1;
				else
					pCity->buffsec[kind] = pValue[1];
				city_change_buff( pCity->index, kind, 0, PATH_GM );
			}
		}
		break;
	case GMC_AWARD:// ����
		if ( pCity )
		{
			if ( pCity->actor_index >= 0 && pCity->actor_index < g_maxactornum )
			{
				award_getaward( pCity->actor_index, pValue[0], pValue[1], -1, PATH_GM, NULL );
			}
			else
			{
				gift( pCity->actorid, pValue[0], pValue[1], -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, PATH_GM );
			}
		}
		break;
	default:
		break;
	}
	return GMR_OK;
}
