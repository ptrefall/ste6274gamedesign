#include "Packet.h"

gp_header Packet::header;
QByteArray *Packet::block = 0x0;
QDataStream *Packet::stream = 0x0;
bool Packet::writing = false;
bool Packet::reading = false;

bool Packet::beginWrite(const gp_uint8_t &type, const gp_uint32_t &request_id, const bool &answer)
{

	if(writing || reading)
		return false;

	writing = true;

	header.size = sizeof(gp_header) - sizeof(gp_header_prefix);
	header.type = type;
	header.flags.answer = answer ? 1 : 0;
	header.request_id = request_id;

	block = new QByteArray();
	stream = new QDataStream(block, QIODevice::ReadWrite);
	stream->setVersion( QDataStream::Qt_4_7 );
	stream->writeRawData( (char*)(&header), sizeof(gp_header) );

	return true;
}

bool Packet::endWrite(QByteArray &block)
{
	if(!writing)
		return false;

	block = *Packet::block;
	delete Packet::stream; Packet::stream = 0x0;
	delete Packet::block; Packet::block = 0x0;

	writing = false;
	return true;
}

bool Packet::beginRead(QTcpSocket *socket)
{
	if(writing || reading)
		return false;

	reading = true;

	stream = new QDataStream(socket);
	stream->setVersion( QDataStream::Qt_4_7 );
	stream->readRawData((char*)(&header), sizeof(gp_header));
}

bool Packet::endRead()
{
	if(!reading)
		return false;

	delete Packet::stream; Packet::stream = 0x0;

	reading = false;
	return true;
}
