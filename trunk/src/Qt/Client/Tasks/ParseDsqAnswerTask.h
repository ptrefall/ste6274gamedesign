#pragma once

#include "ParseAnswerTask.h"

class ParseDsqAnswerTask : public ParseAnswerTask
{
public:
	ParseDsqAnswerTask(const RequestInfo &rinfo, const gp_default_server_query_answer &answer);
    void run();

private:
    gp_default_server_query_answer answer;
};
