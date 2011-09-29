#pragma once

#include <types_config.h>
#include <Protocol/gameprotocol.h>

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>

class SocketParseTask;
class Packet;
template<typename T>class SocketPackTask;

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

	void queueParsedPacket(Packet *packet);
	void queuePackedPacket(const QByteArray &block);
	void update(float dt);
	T_Vector<Packet*>::Type getParsedGamePackets();

	const bool &isIdValid() const { return is_client_id_valid; }

signals:
	void signHostFound();
	void signHandshakeSucceeded();
	void signHandshakeFailed(const QString &);
	void signConnectSucceeded();
	void signConnectFailed(const QString &);

public slots:
	void connectToHost(const QHostAddress& address = QHostAddress::LocalHost, const quint16 &port = 1234);

protected slots:
	void hostFound();
	void connectionSucceeded();
	void displayError(QAbstractSocket::SocketError);
	virtual void readReady();

private:
	void sendPackedPacket(const QByteArray &block);
	void handleParsedPacket(Packet *packet);
	void handleConnectAnswer(const gp_connect_answer &answer);
	void handleDsqAnswer(const gp_default_server_query_answer &answer);
	QTcpSocket *socket;

	gp_header packet_header;

	SocketParseTask *socketParseTask;
	SocketPackTask<gp_connect_request> *conReqTask;
	SocketPackTask<gp_default_server_query> *dsqTask;

	T_Vector<Packet*>::Type parsedPackets;
	T_Vector<Packet*>::Type parsedGamePackets;
	T_Vector<QByteArray>::Type packedPackets;

	QMutex parsedMutex;
	QMutex packedMutex;

	bool is_client_id_valid;
	unsigned long client_id;
};
