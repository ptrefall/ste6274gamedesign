#include "ParseAnswerTask.h"

#include "../DebugUtils.h"
#include "../Client.h"


ParseAnswerTask::ParseAnswerTask(Client  &client, const RequestInfo &rinfo)
	: client(client), rinfo(rinfo)
{
}

void ParseAnswerTask::queue(ParsedData *data)
{
	client.queueAnswer(data);
}
