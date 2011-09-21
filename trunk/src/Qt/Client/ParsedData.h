#pragma once

#include <QByteArray>

class DataPacket 
{
public:
	DataPacket() : cid(0) {}
	DataPacket(quint32 cid, const QByteArray &data) : cid(cid), data(data) {}

	quint32 getClientID() const { return cid; }
	const QByteArray &getData() const { return data; }

private:
	quint32 cid;
	QByteArray data;
};
