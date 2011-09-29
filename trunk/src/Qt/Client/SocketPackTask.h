#pragma once

#include "Client.h"
#include "Packet.h"
#include <Protocol/gameprotocol.h>

#include <QRunnable>
#include <QTcpSocket>

template<typename PacketType>
class SocketPackTask : public QRunnable
{
public:
	explicit SocketPackTask(Client &client, QTcpSocket &socket) : client(client), socket(socket), is_loaded(false) { setAutoDelete(false); }
	virtual ~SocketPackTask(){}

	void load(const gp_uint8 &type, const bool &answer, const PacketType &packet_data)
	{
		this->type = type;
		this->answer = answer;
		this->packet_data = packet_data;
		is_loaded = true;
	}

protected:
	void run()
	{
		if(is_loaded == false)
			return;

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

		client.queuePackedPacket(block);

		is_loaded = false;
	}
	void packRequest(gp_header &header, QDataStream &out)
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
	Client &client;
	QTcpSocket &socket;

	gp_uint8 type;
	bool answer;
	bool is_loaded;
	PacketType packet_data;
};
