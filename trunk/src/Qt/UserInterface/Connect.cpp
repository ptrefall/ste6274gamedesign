#include "Connect.h"
#include "Join.h"
#include "ConnectionFailed.h"
#include <Game/game.h>
#include <Game/GameOptions.h>
#include <Qt/Client/Client.h>
#include <QTimer.h>

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
	game.getClient().connectToServer(opt.ip_addr.c_str(), opt.port);
	tryingToConnect = true;
	onUpdateProgress();
}

void Connect::onClose()
{
	tryingToConnect = false;
	progressBarConnection->setValue(0);
	this->hide();
	join->show();
}

void Connect::onHostFound()
{
}

void Connect::onConnectionSucceeded()
{
	tryingToConnect = false;
	progressBarConnection->setValue(100);

}

void Connect::onConnectionFailed(const QString &why)
{
	tryingToConnect = false;
	progressBarConnection->setValue(0);
	connectionFailed->labelConnectionFailed->setText(why);
	this->hide();
	connectionFailed->show();
}

void Connect::onUpdateProgress()
{
	if(!tryingToConnect)
		return;

	progressBarConnection->setValue(progressBarConnection->value() + 1);
	QTimer::singleShot(1000, this, SLOT(onUpdateProgress()));
}
