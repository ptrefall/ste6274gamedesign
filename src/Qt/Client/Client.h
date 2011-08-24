#pragma once

#include <qobject.h>
#include <QTcpSocket.h>

class QNetworkSession;

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent = 0);
	virtual ~Client();

public slots:
	void connectToServer(const QString &address, quint16);
	void sendTestPkgToServer();

private:
	//NetworkSession *session;
	QNetworkSession *networkSession;
	QTcpSocket *socket;
	unsigned int request_id;
	QString ip_address;

private slots:
	void displayError(QAbstractSocket::SocketError socketError);
	void serverRequest();
};
