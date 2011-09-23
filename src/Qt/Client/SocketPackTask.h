#pragma once

#include "Client.h"
#include <Protocol/gameprotocol.h>

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>

class SocketPackTask : public QObject, public QRunnable
{
	Q_OBJECT
public:
	explicit SocketPackTask(Client &client, QTcpSocket &socket, QObject *parent = 0);
	virtual ~SocketPackTask();

protected:
	void run();
	void packRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	void packAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	template<typename T> addToBlock(QDataStream &out, const T &t);

private:
	Client &client;
	QTcpSocket &socket;
};

template <typename T>
inline void SocketPackTask::addToBlock(QDataStream &out, const T &t)
{
	out.writeRawData((const char*)(&t), sizeof(T));
}