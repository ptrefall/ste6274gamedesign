#include "Connect.h"
#include "Join.h"

Connect::Connect(Join *join, Game &/*game*/, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), join(join)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(connectCancelButton, SIGNAL(clicked()), SLOT(onClose()));
	//connect(exitButton, SIGNAL(clicked()), SLOT(onExit()));
}
Connect::~Connect()
{
}

void Connect::onClose()
{
	this->hide();
	join->show();
}
