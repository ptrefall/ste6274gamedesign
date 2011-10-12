#pragma once

#include <types_config.h>
#include <Protocol/gameprotocol.h>

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>
#include <QMutexLocker>

class SocketParseTask;
class Packet;
template<typename T>class SocketPackTask;
class Client;
class Game;

class ClientThread : public QObject
{
	Q_OBJECT
public:
	explicit ClientThread(Game &game, Client &client, QObject *parent = 0);
	virtual ~ClientThread();

	void stopThread() { /*QMutexLocker scoped_lock(&threadMutex);*/ thread_running = false; }
	bool isThreadRunning() const { return thread_running; }

	void queueParsedPacket(Packet *packet, bool game_packet);
	void queuePackedPacket(const QByteArray &block, bool game_packet);

	T_Vector<Packet*>::Type getParsedGamePackets();

	QTcpSocket &getSocket() { return *socket; }
	QTcpSocket &getGameSocket() { return *game_socket; }
	SocketParseTask &getParser() { return *socketParseTask; }
	Client &getClient() { return client; }

	void update();
	void onMoveEvent(const T_String &x, const T_String &y);

signals:
	void signHostFound();
	void signHandshakeSucceeded();
	void signHandshakeFailed(const QString &);
	void signConnectSucceeded();
	void signConnectFailed(const QString &);
	void signMoveToLobby(const gp_default_server_query_answer &);

private slots:
	void connectToHost(const QHostAddress& address, const quint16 &port);
	void disconnectFromHost();
	void hostFound();
	void connectionSucceeded();
	void displayError(QAbstractSocket::SocketError);
	void readReady();
	void loginToGame();
	void game_hostFound();
	void game_connectionSucceeded();
	void game_readReady();

private:
	void run();

	void sendPackedPacket(const QByteArray &block, bool game_packet);
	void handleParsedPacket(Packet *packet);
	void handleParsedGamePacket(Packet *packet);
	void handleConnectAnswer(const gp_connect_answer &answer);
	void handleDsqAnswer(const gp_default_server_query_answer &answer);
	void handleJoinAnswer(const gp_join_answer &answer);
	void handleClientVerificationRequest(const bool /*request*/);
	void handleGameUpdate(const gp_game_update &answer);
	
	QTcpSocket *socket;
	QTcpSocket *game_socket;

	//T_Vector<SocketParseTask*>::Type socketParseTasks;
	SocketParseTask *socketParseTask;
	SocketPackTask<gp_connect_request> *conReqTask;
	SocketPackTask<gp_default_server_query> *dsqTask;

	T_Vector<Packet*>::Type parsedPackets;
	T_Vector<Packet*>::Type parsedGamePackets;
	T_Vector<QByteArray>::Type packedPackets;
	T_Vector<QByteArray>::Type packedGamePackets;

	//QMutex threadMutex;

	Game &game;
	Client &client;

	volatile bool thread_running;
	volatile bool connect_to_host;
	volatile bool connect_to_game_host;

	QHostAddress address;
	quint16 port;
	quint16 game_port;
	bool is_game_port_valid;

	gp_uint32 request_count;
};
