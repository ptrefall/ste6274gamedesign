#pragma once

#include "../RequestInfo.h"
#include "../ParsedData.h"

#include <Protocol/gameprotocol.h>

#include <QRunnable>
#include <QObject>
#include <QDataStream>

class Client;

class ParseAnswerTask : public QObject, public QRunnable
{
  Q_OBJECT
public:
	explicit ParseAnswerTask(Client &client, const RequestInfo &rinfo);

protected:
	void queue(ParsedData *data);
	Client  &client;
	RequestInfo rinfo;
};
