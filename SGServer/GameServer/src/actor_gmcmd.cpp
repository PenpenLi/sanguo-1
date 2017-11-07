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
			time_t t;
			time( &t );
			t += 120;
			struct tm *nowtime = localtime( &t );
			global.kingwar_activity_week = nowtime->tm_wday;
			global.kingwar_activity_hour = nowtime->tm_hour;
			global.kingwar_activity_minute = nowtime->tm_min;	
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
		if ( pValue[0] == -1 && actor_index >= 0 )
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
	case GMC_AWARD:// ����
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
			mail( pCity->actor_index, pCity->actorid, MAIL_TYPE_SYSTEM, title, content, attach, 0 );
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
	default:
		break;
	}
	return GMR_OK;
}
