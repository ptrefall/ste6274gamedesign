#include "Exit.h"
#include "MainMenu.h"

using namespace Ui;

Exit::Exit(MainMenu *menu, Game &/*game*/, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(exitCancelButton, SIGNAL(clicked()), SLOT(onClose()));
	connect(exitButton, SIGNAL(clicked()), SLOT(onExit()));
}
Exit::~Exit()
{
}

void Exit::onClose()
{
	this->hide();
	menu->show();
}

void Exit::onExit()
{
	QApplication::quit();
}
