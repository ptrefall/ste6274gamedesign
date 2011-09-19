#include "TcpClient.h"

#include <QtNetwork>

TcpClient::TcpClient(QObject *parent) :
    QObject(parent), socket(0x0)
{
	socket = new TcpSocket(this);
}

void TcpClient::connectToHost(const QHostAddress& address, const quint16 &port)
{
	socket->connectToHost(address, port);
}
