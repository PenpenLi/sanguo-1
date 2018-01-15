#include <stdio.h>
#include <time.h>
#include "system_askinfo.h"
#include "actor.h"
#include "gameproc.h"
#include "utils.h"
#include "db.h"
#include "client.h"
#include "area.h"
#include "map.h"
#include "mapunit.h"
#include "actor_notify.h"
#include "server_structsend_auto.h"
#include "system.h"
#include "actor_send.h"
#include "item.h"
#include "equip.h"
#include "global.h"
#include "activity.h"
#include "script_auto.h"
#include "login.h"
#include "city.h"
#include "city_tech.h"
#include "quest.h"
#include "world_quest.h"
#include "world_boss.h"
#include "building.h"
#include "hero.h"
#include "story.h"
#include "map_zone.h"
#include "map_town.h"
#include "map_enemy.h"
#include "map_res.h"
#include "map_event.h"
#include "army_march.h"
#include "army_group.h"
#include "king_war.h"
#include "shop.h"
#include "pay.h"
#include "vip.h"
#include "nation_equip.h"
#include "nation.h"

extern Actor *g_actors;
extern int g_maxactornum;
extern SConfig g_Config;

extern MapUnit *g_mapunit;
extern int g_mapunit_maxcount;

extern Global global;
extern Map g_map;

