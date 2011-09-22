#pragma once

#include "ParseAnswerTask.h"

class ParseConnectAnswerTask : public ParseAnswerTask
{
public:
	ParseConnectAnswerTask(Client &client, const RequestInfo &rinfo, const gp_connect_answer &answer);
    void run();

private:
    gp_connect_answer answer;
};