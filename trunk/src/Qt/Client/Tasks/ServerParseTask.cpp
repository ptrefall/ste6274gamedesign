#include "ServerParseTask.h"

#include <QDataStream>

quint32 ServerParseTask::computeBodySize(const quint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return sizeof(gp_default_server_query_answer);
	case GP_REQUEST_TYPE_CONNECT:				return sizeof(gp_connect_answer);
	case GP_REQUEST_TYPE_JOIN:					return sizeof(gp_join_answer);
	default:									return 0;
	};
}

void ServerParseTask::handleRead(const quint8 &type, QDataStream &in)
{
	switch(type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_default_server_query_answer));
			emit signRegisterDSQAnswer(getRequestInfo(), answer);
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_connect_answer));
			emit signRegisterConnectAnswer(getRequestInfo(), answer);
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_join_answer));
			emit signRegisterJoinAnswer(getRequestInfo(), answer);
		}break;
	default: return;
	};
}

bool ServerParseTask::validateHeaderType(const quint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
	case GP_REQUEST_TYPE_CONNECT:
	case GP_REQUEST_TYPE_JOIN:
		return true;

	default: return false;
	};
}
