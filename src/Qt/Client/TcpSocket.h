#pragma once

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
public:
	TcpSocket() {}
    void send(const QByteArray &pkg);
};
