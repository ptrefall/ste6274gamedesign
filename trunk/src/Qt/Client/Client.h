#pragma once

#include <types_config.h>

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class SocketParseTask;
class Packet;

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

	void connectToHost(const QHostAddress& address = QHostAddress::LocalHost, const quint16 &port = 1234);

	void queueServerPacket(Packet *packet);

signals:
	void signHostFound();
	void signHandshakeSucceeded();
	void signHandshakeFailed(const QString &);
	void signConnectSucceeded();
	void signConnectFailed(const QString &);

protected slots:
	void hostFound();
	void connectionSucceeded();
	void displayError(QAbstractSocket::SocketError);
	virtual void readReady();

private:
	QTcpSocket *socket;

	gp_header packet_header;

	SocketParseTask *socketParseTask;

	T_Vector<Packet*>::Type serverPackets;
};
