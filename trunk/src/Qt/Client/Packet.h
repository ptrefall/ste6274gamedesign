#pragma once

#include <Protocol/gameprotocol.h>
#include <QObject>
#include <QTcpSocket>

class Packet
{
public:
	static bool beginWrite(const gp_uint8_t &type, const gp_uint32_t &request_id, const bool &answer = false);
	template<class T> static bool write(const T &data);
	static bool endWrite(QByteArray &block);

	static bool beginRead(QTcpSocket *socket);
	template<class T> static bool read(T &data);
	static bool endRead();

	static const gp_header &getHeader() { return header; }
	static bool isWriting() { return writing; }
	static bool isReading() { return reading; }

private:
	static gp_header header;
	static QByteArray *block;
	static QDataStream *stream;
	static bool writing;
	static bool reading;
};

template<class T>
inline bool Packet::write(const T &data)
{
	if(!writing)
		return false;

	stream->writeRawData(reinterpret_cast<const char*>(&data), sizeof(T));

	return true;
}

template<class T>
inline bool Packet::read(T &data)
{
	if(!reading)
		return false;

	stream->readRawData(reinterpret_cast<char*>(&data), sizeof(T));

	return true;
}
