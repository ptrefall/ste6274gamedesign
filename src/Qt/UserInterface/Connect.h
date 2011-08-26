#pragma once

#include <QtGui/QDialog.h>
#include <ui_connect.h>
#include <QTime>

class Join;
class Game;
class ConnectionFailed;

class Connect : public QDialog, public Ui::ConnectDialog
{
Q_OBJECT
public:
    Connect(Join *join, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Connect();

	void connectToServerAttempt();

private slots:
	void onClose();
	void onHostFound();
	void onConnectionSucceeded();
	void onConnectionFailed(const QString &why);
	void onUpdateProgress();

private:
	Join *join;
	Game &game;
	QTime timer;
	bool tryingToConnect;
	ConnectionFailed *connectionFailed;
};
