#include "Client.h"
#include "ClientThread.h"
#include <Game/Game.h>
#include <QThread>
#include <QThreadPool>
#include <QMutexLocker>

Client::Client(Game &game, QObject *parent)
: game(game), QObject(parent), client_id(0), is_client_id_valid(false), is_validation_code_valid(false)
{
	int num_cores = QThread::idealThreadCount();
	if(num_cores < 1)
		num_cores = 2;
	QThreadPool::globalInstance()->setMaxThreadCount( num_cores );

	thread = new ClientThread(game, *this);
}

Client::~Client()
{
	thread->stopThread();
}

void Client::connectToHost(const QHostAddress& address, const quint16 &port)
{
	emit signConnectToHost(address, port);
}

void Client::loginToGame()
{
	emit signLoginToGame();
}

void Client::update(float dt)
{
	thread->update();
}

T_Vector<Packet*>::Type Client::getParsedGamePackets()
{
	return thread->getParsedGamePackets();
}

void Client::onMoveEvent(const T_String &x, const T_String &y)
{
	thread->onMoveEvent(x,y);
}
