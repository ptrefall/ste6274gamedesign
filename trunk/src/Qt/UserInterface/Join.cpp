#include "Join.h"
#include "MainMenu.h"

Join::Join(MainMenu *menu, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(joinCancelButton, SIGNAL(clicked()), SLOT(onClose()));
}
Join::~Join()
{
}

void Join::onClose()
{
	this->hide();
	menu->show();
}
