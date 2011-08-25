#include "Exit.h"
#include "MainMenu.h"

Exit::Exit(MainMenu *menu, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(exitCancelButton, SIGNAL(clicked()), SLOT(onClose()));
}
Exit::~Exit()
{
}

void Exit::onClose()
{
	this->hide();
	menu->show();
}
