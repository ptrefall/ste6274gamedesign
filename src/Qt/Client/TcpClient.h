#pragma once

#include "TcpSocket.h"

#include <QObject>
#include <QHostAddress>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

signals:
	void targetHostFound();
	void handshakeSucceeded();
	void handshakeFailed(const QString &);

public slots:
	void connectToHost(const QHostAddress& address = QHostAddress::LocalHost, const quint16 &port = 1234);

protected slots:
	void tcpHostFound();
	void tcpConnectionSucceeded();
	void displayError(QAbstractSocket::SocketError);
	virtual void readReady() = 0;

protected:
	virtual void onHandshakeSuccessful() {}

	TcpSocket *socket;
};
