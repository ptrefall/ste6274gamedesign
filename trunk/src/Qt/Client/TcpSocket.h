#pragma once

#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
public:
	TcpSocket(QObject *parent = 0) : QTcpSocket(parent) {}
    void send(const QByteArray &pkg);
};
