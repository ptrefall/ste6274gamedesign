#include "SocketParseTask.h"
#include "Packet.h"
#include "ClientThread.h"
#include "Client.h"

SocketParseTask::SocketParseTask(ClientThread &client)
	: client(client), is_parsing(false), header_is_read(false), dsqRead(false)
{
}

void SocketParseTask::run()
{
	if(is_parsing)
		return;

	is_parsing = true;

	QDataStream in(&client.getSocket());
	in.setVersion(QDataStream::Qt_4_7);

	gp_uint32 socket_bytes_available = client.getSocket().bytesAvailable();
	if(socket_bytes_available < (int)sizeof(gp_header))
		return;

	if(header_is_read == false)
	{
		header_is_read = true;
		gp_header new_header;
		in.readRawData((char*)(&new_header), sizeof(gp_header));
		if(new_header.prefix.id != prefix.id)
		{
			if(header.prefix.id != prefix.id)
				return;
		}
		else
		{
			header = new_header;
		}
	}

	if(header.flags.answer) 
		parseAnswer(prefix, header, in);
	else
		parseRequest(prefix, header, in);

	header_is_read = false;
	is_parsing = false;
}

void SocketParseTask::parseRequest(gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	gp_uint32 body_size = getRequestBodySize(header.type);
	gp_uint32 socket_bytes_available = client.getSocket().bytesAvailable();
	if(socket_bytes_available < body_size)
		return;

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query request;
			in.readRawData((char*)(&request), sizeof(gp_default_server_query));
			client.queueParsedPacket(new Packet(request));
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_request request;
			in.readRawData((char*)(&request), sizeof(gp_connect_request));
			client.queueParsedPacket(new Packet(request));
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_request request;
			in.readRawData((char*)(&request), sizeof(gp_join_request));
			client.queueParsedPacket(new Packet(request));
		}break;
	default: return;
	};
}

void SocketParseTask::parseAnswer(gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	gp_uint32 body_size = getAnswerBodySize(header.type);
	gp_uint32 socket_bytes_available = client.getSocket().bytesAvailable();
	/*if(socket_bytes_available < body_size)
		return;*/

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			if(dsqRead)
				return;
			dsqRead = true;

			gp_default_server_query_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_default_server_query_answer));
			client.queueParsedPacket(new Packet(answer));
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_connect_answer));
			client.queueParsedPacket(new Packet(answer));
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_join_answer));
			client.queueParsedPacket(new Packet(answer));
		}break;
	default: return;
	};
}

gp_uint32 SocketParseTask::getRequestBodySize(const gp_uint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return (gp_uint32)sizeof(gp_default_server_query);
	case GP_REQUEST_TYPE_CONNECT:				return (gp_uint32)sizeof(gp_connect_request);
	case GP_REQUEST_TYPE_JOIN:					return (gp_uint32)sizeof(gp_join_request);
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
