#include "ParseJoinAnswerTask.h"
#include <Game/ParsedNetData/ParsedJoinData.h>
#include "../Client.h"

ParseJoinAnswerTask::ParseJoinAnswerTask(Client &client, const RequestInfo &rinfo, const gp_join_answer &answer)
	: ParseAnswerTask(client, rinfo), answer(answer)
{
}

void ParseJoinAnswerTask::run()
{
	//Parse
	//...
	ParsedData *data = new ParsedJoinData();
	connect(data, SIGNAL(signParsedDataInvoked(ParsedData *)),
			&client, SLOT(joinAnswerDataInvoked(ParsedData *)));

	//Queue parsed data
	queue(data);
}
