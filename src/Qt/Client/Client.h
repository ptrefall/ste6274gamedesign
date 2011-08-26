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

signals:
	void connectionSucceeded();
	void connectionFailed(const QString &why);

public slots:
	void connectToServer(const QString &address, quint16);
	void sendTestPkgToServer();

private:
	QTcpSocket *socket;
	unsigned int request_id;
	QString ip_address;

private slots:
	void tcpConnectionSucceeded();
	void displayError(QAbstractSocket::SocketError socketError);
	void serverRequest();
};
