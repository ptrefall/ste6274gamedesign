#include "ParseConnectAnswerTask.h"
#include <Game/ParsedNetData/ParsedConnectData.h>
#include "../Client.h"

ParseConnectAnswerTask::ParseConnectAnswerTask(Client &client, const RequestInfo &rinfo, const gp_connect_answer &answer)
	: ParseAnswerTask(client, rinfo), answer(answer)
{
}

void ParseConnectAnswerTask::run()
{
	//Parse
	//...
	ParsedData *data = new ParsedConnectData(answer.state > 0);
	connect(data, SIGNAL(signParsedDataInvoked(ParsedData *)),
			&client, SLOT(connectAnswerDataInvoked(ParsedData *)));

	//Queue parsed data
	queue(data);
}
