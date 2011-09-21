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
  void      signBuildConnectRequest(const RequestInfo &rinfo, const quint8 &state );
  void      signBuildDSQRequest(const RequestInfo &rinfo, const gp_default_server_query& query );
  void      signBuildJoinRequest(const RequestInfo &rinfo, const quint8 &state, const quint32 &validation_conde );
  void      signQueueError(const RequestInfo &rinfo, const quint16 &error );

public slots:
	void      sendConnectRequest( RequestInfo rinfo, const quint8 &state);
	void      sendDSQRequest( RequestInfo rinfo, const quint8 &state);
	void      sendJoinRequest( RequestInfo rinfo, const quint8 &state);

	void      handleConnectAnswer( RequestInfo rinfo, const gp_connect_request& request);
	void      handleDSQAnswer( RequestInfo rinfo, const gp_default_server_query& query );
	void      handleJoinAnswer( RequestInfo rinfo, const gp_join_request& request );

private:
  Client    &client;

};
