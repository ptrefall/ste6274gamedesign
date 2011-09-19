#include "BuildDsqPkgTask.h"

#include "../Client.h"
//#include "../Info/GameInfo.h"
//#include "playerinstance.h"
#include "../Info/ServerInfo.h"

#include <QDebug>

#include <cstring>

void BuildDSQPkgTask::load(Client *client, const gp_default_server_query &query)
{
	this->client = client;
	this->query = query;
	setLoadOK();
}

void BuildDSQPkgTask::run()
{
	if( !isValid() )
		return;

	qDebug() << "Building DSQ Request Pkg!!";

	// Helper vars
	/*GameInstance *ginst = _server->getGameInstance();
	const GameInfo &ginf = ginst->getGameInfo();
	const ServerInfo &gsinf = ginst->getServerInfo();*/

	// Init the pkg
	initRequestPkg(GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY);

	// Compile body
	gp_default_server_query body;

	// Handle server info
	/*if(query.request_flags.server_info)
	{

	// Enable the server info
	body.request_flags.server_info = true;

	// Set server info field flags
	body.server_info.fields = _query.server_fields;

	// Set server info fields
	std::strcpy( body.server_info.game_name,
	 ginf.getName().toStdString().c_str() );

	body.server_info.flags.type             = GP_SERVER_FLAG_TYPE_DEDICATED;
	body.server_info.flags.password         = false;

	#if defined(Q_WS_X11)
	body.server_info.flags.operating_system = GP_SERVER_FLAG_OS_LINUX;
	#elif defined(Q_WS_WIN)
	body.server_info.flags.operating_system = GP_SERVER_FLAG_OS_WINDOWS;
	#elif defined(Q_WS_MACX)
	body.server_info.flags.operating_system = GP_SERVER_FLAG_OS_MAC;
	#else
	body.server_info.flags.operating_system = GP_SERVER_FLAG_OS_UNKNOWN;
	#endif

	std::strcpy( body.server_info.host_name,
	 gsinf.getHostname().toStdString().c_str() );

	body.server_info.connect_port           = ginst->serverPort();

	std::strcpy( body.server_info.game_type,
	 ginf.getType().toStdString().c_str() );

	std::strcpy( body.server_info.game_state,
	 ginst->getState().toStdString().c_str() );

	body.server_info.max_slots              = gsinf.getMaxSlots();
	body.server_info.player_count           = ginst->getNoPlayers();
	body.server_info.bot_count              = ginst->getNoBots();
	body.server_info.reserved_slots         = gsinf.getReservedSlots();
	}


	// Handle map info
	QVector<MapInfo>& mapinf = ginst->accessMapInfo();
	if( _query.request_flags.map_info && mapinf.size() > 0 ) {

	// Enable the map info
	body.request_flags.map_info = true;

	// Enable the queried info fields
	body.map_info.map_fields = _query.map_fields;

	// Fixme:
	// By default, getting info from the first map.
	MapInfo& info = mapinf[0];
	std::strcpy( body.map_info.author, info.getAuthor().toStdString().c_str() );
	std::strcpy( body.map_info.name, info.getName().toStdString().c_str() );
	std::strcpy( body.map_info.url, info.getUrl().toStdString().c_str() );
	std::strcpy( body.map_info.version, info.getVersion().toStdString().c_str() );

	std::strcpy( body.map_info.cfield01, "\0");
	std::strcpy( body.map_info.cfield02, "\0");
	std::strcpy( body.map_info.cfield03, "\0");
	std::strcpy( body.map_info.cfield04, "\0");
	}


	// Handle team info
	QVector<TeamInfo>& team_info = ginst->accessTeamInfo();
	if( _query.request_flags.team_list && team_info.size() > 0 ) {

	// Enable team info
	body.request_flags.team_list = true;

	// Enable the queried info fields
	body.team_list.info_fields = _query.team_fields;

	body.team_list.count = team_info.size();

	for ( int i=0; i < team_info.size() && i < GP_TEAM_COUNT_MAX; ++i ) {
	body.team_list.list[i].id = team_info[i].getId();
	std::strcpy( body.team_list.list[i].name, team_info[i].getName().toStdString().c_str() );
	body.team_list.list[i].score = team_info[i].getScore();
	// Fixme: these are not yet present in TeamInfo
	body.team_list.list[i].avg_loss = 0;
	body.team_list.list[i].avg_ping = 0;
	body.team_list.list[i].member_count = 0;
	}
	}


	// Handle player info
	QMap<quint32, PlayerInstance*>& players = ginst->accessPlayers();
	if( _query.request_flags.player_list ) {

	// Enable the player part of the reply
	body.request_flags.player_list = true;

	// Enable the queried info fields
	body.player_list.info_fields.class_ = _query.player_fields.class_;

	// Populate info fields
	body.player_list.count = players.size();

	QMap<quint32, PlayerInstance*>::iterator iter = players.begin();
	for ( int i=0; iter != players.end() && i < GP_PLAYER_COUNT_MAX; ++iter, ++i ) {
	std::strcpy( body.player_list.list[i].name, (*iter)->getName().toStdString().c_str() );
	body.player_list.list[i].score      = (*iter)->getScore();
	body.player_list.list[i].id         = (*iter)->getId();
	std::strcpy( body.player_list.list[i].class_, (*iter)->getClass().toStdString().c_str() );
	body.player_list.list[i].deaths     = (*iter)->getDeaths();
	body.player_list.list[i].frags      = (*iter)->getFrags();
	body.player_list.list[i].kills      = (*iter)->getKills();
	body.player_list.list[i].suicides   = (*iter)->getSuicides();
	body.player_list.list[i].team_kills = (*iter)->getTeamKills();
	std::strcpy( body.player_list.list[i].race ,(*iter)->getRace().toStdString().c_str() );

	// Player flags
	body.player_list.list[i].flags.bot         = (*iter)->getPfBot();
	body.player_list.list[i].flags.state       = (*iter)->getPfState();
	body.player_list.list[i].flags.team_state  = (*iter)->getPfTeamState();
	}
	}


	// Handle rule info
	if( _query.request_flags.rule_list )
	body.request_flags.rule_list = false;


	// Handle limit info
	if( _query.request_flags.limit_list )
	body.request_flags.limit_list = false;









	// Add body to send package
	addToBlock<gp_default_server_query_answer>(body);

	// Build send task and queue it for execution
	buildAndQueue();*/
}
