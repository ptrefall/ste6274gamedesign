#pragma once

#include <Protocol/gameprotocol.h>
#include <QtGui/QDialog.h>
#include <ui_connect.h>
#include <QTime>
#include <QHostAddress>

class Game;

namespace Ui
{

class Join;
class ConnectionFailed;

class Connect : public QDialog, public Ui::ConnectDialog
{
Q_OBJECT
public:
    Connect(Join *join, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Connect();

	void connectToServerAttempt();

signals:
	void signConnectToHost(const QHostAddress &address, const quint16 &port);

private slots:
	void onClose();
	void onHostFound();
	void onHandshakeSucceeded();
	void onHandshakeFailed(const QString &why);
	void onConnectionSucceeded();
	void onConnectionFailed(const QString &why);
	void onMoveToLobby(const gp_default_server_query_answer &);
	void onUpdateProgress();

private:
	Join *join;
	Game &game;
	QTime timer;
	bool tryingToConnect;
	ConnectionFailed *connectionFailed;

	enum eConnectionState
	{
		E_INITIATE_CONNECTION = 0,
		E_HOST_FOUND,
		E_HANDSHAKE_SUCCEEDED,
		E_HANDSHAKE_FAILED,
		E_CONNECTION_SUCCEEDED,
		E_CONNECTION_FAILED,
		E_CONNECTION_ABORTED,
		E_SERVER_INFO_RECEIVED,
		E_SERVER_INFO_PROCESSED,
		E_FINISHED
	} state;
};

}
