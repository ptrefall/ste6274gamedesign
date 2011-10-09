#pragma once

#include <Protocol/gameprotocol.h>
#include "SocketPackTask.h"
#include <QObject>
#include <QTcpSocket>

class ClientThread;

class SocketParseTask : public QObject
{
	Q_OBJECT
public:
	explicit SocketParseTask(ClientThread &client);
	virtual ~SocketParseTask() {}

	void run();

protected:
	bool parseRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	bool parseAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	quint64 getRequestBodySize(const gp_uint8 &type);
	quint64 getAnswerBodySize(const gp_uint8 &type);

private:
	ClientThread &client;
	volatile bool is_parsing;
	volatile bool header_is_read;
	bool dsqRead;
	gp_header header;
	gp_header_prefix prefix;
};
