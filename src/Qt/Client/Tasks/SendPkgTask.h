#pragma once

#include <QObject>
#include <QRunnable>

class TcpSocket;

class SendPkgTask : public QObject, public QRunnable
{
	Q_OBJECT
public:
	explicit SendPkgTask();

	const quint32 &getClientID() const { return client_id; }
	void set(const quint32 &client_id, const QByteArray &data );
	void setSocket( TcpSocket* socket );

	void run();

private:
	TcpSocket *socket;
	QByteArray data;
	quint32 client_id;

	bool data_set;
	bool socket_set;

};
