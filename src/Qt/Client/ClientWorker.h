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
	void signBuildConnectRequest(const RequestInfo &rinfo, const quint8 &state);
	void signBuildDSQRequest(const RequestInfo &rinfo, const gp_default_server_query &query);
	void signBuildJoinRequest(const RequestInfo &rinfo, const quint8 &state, const quint32 &validation_conde);
	void signQueueError(const RequestInfo &rinfo, const quint16 &error);

	void signParseConnectAnswer(const RequestInfo &rinfo, const gp_connect_answer &answer);
	void signParseDSQAnswer(const RequestInfo &rinfo, const gp_default_server_query_answer &answer);
	void signParseJoinAnswer(const RequestInfo &rinfo, const gp_join_answer &answer);

public slots:
	void sendConnectRequest(const RequestInfo &rinfo, const quint8 &state);
	void sendDSQRequest(const RequestInfo &rinfo, const quint8 &state);
	void sendJoinRequest(const RequestInfo &rinfo, const quint8 &state);

	void handleConnectAnswer(const RequestInfo &rinfo, const gp_connect_answer &answer);
	void handleDSQAnswer(const RequestInfo &rinfo, const gp_default_server_query_answer &answer);
	void handleJoinAnswer(const RequestInfo &rinfo, const gp_join_answer &answer);

private:
  Client &client;

};
