#include "SocketParseTask.h"
#include "Packet.h"
#include "ClientThread.h"
#include "Client.h"

SocketParseTask::SocketParseTask(ClientThread &client)
	: client(client), is_parsing(false), header_is_read(false)
{
}

void SocketParseTask::run(QTcpSocket &socket)
{
	if(is_parsing)
		return;
	else
		is_parsing = true;

	QDataStream in(&socket);
	in.setVersion(QDataStream::Qt_4_7);

	quint64 socket_bytes_available = socket.bytesAvailable();
	if(socket_bytes_available < (quint64)sizeof(gp_header))
	{
		is_parsing = false;
		return;
	}

	if(header_is_read == false)
	{
		header_is_read = true;
		gp_header new_header;
		in.readRawData((char*)(&new_header), sizeof(gp_header));
		if(new_header.prefix.id != prefix.id)
		{
			if(header.prefix.id != prefix.id)
			{
				//This should really never happen...
				is_parsing = false;
				return;
			}
		}
		else
		{
			header = new_header;
		}
	}

	bool success = false;
	if(header.flags.answer) 
		success = parseAnswer(socket, prefix, header, in);
	else
		success = parseRequest(socket, prefix, header, in);

	is_parsing = false;

	if(success == false)
		return;

	header_is_read = false;
}

bool SocketParseTask::parseRequest(QTcpSocket &socket, gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	quint64 body_size = getRequestBodySize(header.type);
	quint64 socket_bytes_available = socket.bytesAvailable();
	if(socket_bytes_available < body_size)
		return false;

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query request;
			in.readRawData((char*)(&request), sizeof(gp_default_server_query));
			client.queueParsedPacket(new Packet(request), false);
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_request request;
			in.readRawData((char*)(&request), sizeof(gp_connect_request));
			client.queueParsedPacket(new Packet(request), false);
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_request request;
			in.readRawData((char*)(&request), sizeof(gp_join_request));
			client.queueParsedPacket(new Packet(request), false);
		}break;
	case GP_REQUEST_TYPE_CLIENT_VERIFICATION:
		{
			client.queueParsedPacket(new Packet(GP_REQUEST_TYPE_CLIENT_VERIFICATION), true);
		}break;
	case GP_REQUEST_TYPE_GAME:
		{
			gp_game_request request;
			in.readRawData((char*)(&request), sizeof(gp_game_request));
			client.queueParsedPacket(new Packet(request), true);
		}break;
	default: return false;
	};
	
	return true;
}

bool SocketParseTask::parseAnswer(QTcpSocket &socket, gp_header_prefix &prefix, gp_header &header, QDataStream &in)
{
	quint64 body_size = getAnswerBodySize(header.type);
	quint64 socket_bytes_available = socket.bytesAvailable();
	if(socket_bytes_available < body_size)
		return false;

	switch(header.type)
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
		{
			gp_default_server_query_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_default_server_query_answer));
			client.queueParsedPacket(new Packet(answer), false);
		}break;
	case GP_REQUEST_TYPE_CONNECT:
		{
			gp_connect_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_connect_answer));
			client.queueParsedPacket(new Packet(answer), false);
		}break;
	case GP_REQUEST_TYPE_JOIN:
		{
			gp_join_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_join_answer));
			client.queueParsedPacket(new Packet(answer), false);
		}break;
	case GP_REQUEST_TYPE_CLIENT_VERIFICATION:
		{
			gp_client_verification_answer answer;
			in.readRawData((char*)(&answer), sizeof(gp_client_verification_answer));
			client.queueParsedPacket(new Packet(answer), true);
		}break;
	case GP_REQUEST_TYPE_GAME:
		{
			gp_game_update answer;
			in.readRawData((char*)(&answer), sizeof(gp_game_update));
			client.queueParsedPacket(new Packet(answer), true);
		}break;
	default: return false;
	};

	return true;
}

quint64 SocketParseTask::getRequestBodySize(const gp_uint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return (quint64)sizeof(gp_default_server_query);
	case GP_REQUEST_TYPE_CONNECT:				return (quint64)sizeof(gp_connect_request);
	case GP_REQUEST_TYPE_JOIN:					return (quint64)sizeof(gp_join_request);
	case GP_REQUEST_TYPE_CLIENT_VERIFICATION:	return (quint64)0; //Has no body
	default:									return (quint64)0;
	};
}

quint64 SocketParseTask::getAnswerBodySize(const gp_uint8 &type)
{
	switch(type) 
	{
	case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:	return (quint64)sizeof(gp_default_server_query_answer);
	case GP_REQUEST_TYPE_CONNECT:				return (quint64)sizeof(gp_connect_answer);
	case GP_REQUEST_TYPE_JOIN:					return (quint64)sizeof(gp_join_answer);
	case GP_REQUEST_TYPE_CLIENT_VERIFICATION:	return (quint64)0; //Has no body
	default:									return (quint64)0;
	};
}
