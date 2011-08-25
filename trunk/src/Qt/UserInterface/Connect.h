#pragma once

#include <QtGui/QDialog.h>
#include <ui_connect.h>

class Join;
class Game;

class Connect : public QDialog, public Ui::ConnectDialog
{
Q_OBJECT
public:
    Connect(Join *join, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Connect();

private slots:
	void onClose();

private:
	Join *join;
};
