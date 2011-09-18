#include "SendPkgTask.h"

#include "../TcpSocket.h"

#include <QDebug>
#include <QThread>

SendPkgTask::SendPkgTask()
{
	data_set = false;
	socket_set = false;
}

void SendPkgTask::run()
{
	/*qDebug() << QThread::currentThreadId() << " SendPkgTask::run()";

	if( !_data_set || !_socket_set )
		return;

	// Send pkg
	qDebug() << "Server: ClientConnection::handleClientErrorTask(...) - write block to socket";
	_socket->send( _block );
	qDebug() << "Server: ClientConnection::handleClientErrorTask(...) - write block to socket END";*/
}

void SendPkgTask::set(const quint32 &client_id, const QByteArray &data)
{
	this->data = data;
	this->client_id = client_id;

	data_set = true;
}

void SendPkgTask::setSocket(TcpSocket *socket)
{
	this->socket = socket;
	socket_set = true;
}
