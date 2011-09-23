#include "SocketParseTask.h"
#include "Packet.h"

SocketParseTask::SocketParseTask(Client &client, QTcpSocket &socket, QObject *parent)
	: QObject(parent), client(client), socket(socket)
{
}

void SocketParseTask::run()
{
	QDataStream in(&socket);
	in.setVersion(QDataStream::Qt_4_7);

	if(socket.bytesAvailable() < (int)sizeof(gp_header))
		return;

	gp_header header;
	in.readRawData((char*)(&header), sizeof(gp_header));

	gp_header_prefix prefix;
	if(header.prefix.id != prefix.id)
		return;

	if(header.flags.answer) 
		parseAnswer(prefix, header, in);
	else
		parseRequest(prefix, header, in);
}

void SocketParseTask::parseRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	gp_uint32 body_size = getRequestBodySize(header.type);
	if(socket.bytesAvailable() < body_size)
		return;

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query request;
			in.readRawData((char*)(&request), sizeof(gp_default_server_query));
			client.queueServerPacket(new Packet(request));
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_request request;
			in.readRawData((char*)(&request), sizeof(gp_connect_request));
			client.queueServerPacket(new Packet(request));
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_request request;
			in.readRawData((char*)(&request), sizeof(gp_join_request));
			client.queueServerPacket(new Packet(request));
		}break;
	default: return;
	};
}

void SocketParseTask::parseAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	gp_uint32 body_size = getAnswerBodySize(header.type);
	if(socket.bytesAvailable() < body_size)
		return;

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_default_server_query_answer));
			client.queueServerPacket(new Packet(answer));
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_connect_answer));
			client.queueServerPacket(new Packet(answer));
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_join_answer));
			client.queueServerPacket(new Packet(answer));
		}break;
	default: return;
	};
}

gp_uint32 SocketParseTask::getRequestBodySize(const gp_uint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return (gp_uint32)sizeof(gp_default_server_query);
	case GP_REQUEST_TYPE_CONNECT:				return (gp_uint32)sizeof(gp_connect);
	case GP_REQUEST_TYPE_JOIN:					return (gp_uint32)sizeof(gp_join);
	default:									return (gp_uint32)0;
	};
}

gp_uint32 SocketParseTask::getAnswerBodySize(const gp_uint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return (gp_uint32)sizeof(gp_default_server_query_answer);
	case GP_REQUEST_TYPE_CONNECT:				return (gp_uint32)sizeof(gp_connect_answer);
	case GP_REQUEST_TYPE_JOIN:					return (gp_uint32)sizeof(gp_join_answer);
	default:									return (gp_uint32)0;
	};
}
