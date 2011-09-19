#include "Client.h"

#include "PFW/NegotiationPFW.h"
#include "Tasks/SendPkgTask.h"
#include "ClientWorker.h"

#include <QDebug>
#include <QThreadPool>


Client::Client(QObject *parent) 
	: TcpClient(parent)
{

	int num_cores = QThread::idealThreadCount();
	if(num_cores < 1)
		num_cores = 2;
	QThreadPool::globalInstance()->setMaxThreadCount( num_cores );

	gp_send_header.size = sizeof(gp_header) - sizeof(gp_header_prefix);

	clientWorker = new ClientWorker(*this);

	negotiationPFW = new NegotiationPFW(*this);

	// Connect packet factory to tcp client (this),
	// so that packet tasks are distributed correctly
	connect(negotiationPFW,	SIGNAL(signDataBuildt			(DataPacket)),
			this,			SLOT(distributeData				(DataPacket)));

	// Connect client worker to packet factory worker
	connect(clientWorker,	SIGNAL(signBuildConnectRequest	(const RequestInfo &, const quint8 &)),
			negotiationPFW, SLOT(buildConnectRequestPkg		(const RequestInfo &, const quint8 &)));

	connect(clientWorker,	SIGNAL(signQueueError			(const RequestInfo &, const quint16 &)),
			negotiationPFW, SLOT(buildServerErrorPkg		(const RequestInfo &, const quint16 &)));

	connect(clientWorker,	SIGNAL(signBuildDSQRequest		(const RequestInfo &, const gp_default_server_query &)),
			negotiationPFW, SLOT(buildDSQPkg				(const RequestInfo &, const gp_default_server_query &)));

	connect(clientWorker,	SIGNAL(signBuildJoinRequest		(const RequestInfo 6, const quint8 &, const quint32 &)),
			negotiationPFW, SLOT(buildJoinPkg				(const RequestInfo &, const quint8 &, const quint32 &)));
}

Client::~Client()
{
	delete clientWorker;
	delete negotiationPFW;
}

void Client::distributeData( const DataPacket& pkg )
{
	socket->send(pkg.getData());
}
