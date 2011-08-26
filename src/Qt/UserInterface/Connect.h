#pragma once

#include <QtGui/QDialog.h>
#include <ui_connect.h>
#include <QTime>

class Game;

namespace Ui
{

class Join;
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

	enum eConnectionState
	{
		E_INITIATE_CONNECTION = 0,
		E_HOST_FOUND,
		E_CONNECTION_SUCCEEDED,
		E_CONNECTION_FAILED,
		E_CONNECTION_ABORTED,
		E_SERVER_INFO_RECEIVED,
		E_SERVER_INFO_PROCESSED,
		E_FINISHED
	} state;
};

}
