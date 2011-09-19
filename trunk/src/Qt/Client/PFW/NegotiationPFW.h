#pragma once

#include "PacketFactoryWorker.h"

#include <Protocol/gameprotocol.h>

class NegotiationPFW : public PacketFactoryWorker
{
	Q_OBJECT
public:
    NegotiationPFW(Client &client, QObject *parent = 0);

public slots:
	void buildConnectRequestPkg(const RequestInfo &rinfo, const quint8 &state);
	void buildDSQPkg(const RequestInfo &rinfo, const gp_default_server_query &query);
	void buildJoinPkg(const RequestInfo &rinfo, const quint8 &state, const quint32 &validation_code);

private:
	Client  &client;
};
