#include "ConnectionFailed.h"
#include "Join.h"
#include <QTimer.h>

ConnectionFailed::ConnectionFailed(Join *join, Game &/*game*/, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), join(join)
{
    setupUi(this);
	connect(okButton, SIGNAL(clicked()), SLOT(onClose()));
}
ConnectionFailed::~ConnectionFailed()
{
}

void ConnectionFailed::onClose()
{
	this->hide();
	join->show();
}
