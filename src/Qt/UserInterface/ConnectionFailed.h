#pragma once

#include <QtGui/QDialog.h>
#include <ui_connectionFailed.h>
#include <QTime>

class Join;
class Game;

class ConnectionFailed : public QDialog, public Ui::connectionFailedDialog
{
Q_OBJECT
public:
    ConnectionFailed(Join *join, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~ConnectionFailed();

private slots:
	void onClose();

private:
	Join *join;
};
