#pragma once

#include <qobject.h>
#include <QTcpSocket.h>

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

public slots:
	void connect(const QString &address, int);
	void sendTestPkgToServer();

private:
	QTcpSocket *socket;
	unsigned int request_id;

private slots:
	void serverRequest();
};
