#pragma once

#include "RequestInfo.h"
#include "DataPacket.h"
#include "ParsedData.h"

#include <Protocol/gameprotocol.h>

#include <QQueue>
#include <QMutex>

#include "TcpClient.h"

#include <types_config.h>

class NegotiationPFW;
class ClientWorker;
class ServerParseTask;

class Client : public TcpClient
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

	void queueAnswer(ParsedData *data);

	T_Vector<ParsedData*>::Type getParsedAnswerData_ThreadSafe();

	
public slots:
	void connectAnswerDataInvoked(ParsedData *);
	void dsqAnswerDataInvoked(ParsedData *);
	void joinAnswerDataInvoked(ParsedData *);

protected slots:
	virtual void readReady();

protected slots:
	void distributeData(const DataPacket &pkg);

protected:
	virtual void onHandshakeSuccessful();

private:
	gp_header gp_send_header;

	NegotiationPFW *negotiationPFW;
	ClientWorker *clientWorker;
	ServerParseTask *serverParseTask;

	T_Vector<ParsedData*>::Type parsed_answer_data;

	gp_uint32 request_id;

	QMutex data_mutex;
};
