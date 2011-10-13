#include "Connect.h"
#include "Join.h"
#include "ConnectionFailed.h"
#include "Lobby.h"
#include "MainMenu.h"
#include <Game/game.h>
#include <Game/GameOptions.h>
#include <Qt/Client/Client.h>
#include <Qt/Client/ClientThread.h>
#include <Qt/Client/SocketParseTask.h>
#include <QTimer.h>

using namespace Ui;

Connect::Connect(Join *join, Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), join(join), game(game), tryingToConnect(false)
{
    setupUi(this);

	connectionFailed = new ConnectionFailed(join, game);
	connectionFailed->hide();

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(connectCancelButton, SIGNAL(clicked()), SLOT(onClose()));
	//connect(this, SIGNAL(connectToServer()), SLOT(onServerConnectionAttempt()));
}
Connect::~Connect()
{
}

void Connect::connectToServerAttempt()
{
	GameOptions &opt = game.getOptions();
	if(opt.ip_addr == T_String())
		return;
	if(opt.port < 1000)
		return;

	connect(this, SIGNAL(signConnectToHost(const QHostAddress &, const quint16 &)), &game.getClient(), SLOT(connectToHost(const QHostAddress &, const quint16 &)));

	connect(&game.getClient().getClientThread(), SIGNAL(signHostFound()), SLOT(onHostFound()));
	connect(&game.getClient().getClientThread(), SIGNAL(signHandshakeSucceeded()), SLOT(onHandshakeSucceeded()));
	connect(&game.getClient().getClientThread(), SIGNAL(signHandshakeFailed(const QString &)), SLOT(onHandshakeFailed(const QString &)));
	connect(&game.getClient().getClientThread(), SIGNAL(signConnectSucceeded()), SLOT(onConnectionSucceeded()));
	connect(&game.getClient().getClientThread(), SIGNAL(signConnectFailed(const QString &)), SLOT(onConnectionFailed(const QString &)));
	connect(&game.getClient().getClientThread(), SIGNAL(signMoveToLobby(const gp_default_server_query_answer &)), SLOT(onMoveToLobby(const gp_default_server_query_answer &)));

	timer.start();
	state = E_INITIATE_CONNECTION;
	//game.getClient().connectToHost(QHostAddress(opt.ip_addr.c_str()), opt.port);
	emit signConnectToHost(QHostAddress(opt.ip_addr.c_str()), opt.port);
	tryingToConnect = true;
	onUpdateProgress();
}

void Connect::onClose()
{
	/*if(state == E_CONNECTION_SUCCEEDED)
		game.getClient().sendDisconnectRequest();*/

	state = E_CONNECTION_ABORTED;
	tryingToConnect = false;
	progressBarConnection->setValue(0);
	this->hide();
	join->show();
}

void Connect::onHostFound()
{
	state = E_HOST_FOUND;
}

void Connect::onHandshakeSucceeded()
{
	state = E_HANDSHAKE_SUCCEEDED;

	//game.getClient().sendConnectRequest();
}

void Connect::onHandshakeFailed(const QString &why)
{
	state = E_HANDSHAKE_FAILED;
	tryingToConnect = false;
	progressBarConnection->setValue(0);
	connectionFailed->labelConnectionFailed->setText(why);
	this->hide();
	connectionFailed->show();
}

void Connect::onConnectionSucceeded()
{
	state = E_CONNECTION_SUCCEEDED;

	tryingToConnect = false;
	progressBarConnection->setValue(100);

	//From here, attempt to join and enter lobby
	//game.getClient().sendJoinRequest();

}

void Connect::onConnectionFailed(const QString &why)
{
	state = E_CONNECTION_FAILED;
	tryingToConnect = false;
	progressBarConnection->setValue(0);
	connectionFailed->labelConnectionFailed->setText(why);
	this->hide();
	connectionFailed->show();
}

void Connect::onMoveToLobby(const gp_default_server_query_answer &answer)
{
	state = E_FINISHED;

	tryingToConnect = false;
	progressBarConnection->setValue(100);

	this->hide();
	join->getMainMenu().getLobby().setData(answer);
	join->getMainMenu().getLobby().show();
}

void Connect::onUpdateProgress()
{
	switch(state)
	{
	case E_INITIATE_CONNECTION:
		this->setWindowTitle("Initializing connection...");
		break;
	case E_HOST_FOUND:
		this->setWindowTitle("Host found, trying to connect...");
		break;
	case E_HANDSHAKE_SUCCEEDED:
		this->setWindowTitle("Handshake successful, requesting server connection...");
		break;
	case E_HANDSHAKE_FAILED:
		this->setWindowTitle("Handshake failed!");
		break;
	case E_CONNECTION_SUCCEEDED:
		this->setWindowTitle("Connection successful, requesting server information...");
		break;
	case E_CONNECTION_FAILED:
		this->setWindowTitle("Connection failed!");
		break;
	case E_CONNECTION_ABORTED:
		this->setWindowTitle("Connection aborted!");
		break;
	case E_SERVER_INFO_RECEIVED:
		this->setWindowTitle("Server information received, processing...");
		break;
	case E_SERVER_INFO_PROCESSED:
		this->setWindowTitle("Server information processed, finalizing connection...");
		break;
	case E_FINISHED:
		this->setWindowTitle("Connection established, entering lobby!");
		break;
	default:
		this->setWindowTitle("Unknown connection state!");
		break;
	};

	if(!tryingToConnect)
		return;

	progressBarConnection->setValue(progressBarConnection->value() + 1);
	QTimer::singleShot(1000, this, SLOT(onUpdateProgress()));
}