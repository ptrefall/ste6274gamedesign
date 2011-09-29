#pragma once

#include "Client.h"
#include <Protocol/gameprotocol.h>

#include <QRunnable>
#include <QTcpSocket>

class SocketParseTask : public QRunnable
{
public:
	explicit SocketParseTask(Client &client, QTcpSocket &socket);
	virtual ~SocketParseTask() {}

protected:
	void run();
	void parseRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	void parseAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in);
	gp_uint32 getRequestBodySize(const gp_uint8 &type);
	gp_uint32 getAnswerBodySize(const gp_uint8 &type);

private:
	Client &client;
	QTcpSocket &socket;
};
