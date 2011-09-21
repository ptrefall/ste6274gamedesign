#include "TcpClient.h"

#include <QtNetwork>

TcpClient::TcpClient(QObject *parent) :
    QObject(parent), socket(0x0)
{
	socket = new TcpSocket(this);

	connect(socket, SIGNAL(hostFound()), this, SLOT(tcpHostFound()));
	connect(socket, SIGNAL(connected()), this, SLOT(tcpConnectionSucceeded()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readReady()));
}

void TcpClient::connectToHost(const QHostAddress& address, const quint16 &port)
{
	socket->connectToHost(address, port);
}

void TcpClient::tcpHostFound()
{
	emit targetHostFound();
}

void TcpClient::tcpConnectionSucceeded()
{
	emit handshakeSucceeded();
	onHandshakeSuccessful();
}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
	{
    case QAbstractSocket::RemoteHostClosedError:	emit handshakeFailed("Remote host closed");		break;
    case QAbstractSocket::HostNotFoundError:		emit handshakeFailed("Host not found");			break;
    case QAbstractSocket::ConnectionRefusedError:	emit handshakeFailed("Connection refused");		break;
    default:										emit handshakeFailed("Unknown error");			break;
    };
}
