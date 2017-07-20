#include "actor.h"
#include "actor_send.h"
#include "gameproc.h"
#include "server_netsend_auto.h"
#include "area.h"
#include "city.h"

extern Actor *g_actors;
extern int g_actornum;
extern int g_maxactornum;

int zone_sendmsg( int zone, int datasize, char *databuf )
{
	if ( datasize > 0 )
	{
		for ( int tmpi = 0; tmpi < g_maxactornum; tmpi++ )
		{
			if ( g_actors[tmpi].actorid <= 0 )
				continue;
			City *pCity = city_getptr( tmpi );
			if ( !pCity )
				continue;
			if ( pCity->zone == zone )
			{
				sendtoclient( tmpi, databuf, datasize + sizeof( short ) );
			}
		}
	}
	return 0;
}

int nation_sendmsg( int nation, int datasize, char *databuf )
{
	if ( datasize > 0 )
	{
		for ( int tmpi = 0; tmpi < g_maxactornum; tmpi++ )
		{
			if ( g_actors[tmpi].actorid <= 0 )
				continue;
			City *pCity = city_getptr( tmpi );
			if ( !pCity )
				continue;
			if ( pCity->nation == nation )
			{
				sendtoclient( tmpi, databuf, datasize + sizeof( short ) );
			}
		}
	}
	return 0;
}

// 世界信息发送,信息立即发送
int world_sendmsg( int datasize, char *databuf )
{
	if ( datasize > 0 )
	{
		for ( int tmpi = 0; tmpi < g_maxactornum; tmpi++ )
		{
			if ( g_actors[tmpi].actorid > 0 )
				sendtoclient( tmpi, databuf, datasize + sizeof(short) );
		}
	}
	return 0;
}

int actor_senddata( int actor_index, char send_type, char *data, int datasize )
{
	switch( send_type )
	{
	case SENDTYPE_ACTOR:
		sendtoclient( actor_index, data, datasize+sizeof(short) );
		break;
	case SENDTYPE_AREA:
		{
			area_sendmsg( actor_index, datasize, data + sizeof(short) );
			//area_clearmsg( actor_index );
		}
		break;
	case SENDTYPE_MAP:
		break;
	case SENDTYPE_ZONE:
		zone_sendmsg( actor_index, datasize, data );
		break;
	case SENDTYPE_NATION:
		nation_sendmsg( actor_index, datasize, data );
		break;
	case SENDTYPE_WORLD:
		world_sendmsg( datasize, data );
		break;
	}
	return 0;
}
