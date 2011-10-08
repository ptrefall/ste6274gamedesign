#pragma once

#include "ClientThread.h"
#include "Packet.h"
#include <Protocol/gameprotocol.h>

#include <QTcpSocket>

template<typename PacketType>
class SocketPackTask
{
public:
	explicit SocketPackTask(ClientThread &thread, const gp_uint8 &type, const bool &answer, const PacketType &packet_data) 
		: thread(thread), type(type), answer(answer), packet_data(packet_data)
	{
	}
	virtual ~SocketPackTask(){}

	void run()
	{
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);

		gp_header header;
		header.type = type;
		header.size = sizeof(gp_header) - sizeof(gp_header_prefix);
		header.flags.answer = answer;

		addHeaderToBlock(header, out);

		if(answer) 
			packAnswer(header, out);
		else
			packRequest(header, out);

		thread.queuePackedPacket(block);
	}

protected:
	void packRequest(gp_header &header, QDataStream &out)
	{
		switch(header.type)
		{
		case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
			{
				gp_default_server_query *query = reinterpret_cast<gp_default_server_query*>(&packet_data);
				query->request_flags.limit_list = 0;
				query->request_flags.map_info = 1;
				query->request_flags.player_list = 1;
				query->request_flags.rule_list = 0;
				query->request_flags.server_info = 1;
				query->request_flags.team_list = 0;
				query->server_fields.host_name = 1;
				query->server_fields.connect_port = 1;
				addToBlock(packet_data, out);
			}break;
		case GP_REQUEST_TYPE_CONNECT:
			{
				addToBlock(packet_data, out);
			}break;
		case GP_REQUEST_TYPE_JOIN:
			{
				addToBlock(packet_data, out);
			}break;
		default: return;
		};
	}
	void packAnswer(gp_header &header, QDataStream &out)
	{
		switch(header.type)
		{
		case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:
			{
				addToBlock(packet_data, out);
			}break;
		case GP_REQUEST_TYPE_CONNECT:
			{
				addToBlock(packet_data, out);
			}break;
		case GP_REQUEST_TYPE_JOIN:
			{
				addToBlock(packet_data, out);
			}break;
		default: return;
		};
	}
	void addToBlock(const PacketType &t, QDataStream &out)
	{
		out.writeRawData((const char*)(&t), sizeof(PacketType));
	}
	void addHeaderToBlock(const gp_header &header, QDataStream &out)
	{
		out.writeRawData((const char*)(&header), sizeof(gp_header));
	}

private:
	ClientThread &thread;

	gp_uint8 type;
	bool answer;
	bool is_loaded;
	PacketType packet_data;
};
