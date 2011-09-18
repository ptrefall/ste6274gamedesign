#include "PacketFactoryWorker.h"

#include "../Tasks/BuildServerErrorPkgTask.h"

#include <QThreadPool>
#include <QDebug>

PacketFactoryWorker::PacketFactoryWorker(QObject *parent) 
	: QObject(parent) 
{
}

void PacketFactoryWorker::buildServerErrorPkg(const RequestInfo &rinfo, const quint16 &error)
{
	BuildPkgTask *task = new BuildServerErrorPkgTask;
	task->set(rinfo);
	task->load(error);

	connectTask(task);
	launch(task);
}

void PacketFactoryWorker::connectTask(BuildPkgTask *task)
{
	connect(task, SIGNAL(signDataPkgBuilt(DataPacket)),
			this, SLOT(relaySendData(DataPacket)));
}

void PacketFactoryWorker::launch(BuildPkgTask *task)
{
	QThreadPool::globalInstance()->start(task);
}

void PacketFactoryWorker::relaySendData(const DataPacket& pkg)
{
	emit signDataBuilt(pkg);
}
