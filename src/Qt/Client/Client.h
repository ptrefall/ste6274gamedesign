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
	void targetHostFound();
	void handshakeSucceeded();
	void handshakeFailed(const QString &why);
	void connectionSucceeded();
	void connectionFailed(const QString &why);

public slots:
	void connectToServer(const QString &address, quint16);
	void sendTestPkgToServer();
	void sendConnectRequest();
	void sendDisconnectRequest();

private:
	QTcpSocket *socket;
	unsigned int request_id;
	QString ip_address;

private slots:
	void tcpHostFound();
	void tcpConnectionSucceeded();
	void displayError(QAbstractSocket::SocketError socketError);
	void serverRequest();
};
