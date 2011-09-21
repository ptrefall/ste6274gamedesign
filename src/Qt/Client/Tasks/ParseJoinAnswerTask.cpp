#include "ParseJoinAnswerTask.h"

ParseJoinAnswerTask::ParseJoinAnswerTask(const RequestInfo &rinfo, const gp_join_answer &answer)
	: ParseAnswerTask(rinfo), answer(answer)
{
}

void ParseJoinAnswerTask::run()
{
	//Parse
	//...

	//Queue parsed data
	queue();
}
