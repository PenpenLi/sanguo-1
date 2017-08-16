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
#include "building.h"
#include "hero.h"

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
			quest_getaward( actor_index, pvalue[1], 0 );
		}
		else if ( pvalue[0] == 2 )
		{ // ����������͵�����
			quest_setcomplete( actor_index, pvalue[1], QUEST_COMPLETEFLAG_SUCCESS );
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
			hero_addsoldiers( actor_index, pvalue[1] );
		}
		else if ( pvalue[0] == 2 )
		{// ʹ�þ������
			hero_useexpitem( actor_index, pvalue[1], pvalue[2] );
		}
		else if ( pvalue[0] == 3 )
		{// ����
			hero_up( actor_index, pvalue[1], pvalue[2], pvalue[3] );
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
		break;
	case ASKINFO_MATERIALMAKE:
		if ( pvalue[0] == 0 )
		{ // ��ȡ��Ϣ
			city_material_sendinfo( actor_index );
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
	default:
		break;
	}
	return 0;
}
