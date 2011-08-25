#include "MainMenu.h"
#include "Join.h"
#include "Options.h"
#include "Exit.h"

#include <QGraphicsScene>

MainMenu::MainMenu(QGraphicsScene *scene, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), join(0x0), options(0x0), exit(0x0)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	join = new Join(this);
	scene->addWidget(join);
	join->hide();
	options = new Options(this);
	scene->addWidget(options);
	options->hide();
	exit = new Exit(this);
	scene->addWidget(exit);
	exit->hide();

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
