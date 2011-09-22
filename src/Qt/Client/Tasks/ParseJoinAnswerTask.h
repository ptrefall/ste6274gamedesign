#pragma once

#include "ParseAnswerTask.h"

class ParseJoinAnswerTask : public ParseAnswerTask
{
public:
	ParseJoinAnswerTask(Client &client, const RequestInfo &rinfo, const gp_join_answer &answer);
    void run();

private:
    gp_join_answer answer;
};
