#include "ClientWorker.h"

// local
/*#include "Client.h"
#include "ClientConnection.h"
#include "GameInstance.h"
#include "PlayerJoinInfo.h"*/



ClientWorker::ClientWorker(Client &client, QObject *parent)
	: QObject(parent), client(client)
{
}

void ClientWorker::sendConnectRequest(const RequestInfo &rinfo, const quint8 &state)
{
	emit signBuildConnectRequest(rinfo, state);
}
void ClientWorker::sendDSQRequest(const RequestInfo &rinfo, const quint8 &state)
{
}
void ClientWorker::sendJoinRequest(const RequestInfo &rinfo, const quint8 &state)
{
}

void ClientWorker::handleConnectAnswer(const RequestInfo &rinfo, const gp_connect_answer &answer)
{
	emit signParseConnectAnswer(rinfo, answer);
}

  // Helper vars
  /*ClientConnection *cc = _server->getClientConnection( rinfo.getCId() );

  /////////////// REWRITE to utilize the defines

  // Check request
  switch( query.connect_flag ) {

  case GP_CONNECT_FLAG_CONNECT:
    if( cc->isConnected() )
      emit signQueueError( rinfo, GP_ERROR_CONNECT_CONNECTED );
    else {
      cc->setConnected( true );
      emit signBuildConnectAnswer( rinfo, GP_CONNECT_FLAG_CONNECT );
    }
    break;

  case GP_CONNECT_FLAG_DISCONNECT:
    if( cc->isConnected() ) {
      cc->setConnected( false );
      emit signBuildConnectAnswer( rinfo, GP_CONNECT_FLAG_DISCONNECT );
    }
    else
      emit signQueueError( rinfo, GP_ERROR_CONNECT_DISCONNECTED );
    break;

  default:
    emit signQueueError( rinfo, GP_ERROR_CONNECT_UNKNOWN );
  }
}*/

void ClientWorker::handleDSQAnswer(const RequestInfo &rinfo, const gp_default_server_query_answer &answer) {

  // Helper vars
  /*ClientConnection *cc = _server->getClientConnection( rinfo.getCId() );

  // Check whether the client is connected. Must be connected before queries is allowed.
  if( !cc->isConnected() ) {
    emit signQueueError( rinfo, GP_ERROR_DSQ_NOT_CONNECTED );
    return;
  }

  emit signBuildDSQAnswer( rinfo, query );*/
}

void ClientWorker::handleJoinAnswer(const RequestInfo &rinfo, const gp_join_answer &answer) {

  // Helper vars
  /*GameInstance *gi = _server->getGameInstance();

  quint32 validation_code = 88;


  // Check if server is full if not reserve a slot (mutex!!)
  if( !gi->reserveConnectSlot( rinfo.getCId(),
                               PlayerJoinInfo( validation_code, request ) )
      ) {

    emit signQueueError( rinfo, GP_ERROR_JOIN_UNKNOWN );
    return;
  }

  // Check whether player is banned ><

  // Deterimine part join, and check if already joind/parted

  // If team match, check if team_id is valid and if team is full

  // Check race and class

  // If all is good and well add a playerinstance and send validation code
  // back to client

  emit signBuildJoinAnswer( rinfo, request.flags.join_flag, validation_code );*/
}
