#include "actor_notify.h"
#include "actor.h"
#include "actor_send.h"
#include "gameproc.h"
#include "server_netsend_auto.h"

extern Actor *g_actors;
extern int g_actornum;
extern int g_maxactornum;

// 发送给角色短消息 无参数
int actor_notify( int actor_index, short msgid, const char *msg )
{
	SLK_NetS_Notify Value = { 0 };
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Value.m_msgid = msgid;
	Value.m_valuenum = 0;
	if ( msg )
	{
		Value.m_msg_length = (short)strlen( msg ) + 1;
		strcpy( Value.m_msg, msg );
	}
	netsend_notify_S( actor_index, SENDTYPE_ACTOR, &Value );

	return 0;
}

// 发送给角色短消息 带参数
int actor_notify_value( int actor_index, short msgid, char count, const int *data, const char *msg )
{
	SLK_NetS_Notify Value = { 0 };
	if ( actor_index < 0 || actor_index >= g_maxactornum )
		return -1;
	Value.m_msgid = msgid;
	Value.m_valuenum = count;
	for ( int tmpi = 0; tmpi < count; tmpi++ )
	{
		Value.m_value[tmpi] = data[tmpi];
	}
	if ( msg )
	{
		Value.m_msg_length = (short)strlen( msg ) + 1;
		strcpy( Value.m_msg, msg );
	}
	netsend_notify_S( actor_index, SENDTYPE_ACTOR, &Value );

	return 0;
}

// 发消息提示，通过消息ID
int actor_system_message( int actor_index, int msgid )
{
	actor_notify_value( actor_index, NOTIFY_NORMAL, 1, &msgid, NULL );
	return 0;
}

// npc对话
int npc_talk( int actor_index, int textid )
{
	actor_notify_value( actor_index, NOTIFY_NPCTALK, 1, &textid, NULL );
	return 0;
}

// 弹出确定消息
int actor_notify_alert( int actor_index, int textid )
{
	actor_notify_value( actor_index, NOTIFY_ALERT, 1, &textid, NULL );
	return 0;
}

// 弹出确定消息带参数
int actor_notify_alert_v( int actor_index, int textid, char *v1, char *v2 )
{
	char content[128] = { 0 };
	if ( v1 && v2 )
	{
		sprintf( content, "{\"v1\":\"%s\",\"v2\":\"%s\"}", v1, v2 );
		actor_notify_value( actor_index, NOTIFY_ALERT, 1, &textid, content );
	}
	else if ( v1 )
	{
		sprintf( content, "{\"v1\":\"%s\"}", v1 );
		actor_notify_value( actor_index, NOTIFY_ALERT, 1, &textid, content );
	}
	else
	{
		actor_notify_value( actor_index, NOTIFY_ALERT, 1, &textid, NULL );
	}
	return 0;
}
