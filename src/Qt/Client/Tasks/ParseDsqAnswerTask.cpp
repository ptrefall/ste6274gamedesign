#include "ParseDsqAnswerTask.h"
#include <Game/ParsedNetData/ParsedDsqData.h>
#include "../Client.h"

ParseDsqAnswerTask::ParseDsqAnswerTask(Client &client, const RequestInfo &rinfo, const gp_default_server_query_answer &answer)
	: ParseAnswerTask(client, rinfo), answer(answer)
{
}

void ParseDsqAnswerTask::run()
{
	//Parse
	//...
	ParsedData *data = new ParsedDsqData();
	connect(data, SIGNAL(signParsedDataInvoked(ParsedData *)),
			&client, SLOT(dsqAnswerDataInvoked(ParsedData *)));

	//Queue parsed data
	queue(data);
}
