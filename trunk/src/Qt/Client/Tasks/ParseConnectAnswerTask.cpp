#include "ParseConnectAnswerTask.h"

ParseConnectAnswerTask::ParseConnectAnswerTask(const RequestInfo &rinfo, const gp_connect_answer &answer)
	: ParseAnswerTask(rinfo), answer(answer)
{
}

void ParseConnectAnswerTask::run()
{
	//Parse
	//...

	//Queue parsed data
	queue();
}
