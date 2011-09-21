#include "ParseDsqAnswerTask.h"

ParseDsqAnswerTask::ParseDsqAnswerTask(const RequestInfo &rinfo, const gp_default_server_query_answer &answer)
	: ParseAnswerTask(rinfo), answer(answer)
{
}

void ParseDsqAnswerTask::run()
{
	//Parse
	//...

	//Queue parsed data
	queue();
}