// �ͻ��˽ű�ֱ�ӷ�������Ϣ
int system_askinfo( int actor_index, int msgid, char *pstr, int *pvalue )
{
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	switch ( msgid )
	{
	case ASKINFO_NORMAL:
		break;
	case ASKINFO_CHANGESHAPE:
		actor_changeshape( actor_index, (char)pvalue[0] );
		break;
	case ASKINFO_CHANGENAME:
		actor_changename( actor_index, pstr, pvalue[0] );
		break;
	case ASKINFO_CITYGUARD:
		if ( pvalue[0] == 0 )
		{// �б�
			city_guard_sendlist( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ��ļ����
			city_guard_call( g_actors[actor_index].city_index );
		}
		else if ( pvalue[0] == 2 )
		{ // ����������
			city_guard_upgrade( g_actors[actor_index].city_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{ // ���������ļ��ȴ
			city_guard_clearcd( g_actors[actor_index].city_index );
		}
		else if ( pvalue[0] == 4 )
		{ // ��Ѫ
			city_guard_soldiers( g_actors[actor_index].city_index, pvalue[1] );
		}
		
		break;
	case ASKINFO_QUEST:
		if ( pvalue[0] == 1 )
		{ // ��ȡ������
			quest_getaward( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ����������͵�����
			quest_client_op( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 10 )
		{ // ��������
			worldquest_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 11 )
		{ // ����������
			worldquest_sendaward( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 12 )
		{ // ����������ȡ����
			worldquest_getaward( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 13 )
		{ // ����boss��Ϣ
			worldboss_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 14 )
		{ // ����boss��Ϣ
			worldboss_sendbattleinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 15 )
		{ // �״����ǰ���ݳ�
			map_zone_goto_zc( actor_index );
		}
		break;
	case ASKINFO_BUILDING:
		if ( pvalue[0] == 0 )
		{ // ������Ϣ
			building_send_upgradeinfo( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 1 )
		{ // ����
			building_upgrade( g_actors[actor_index].city_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 2 )
		{ // ������Ѽ���
			building_workerfree( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{ // �������ý������
			building_workerbuy( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 4 )
		{ // ���ٽ����ļ���
			building_awardquick_get( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 5 )
		{ // �Ľ�
			building_rebuild( g_actors[actor_index].city_index, pvalue[1], pvalue[2], pvalue[3] );
		}
		else if ( pvalue[0] == 6 )
		{ // ��Դ�㽨��
			building_giveres_build( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_LEVY:
		if ( pvalue[0] == 0 )
		{ // ������Ϣ
			city_levy_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ����
			city_levy( actor_index );
		}
		break;
	case ASKINFO_TRAIN:
		if ( pvalue[0] == 0 )
		{ // ��ļ��Ϣ
			city_train_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{ // ��ļ
			city_train( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{ // ȡ��
			city_train_cancel( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ȡ
			city_train_get( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 5 )
		{ // ����
			city_train_buyqueue( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 6 )
		{ // ����ʱ��
			city_train_buylong( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 7 )
		{ // ����������ȡ
			city_train_awardquick_get( actor_index, pvalue[1] );
		}
		
		break;
	case ASKINFO_EQUIPFORGING:
		if ( pvalue[0] == 0 )
		{ // ����װ��
			equip_forging( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{ // ���ٴ���װ��
			equip_forging_quick( actor_index );
		}
		else if ( pvalue[0] == 2 )
		{ // �������ٴ���װ��
			equip_forging_freequick( actor_index );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ȡװ��
			equip_forging_get( actor_index );
		}
		
		break;
	case ASKINFO_EQUIPWASH:
		break;
	case ASKINFO_EQUIP:
		if ( pvalue[0] == 1 )
		{ // �ֽ�
			equip_resolve( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // װ��
			equip_up( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{ // ж��
			equip_down( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 4 )
		{ // ����װ����
			equip_buyext( actor_index );
		}
		else if ( pvalue[0] == 5 )
		{ // װ��ϴ������
			equip_wash_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 6 )
		{ // װ�����ϴ��
			equip_wash_free( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 7 )
		{ // װ����ʯϴ��
			equip_wash_token( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 8 )
		{ // װ���ؼ�ϴ��
			equip_wash_super( actor_index, pvalue[1] );
		}
	
		break;
	case ASKINFO_ITEM:
		if ( pvalue[0] == ITEM_PROCESS_INFO )
		{

		}
		else if ( pvalue[0] == ITEM_PROCESS_USE )
		{
			item_use( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4] );
		}
		else if ( pvalue[0] == ITEM_PROCESS_SELL )
		{
			item_drop( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == ITEM_PROCESS_TOKENUSE )
		{
			item_use_withtoken( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4] );
		}
		else if ( pvalue[0] == ITEM_PROCESS_BUY )
		{
			item_buy( actor_index, pvalue[1], pvalue[2] );
		}
		
		break;
	case ASKINFO_HERO:
		if ( pvalue[0] == 1 )
		{// ����
			hero_addsoldiers( actor_index, pvalue[1], PATH_HERO_ADDSOLDIERS );
		}
		else if ( pvalue[0] == 2 )
		{// ʹ�þ������
			hero_useexpitem( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{// ����
			hero_up( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4] );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ϴ������ȡ��Ϣ
			hero_wash_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 5 )
		{ // ���ϴ��
			hero_wash_free( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 6 )
		{ // ����ϴ��
			hero_wash_token( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 7 )
		{ // ����ͻ����Ϣ
			hero_colorup_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 8 )
		{ // ����ͻ��
			hero_colorup( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 9 )
		{// ����
			hero_down( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 10 )
		{ // ����������ʿ��
			hero_guard_soldiers_token( actor_index, pvalue[1] );
		}
		
		break;
	case ASKINFO_TECH:
		if ( pvalue[0] == 1 )
		{ // ����
			city_tech_upgrade( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ����
			city_tech_quick( actor_index );
		}
		else if ( pvalue[0] == 3 )
		{ // ��Ѽ���
			city_tech_freequick( actor_index );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ȡ
			city_tech_get( actor_index );
		}
		break;
	case ASKINFO_GOV:
		if ( pvalue[0] == 0 )
		{ // �¼�
			city_event_sendlist( actor_index );
		}
		break;
	case ASKINFO_OFFICIALHIRE:
		if ( pvalue[0] == 0 )
		{
			city_officialhire( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_QUICK:
		if ( pvalue[0] == 0 )
		{
			item_use_quick( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4] );
		}
		break;
	case ASKINFO_ACTOR:
		if ( pvalue[0] == 0 )
		{ // ��������
			actor_buybody( actor_index, pvalue[1] );
		}
		else if( pvalue[0] == 1 )
		{ // ���¿�ʼ��ɫ
			actor_restart( actor_index );
		}
		else if ( pvalue[0] == 2 )
		{ // ��ȡ��ɫ��Ϣ
			actor_search( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{ // �������б�
			actor_blacklist_sendlist( actor_index );
		}
		else if ( pvalue[0] == 4 )
		{ // ���������
			actor_blacklist_add( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 5 )
		{ // ������ɾ��
			actor_blacklist_del( actor_index, pvalue[1] );
		}
		break;
	case ASKINFO_MATERIALMAKE:
		if ( pvalue[0] == 0 )
		{ // ��ȡ��Ϣ
			city_material_sendinfo( actor_index, 1 );
		}
		else if ( pvalue[0] == 1 )
		{ // ����
			city_material_make( actor_index, pvalue[1], pvalue[2], 0 );
		}
		else if ( pvalue[0] == 2 )
		{ // Ԥ��������Ϣ
			city_material_will_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 3 )
		{ // �������
			city_material_buyqueue( actor_index );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ȡ
			city_material_get( actor_index );
		}
		else if ( pvalue[0] == 5 )
		{ // ����
			city_material_make( actor_index, pvalue[1], pvalue[2], 1 );
		}
		break;
	case ASKINFO_STORY:
		if ( pvalue[0] == 0 )
		{
			story_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{
			story_sendrank( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ��Դ��������
			story_res_get( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{ // ��Դ��������
			story_res_reset( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 4 )
		{ // ��ļ���������ļ
			story_hero_free( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 5 )
		{ // ��ļ������Ǯ��ļ
			story_hero_token( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 6 )
		{ // ͼֽ��������
			story_drawing_buy( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 7 )
		{ // ͼֽ��������
			story_drawing_get( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 8 )
		{ // ɨ��
			story_sweep( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4], pvalue[5] );
		}
		break;
	case ASKINFO_WORLDMAP:
		if ( pvalue[0] == 1 )
		{ // ���ܽ���
			map_enemy_sendaward( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // �������������Ϣ
			city_battlequeue_sendlist( actor_index, -1 );
		}
		else if ( pvalue[0] == 3 )
		{ // �Ѿ��ﵽĿ�ĵ�ĳ���
			actor_army_return( actor_index, pvalue[1], -1 );
		}
		else if ( pvalue[0] == 4 )
		{ // �о�;�е��ٻ�
			actor_army_callback( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 5 )
		{ // �о�����
			actor_army_march_speedup( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 7 )
		{ // ��Դ����Ϣ
			map_res_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 8 )
		{ // Ǩ��
			city_move_actor( actor_index, pvalue[1], pvalue[2], pvalue[3] );
		}
		else if ( pvalue[0] == 9 )
		{ // ǲ��
			actor_helparmy_repatriate( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 10 )
		{ // ���ʳǵ����ķ�Χ����
			map_zone_center_townlist( actor_index );
		}
		break;
	case ASKINFO_MAP_EVENT:
		if ( pvalue[0] == 1 )
		{ // �ɼ��¼�
			map_event_gather( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ��ȡ�¼�
			map_event_getaward( actor_index, pvalue[1] );
		}
		break;
	case ASKINFO_SPY_CITY:
		if ( pvalue[0] == 0 )
		{ // ���
			city_spy( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_CITYHELP:
		if ( pvalue[0] == 0 )
		{// פ��
			city_helparmy_sendlist( actor_index, pvalue[1] );
		}
		break;
	case ASKINFO_CITYARMYGROUP:
		if ( pvalue[0] == 0 )
		{ // ��ս�б�
			armygroup_city_sendlist( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{
			armygroup_askhelp( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_NATIONARMYGROUP:
		if ( pvalue[0] == 0 )
		{ // ��ս�б�
			armygroup_town_sendlist( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{ // ������ս
			armygroup_nation_askcreate( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ������ս���ĳ���
			armygroup_nation_sendlist( actor_index );
		}
		break;
	case ASKINFO_MAPTOWN:
		if ( pvalue[0] == 0 )
		{ // �������
			map_town_ask_owner( actor_index, pvalue[1] );
		}
		else if( pvalue[0] == 1 )
		{ // �����б�
			map_town_ask_owner_sendlist( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ��������
			map_town_owner_leave( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{ // ����
			map_town_soldiers_repair( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 4 )
		{ // ����
			map_town_levy( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 5 )
		{ // ������
			map_town_sendaward( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 6 )
		{ // ������ϸ��Ϣ
			map_town_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 7 )
		{ // ������ϸ��Ϣ
			map_town_ex_sendinfo( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 8 )
		{ // ���ǿ���
			map_town_dev( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 9 )
		{ // ���ǿ�����ȴ����
			map_town_dev_delcd( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 10 )
		{ // �޸�����
			map_town_changename( actor_index, pvalue[1], pstr );
		}
		break;
	case ASKINFO_MAPZONE:
		if ( pvalue[0] == 0 )
		{// ����б�
			map_zone_citylist( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{// �����б�
			map_zone_townlist( actor_index, pvalue[1] );
		}
		break;
	case ASKINFO_LOSTREBUILD:
		if ( pvalue[0] == 0 )
		{
			city_lost_rebuild_num( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{
			city_lost_rebuild_get( actor_index );
		}
		break;
	case ASKINFO_KINGWAR:
		if ( pvalue[0] == -1 )
		{ // ȡ������
			kingwar_subscribe_cancel( actor_index );
		}
		else if ( pvalue[0] == 0 )
		{ // ��ȡ�б�����
			kingwar_town_sendlist( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ǰ��
			kingwar_army_goto( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 2 )
		{ // ͵Ϯ
			kingwar_army_sneak( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{ // ����
			kingwar_army_pk( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 4 )
		{ // ����
			kingwar_army_attack( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 5 )
		{ // �ط�
			kingwar_army_defense( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 6 )
		{ // ��Ԯ
			kingwar_army_rebirth( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 10 )
		{ // Ѫս���а�
			kingwar_ranklist( actor_index );
		}
		else if ( pvalue[0] == 11 )
		{ // ��ȡѪս����
			kingwar_sendpoint( actor_index );
		}
		else if ( pvalue[0] == 12 )
		{ // �ʳ��ܿ�һ�
			kingwar_changeitem( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 13 )
		{ // ����׻�
			kingwar_treasure_buypos( actor_index );
		}
		else if ( pvalue[0] == 14 )
		{ // �ڱ�
			kingwar_treasure_do( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 15 )
		{ // �ڱ�ǰ��
			kingwar_treasure_goto( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 16 )
		{ // �����б�
			kingwar_congratulate_sendlist( actor_index );
		}
		else if ( pvalue[0] == 17 )
		{ // ����
			kingwar_congratulate( actor_index );
		}
		else if ( pvalue[0] == 18 )
		{
			kingwar_treasure_cityinfo( actor_index );
		}
		break;
	case ASKINFO_MSGBOX_CALLBACK:
		actor_notify_msgbox_callback( actor_index, pvalue[0], pvalue[1], pvalue[2] );
		break;
	case ASKINFO_AUTOBUILD:
		if ( pvalue[0] == 0 )
		{
			city_autobuild_open( g_actors[actor_index].city_index );
		}
		else if ( pvalue[0] == 1 )
		{ // �ͻ��˷��������Զ�����
			building_upgrade_auto( g_actors[actor_index].city_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 2 )
		{
			city_autoguard_open( g_actors[actor_index].city_index );
		}
		break;
	case ASKINFO_HERO_VISIT:
		if ( pvalue[0] == 0 )
		{ // Ѱ����Ϣ
			hero_visit_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ����Ѱ��
			if ( pvalue[1] == 0 )
				hero_visit_low( actor_index );
			else
				hero_visit_low10( actor_index );
		}
		else if ( pvalue[0] == 2 )
		{ // ��Ѱ��
			if ( pvalue[1] == 0 )
				hero_visit_high( actor_index );
			else
				hero_visit_high10( actor_index );
		}
		break;
	case ASKINFO_CHANGESIGN:
		actor_changsign( actor_index, pstr );
		break;
	case ASKINFO_SHOP:
		if ( pvalue[0] == 0 )
		{
			shop_list( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 1 )
		{
			shop_buy( actor_index, pvalue[1], pvalue[2], pvalue[3], pvalue[4], pvalue[5] );
		}
		break;
	case ASKINFO_PAY:
		if ( pvalue[0] == 0 )
		{ // ֧���̵��б�
			paystore_list( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ����б�
			activity_paybag_list( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ������Ʒ
			paystore_buy( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{ // ����֧��
			if ( g_actors[actor_index].admin >= 90 )
			{
				actor_pay( g_actors[actor_index].actorid, pvalue[1], pstr, "0", "0" );
			}
		}
		break;
	case ASKINFO_VIPSHOP:
		if ( pvalue[0] == 0 )
		{
			vipshop_list( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{
			vipshop_buy( actor_index, pvalue[1], pvalue[2], pvalue[3] );
		}
		else if ( pvalue[0] == 2 )
		{
			vipshop_set_useitembuy( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{
			vipshop_useitem_buy( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_VIPBAG:
		if ( pvalue[0] == 0 )
		{
			vipbag_list( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{
			vipbag_buy( actor_index, pvalue[1] );
		}
		break;
	case ASKINFO_ACTIVITY:
		if ( pvalue[0] == 0 )
		{
			activity_sendlist( actor_index );
		}
		break;
	case ASKINFO_NATIONEQUIP:
		if ( pvalue[0] == 0 )
		{
			nation_equip_sendlist( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ����
			nation_equip_open( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{ // ����
			nation_equip_upgrade( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 3 )
		{ // ����
			nation_equip_remake( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 4 )
		{ // ����
			nation_equip_quick( actor_index, pvalue[1], pvalue[2] );
		}
		break;
	case ASKINFO_NATION:
		if ( pvalue[0] == 0 )
		{
			nation_sendinfo( actor_index );
		}
		else if ( pvalue[0] == 1 )
		{ // ���ҽ���
			nation_build( actor_index );
		}
		else if ( pvalue[0] == 2 )
		{ // ��λ����
			nation_place_upgrade( actor_index );
		}
		else if ( pvalue[0] == 3 )
		{ // ���ҳǳ�
			nation_town_sendlist( actor_index );
		}
		else if ( pvalue[0] == 4 )
		{ // �ؽ���Ϣ
			nation_town_sendinfo( actor_index, pvalue[1], 1 );
		}
		else if ( pvalue[0] == 5 )
		{ // �޸�
			nation_town_repair( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 6 )
		{ // ����ս���б�
			nation_town_warlist( actor_index );
		}
		else if ( pvalue[0] == 7 )
		{ // �ǳ�ս���б�
			nation_city_warlist( actor_index );
		}
		break;
	default:
		break;
	}
	return 0;
}
