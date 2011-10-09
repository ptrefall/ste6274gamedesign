#include "MainMenu.h"
#include "Join.h"
#include "Options.h"
#include "Exit.h"
#include "Login.h"
#include "Lobby.h"

#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

using namespace Ui;

MainMenu::MainMenu(QGraphicsScene *scene, Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), join(0x0), options(0x0), exit(0x0)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	join = new Join(this, game);
	QGraphicsProxyWidget *proxyJoin = scene->addWidget(join);
	join->hide();
	
	options = new Options(this, game);
	QGraphicsProxyWidget *proxyOptions = scene->addWidget(options);
	options->hide();
	
	exit = new Exit(this, game);
	QGraphicsProxyWidget *proxyExit = scene->addWidget(exit);
	exit->hide();

	lobby = new Lobby(this, game);
	QGraphicsProxyWidget *proxyLobby = scene->addWidget(lobby);
	lobby->hide();
	proxyLobby->setPos(10,10);

	login = new Login(game);
	QGraphicsProxyWidget *proxyLogin = scene->addWidget(login);
	login->hide();
	proxyLogin->setPos(10,10);

	connect(joinButton, SIGNAL(clicked()), SLOT(onJoinClicked()));
	connect(optionsButton, SIGNAL(clicked()), SLOT(onOptionsClicked()));
	connect(exitButton, SIGNAL(clicked()), SLOT(onExitClicked()));
}
MainMenu::~MainMenu()
{
}

void MainMenu::onJoinClicked()
{
	this->hide();
	join->show();
}
void MainMenu::onOptionsClicked()
{
	this->hide();
	options->show();
}
void MainMenu::onExitClicked()
{
	this->hide();
	exit->show();
}
