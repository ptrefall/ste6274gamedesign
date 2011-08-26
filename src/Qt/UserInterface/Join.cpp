#include "Join.h"
#include "MainMenu.h"
#include "Connect.h"
#include <Game/Game.h>
#include <Game/GameOptions.h>

Join::Join(MainMenu *menu, Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu), game(game)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	con = new Connect(this, game);
	con->hide();

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(joinCancelButton, SIGNAL(clicked()), SLOT(onClose()));
	connect(joinConnectButton, SIGNAL(clicked()), SLOT(onConnect()));
}
Join::~Join()
{
}

void Join::onClose()
{
	this->hide();
	menu->show();
}

void Join::onConnect()
{
	//Use ip:port and try to connect to the server
	GameOptions &opt = game.getOptions();
	opt.ip_addr = lineIpAddr->text().toAscii().constData();
	opt.port = (unsigned short)atoi(linePort->text().toAscii().constData());
	
	this->hide();
	con->show();

	con->connectToServerAttempt();
}
