#include "MainMenu.h"

MainMenu::MainMenu(QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);
}
MainMenu::~MainMenu()
{
}
