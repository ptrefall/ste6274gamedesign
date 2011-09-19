#pragma once

#include "RequestInfo.h"
#include "DataPacket.h"

#include <Protocol/gameprotocol.h>

#include <QQueue>

#include "TcpClient.h"

class NegotiationPFW;
class ClientWorker;

class Client : public TcpClient
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

protected slots:
	void distributeData(const DataPacket &pkg);

private:
	gp_header gp_send_header;

	NegotiationPFW *negotiationPFW;
	ClientWorker *clientWorker;
};
