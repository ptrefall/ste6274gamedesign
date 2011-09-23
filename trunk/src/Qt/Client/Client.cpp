#include "Client.h"
#include "SocketParseTask.h"

Client::Client(QObject *parent)
: QObject(parent)
{
	int num_cores = QThread::idealThreadCount();
	if(num_cores < 1)
		num_cores = 2;
	QThreadPool::globalInstance()->setMaxThreadCount( num_cores );

	packet_header.size = sizeof(gp_header) - sizeof(gp_header_prefix);

	socket = new QTcpSocket(this);
	socketParseTask = new SocketParseTask(*this, *socket);

	connect(socket, SIGNAL(hostFound()), this, SLOT(hostFound()));
	connect(socket, SIGNAL(connected()), this, SLOT(connectionSucceeded()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readReady()));
}

Client::~Client()
{
}

void Client::connectToHost(const QHostAddress& address, const quint16 &port)
{
	socket->connectToHost(address, port);
}

void Client::hostFound()
{
	emit signHostFound();
}

void Client::connectionSucceeded()
{
	emit signHandshakeSucceeded();

}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
	{
    case QAbstractSocket::RemoteHostClosedError:	emit signHandshakeFailed("Remote host closed");		break;
    case QAbstractSocket::HostNotFoundError:		emit signHandshakeFailed("Host not found");			break;
    case QAbstractSocket::ConnectionRefusedError:	emit signHandshakeFailed("Connection refused");		break;
    default:										emit signHandshakeFailed("Unknown error");			break;
    };
}

void Client::readReady()
{
	QThreadPool::globalInstance()->start(socketParseTask);
}

void Client::queueServerPacket(Packet *packet)
{
	serverPackets.push_back(packet);
}
