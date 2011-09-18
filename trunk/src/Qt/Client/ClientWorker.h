#pragma once

#include "requestinfo.h"
#include <Protocol/gameprotocol.h>
#include <QObject>

class Client;

class ClientWorker : public QObject
{
  Q_OBJECT
public:
  explicit ClientWorker(Client &client, QObject *parent = 0);

signals:
  void      signBuildConnectRequest( RequestInfo rinfo, quint8 state );
  void      signBuildDSQRequest( RequestInfo rinfo, const gp_default_server_query& query );
  void      signBuildJoinRequest( RequestInfo rinfo, quint8 state, quint32 validation_conde );
  void      signQueueError( RequestInfo rinfo, quint16 error );

public slots:
  void      handleConnectAnswer( RequestInfo rinfo, const gp_connect_request& request);
  void      handleDSQAnswer( RequestInfo rinfo, const gp_default_server_query& query );
  void      handleJoinAnswer( RequestInfo rinfo, const gp_join_request& request );

private:
  Client    &client;

};
