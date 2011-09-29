#include "Client.h"
#include "SocketParseTask.h"
#include "SocketPackTask.h"
#include <QThread>
#include <QThreadPool>
#include <QMutexLocker>

Client::Client(QObject *parent)
: QObject(parent), client_id(0), is_client_id_valid(false)
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

	// Create and pack a connect request package
	gp_connect_request request;
	request.connect_flag = GP_CONNECT_FLAG_CONNECT;
	
	conReqTask = new SocketPackTask<gp_connect_request>(*this, *socket);
	conReqTask->load(GP_REQUEST_TYPE_CONNECT, false, request);
	QThreadPool::globalInstance()->start(conReqTask);
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

void Client::queueParsedPacket(Packet *packet)
{
	QMutexLocker scoped_lock(&parsedMutex);
	parsedPackets.push_back(packet);
}

void Client::queuePackedPacket(const QByteArray &block)
{
	QMutexLocker scoped_lock(&packedMutex);
	packedPackets.push_back(block);
}

void Client::update(float dt)
{
	//Handle packed packets in mutex scope
	{
		QMutexLocker scoped_lock(&packedMutex);
		if(!packedPackets.empty())
		{
			T_Vector<QByteArray>::Type temp = packedPackets;
			packedPackets.clear();
			scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				sendPackedPacket(temp[i]);
		}
	}

	//Handle parsed packets in mutex scope
	{
		QMutexLocker scoped_lock(&parsedMutex);
		if(!parsedPackets.empty())
		{
			T_Vector<Packet*>::Type temp = parsedPackets;
			parsedPackets.clear();
			scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				handleParsedPacket(temp[i]);
		}
	}
}

T_Vector<Packet*>::Type Client::getParsedGamePackets()
{
	/*T_Vector<Packet*>::Type temp;

	QMutexLocker scoped_lock(&parsedMutex);
	if(parsedPackets.empty())
		return temp;
	temp = parsedPackets;
	parsedPackets.clear();
	scoped_lock.unlock();*/

	if(parsedGamePackets.empty())
		return parsedGamePackets;

	T_Vector<Packet*>::Type temp = parsedGamePackets;
	parsedGamePackets.clear();

	return temp;
}

void Client::sendPackedPacket(const QByteArray &block)
{
	qint64 bytes_written = socket->write(block);
	if(bytes_written == 0)
	{
		return;
	}
}

void Client::handleParsedPacket(Packet *packet)
{
	if(packet->isConAns())
		handleConnectAnswer(packet->getConAns());
	else if(packet->isDsqAns())
		handleDsqAnswer(packet->getDsqAns());
}

void Client::handleConnectAnswer(const gp_connect_answer &answer)
{
	if(answer.state == GP_CONNECT_FLAG_CONNECT)
	{
		is_client_id_valid = true;
		client_id = answer.client_id;
		emit signConnectSucceeded();

		//Create and pack a default server query package
		gp_default_server_query request; //Use default protocol settings...
		
		dsqTask = new SocketPackTask<gp_default_server_query>(*this, *socket);
		dsqTask->load(GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY, false, request);
		QThreadPool::globalInstance()->start(dsqTask);
	}
	else
	{

	}
}

void Client::handleDsqAnswer(const gp_default_server_query_answer &answer)
{
	if(answer.request_flags.server_info)
	{
	}
}
