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
	void parseRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	void parseAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	gp_uint32 getRequestBodySize(const gp_uint8 &type);
	gp_uint32 getAnswerBodySize(const gp_uint8 &type);

private:
	ClientThread &client;
	volatile bool is_parsing;
	volatile bool header_is_read;
	bool dsqRead;
	gp_header header;
	gp_header_prefix prefix;
};
