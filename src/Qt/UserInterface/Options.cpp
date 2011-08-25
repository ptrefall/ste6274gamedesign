#include "Options.h"
#include "MainMenu.h"
#include <Game/Game.h>

Options::Options(MainMenu *menu, Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu), game(game)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(optCancelButton, SIGNAL(clicked()), SLOT(onClose()));
	connect(optSaveButton, SIGNAL(clicked()), SLOT(onSave()));
}
Options::~Options()
{
}

void Options::onClose()
{
	this->hide();
	menu->show();
}

void Options::onSave()
{
	//Look at all option values, save to xml and make current...
}
