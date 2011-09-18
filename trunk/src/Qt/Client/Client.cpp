#include "Client.h"
#include "Packet.h"
#include <Protocol/gameprotocol.h>
#include <QtNetwork>

Client::Client(QObject *parent)
	: QObject(parent)
{
	// Find host address
	/*QList<QHostAddress> ip_address_list = QNetworkInterface::allAddresses();
	for(int i = 0; i < ip_address_list.size(); i++)
	{
		if((ip_address_list.at(i) != QHostAddress::LocalHost) && ip_address_list.at(i).toIPv4Address())
		{
			ip_address = ip_address_list.at(i).toString();
			break;
		}
	}*/

	// If no external address were available use localhost
	if(ip_address.isEmpty())
		ip_address = QHostAddress(QHostAddress::LocalHost).toString();

	socket = new QTcpSocket(this);
	connect(socket, SIGNAL(hostFound()), this, SLOT(tcpHostFound()));
	connect(socket, SIGNAL(connected()), this, SLOT(tcpConnectionSucceeded()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

	connect(socket, SIGNAL(readyRead()), this, SLOT(serverRequest()));



	request_id = 0;
}

Client::~Client()
{
  socket->abort();
  delete socket;
}

void Client::connectToServer(const QString &address, quint16 port )
{
  socket->abort();
  socket->connectToHost(address, port);
}

void Client::tcpHostFound()
{
	emit targetHostFound();
}

void Client::tcpConnectionSucceeded()
{
	emit handshakeSucceeded();
}

void Client::sendConnectRequest()
{
	gp_connect_request request;
	request.connect_flag = GP_CONNECT_FLAG_CONNECT;

	QByteArray block;
	Packet::beginWrite(GP_REQUEST_TYPE_CONNECT, ++request_id, false);
	Packet::write<gp_connect_request>(request);
	Packet::endWrite(block);
	socket->write( block );
}

void Client::sendDisconnectRequest()
{
	gp_connect_request request;
	request.connect_flag = GP_CONNECT_FLAG_DISCONNECT;

	QByteArray block;
	Packet::beginWrite(GP_REQUEST_TYPE_CONNECT, ++request_id, false);
	Packet::write<gp_connect_request>(request);
	Packet::endWrite(block);
	socket->write( block );
}

void Client::sendTestPkgToServer()
{
	QByteArray block;
	Packet::beginWrite(GP_REQUEST_TYPE_TEST, ++request_id, false);
	Packet::endWrite(block);
	socket->write( block );
}

void Client::serverRequest()
{
	qDebug() << "Client: Incoming server request!";
	Packet::beginRead(socket);
	switch(Packet::getHeader().type)
	{
	case GP_REQUEST_TYPE_CONNECT:
		gp_connect_answer answer;
		Packet::read<gp_connect_answer>(answer);
		qDebug() << "Type: Connect request";
		qDebug() << "- is answer, not request: " << Packet::getHeader().flags.answer;	
		qDebug() << "- the answer for connection request is: " << answer.state;
		if(answer.state == 1)
			emit connectionSucceeded();
		else
			emit connectionFailed("Server did not grant you connection access!");
		break;
	};
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
		emit handshakeFailed("Remote host closed");
        break;
    case QAbstractSocket::HostNotFoundError:
		emit handshakeFailed("Host not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
		emit handshakeFailed("Connection refused");
        break;
    default:
		emit handshakeFailed("Unknown error");
		break;
    }
}
