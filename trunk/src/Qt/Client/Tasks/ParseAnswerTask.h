#pragma once

#include "../RequestInfo.h"
#include "../DataPacket.h"

#include <Protocol/gameprotocol.h>

#include <QRunnable>
#include <QObject>
#include <QDataStream>

class ParseAnswerTask : public QObject, public QRunnable
{
  Q_OBJECT
public:
	explicit ParseAnswerTask(const RequestInfo &rinfo);

protected:
	void queue();

private:
	RequestInfo rinfo;
};
