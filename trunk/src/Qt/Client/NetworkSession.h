#pragma once

#include <QObject>

class QNetworkSession;

class NetworkSession : public QObject
{
  Q_OBJECT
public:
  explicit NetworkSession(QObject *parent = 0);

signals:
  void signConnect(const QString &address, int port);

private slots:
  void sessionOpened();

private:
  QString ip_address;
  QNetworkSession *network_session;

};