#include "Connect.h"
#include "Join.h"
#include "ConnectionFailed.h"
#include <Game/game.h>
#include <Game/GameOptions.h>
#include <Qt/Client/Client.h>
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

	connect(&game.getClient(), SIGNAL(targetHostFound()), SLOT(onHostFound()));
	connect(&game.getClient(), SIGNAL(connectionSucceeded()), SLOT(onConnectionSucceeded()));
	connect(&game.getClient(), SIGNAL(connectionFailed(const QString &)), SLOT(onConnectionFailed(const QString &)));

	timer.start();
	state = E_INITIATE_CONNECTION;
	game.getClient().connectToServer(opt.ip_addr.c_str(), opt.port);
	tryingToConnect = true;
	onUpdateProgress();
}

void Connect::onClose()
{
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

void Connect::onConnectionSucceeded()
{
	state = E_CONNECTION_SUCCEEDED;
	tryingToConnect = false;
	progressBarConnection->setValue(100);

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
