#pragma once

#include <types_config.h>
#include <Protocol/gameprotocol.h>

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMutex>

class ClientThread;
class Packet;
class Game;

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(Game &game, QObject *parent = 0);
	virtual ~Client();

	void update(float dt);
	T_Vector<Packet*>::Type getParsedGamePackets();

	ClientThread &getClientThread() { return *thread; }

	const bool isIdValid() const { return is_client_id_valid; }
	const bool isValidationCodeValid() const { return is_validation_code_valid; }
	const unsigned long &getId() const { return client_id; }
	const unsigned long &getValidationCode() const { return validation_code; }

	void setClientId(const unsigned long &id) { client_id = id; is_client_id_valid = true; }
	void setValidationCode(const unsigned long &code) { validation_code = code; is_validation_code_valid = true; }

signals:
	void signConnectToHost(const QHostAddress&, const quint16 &);
	void signLoginToGame();

public slots:
	void connectToHost(const QHostAddress& address = QHostAddress::LocalHost, const quint16 &port = 1234);
	void loginToGame();

private:
	bool is_client_id_valid;
	unsigned long client_id;
	bool is_validation_code_valid;
	unsigned long validation_code;

	Game &game;
	ClientThread *thread;
};
