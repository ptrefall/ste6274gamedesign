#include "Options.h"
#include "MainMenu.h"

Options::Options(MainMenu *menu, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(optCancelButton, SIGNAL(clicked()), SLOT(onClose()));
}
Options::~Options()
{
}

void Options::onClose()
{
	this->hide();
	menu->show();
}
