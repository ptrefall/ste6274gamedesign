#include "Client.h"
#include "ClientThread.h"
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

	thread = new ClientThread(*this);
}

Client::~Client()
{
	thread->stopThread();
}

void Client::connectToHost(const QHostAddress& address, const quint16 &port)
{
	emit signConnectToHost(address, port);
}

void Client::update(float dt)
{
	thread->update();
}

T_Vector<Packet*>::Type Client::getParsedGamePackets()
{
	return thread->getParsedGamePackets();
}
