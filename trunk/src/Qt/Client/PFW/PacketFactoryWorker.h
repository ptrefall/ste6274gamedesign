#pragma once

#include "../RequestInfo.h"
#include "../DataPacket.h"

#include <QObject>

class BuildPkgTask;
class Client;

class PacketFactoryWorker : public QObject
{
	Q_OBJECT
public:
	explicit PacketFactoryWorker(QObject *parent = 0);

public slots:
	void buildServerErrorPkg(const RequestInfo &rinfo, const quint16 &error);

signals:
	void signDataBuilt(const DataPacket &pkg);

protected:
	void connectTask(BuildPkgTask *task);
	void launch(BuildPkgTask *task);

private slots:
	void relaySendData(const DataPacket &data);
};
