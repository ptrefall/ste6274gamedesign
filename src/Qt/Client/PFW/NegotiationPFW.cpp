#include "NegotiationPFW.h"

#include "../Tasks/BuildConnectRequestPkgTask.h"
#include "../Tasks/BuildDsqPkgTask.h"
#include "../Tasks/BuildJoinRequestPkgTask.h"

#include <QThreadPool>

NegotiationPFW::NegotiationPFW(Client &client, QObject *parent)
	: PacketFactoryWorker(parent), client(client)
{
}

void NegotiationPFW::buildConnectRequestPkg(const RequestInfo &rinfo, const quint8 &state)
{
	BuildConnectRequestPkgTask *task = new BuildConnectRequestPkgTask;
	task->set(rinfo);
	task->load(state);

	connectTask(task);
	launch(task);
}

void NegotiationPFW::buildDSQPkg(const RequestInfo &rinfo, const gp_default_server_query &query)
{
	BuildDSQPkgTask *task = new BuildDSQPkgTask;
	task->set(rinfo);
	task->load(&client, query);

	connectTask(task);
	launch(task);
}

void NegotiationPFW::buildJoinPkg(const RequestInfo &rinfo, const quint8 &state, const quint32 &validation_code)
{
	BuildJoinRequestPkgTask *task = new BuildJoinRequestPkgTask;
	task->set(rinfo);
	task->load(state, validation_code);

	connectTask(task);
	launch(task);
}
