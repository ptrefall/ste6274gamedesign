#pragma once

#include "TcpSocket.h"

#include <QObject>
#include <QHostAddress>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = 0);

	virtual void connectToHost(const QHostAddress& address = QHostAddress::LocalHost, const quint16 &port = 1234);

protected:
	TcpSocket *socket;
};
