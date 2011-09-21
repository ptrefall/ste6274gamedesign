#pragma once

#include "TcpParseTask.h"

class ServerParseTask : public TcpParseTask {
  Q_OBJECT

public:
	explicit ServerParseTask(TcpSocket &socket) : TcpParseTask(socket) {}

signals:
	void      signRegisterConnectAnswer(const RequestInfo &rinfo, const gp_connect_answer &answer);
	void      signRegisterDSQAnswer(const RequestInfo &rinfo, const gp_default_server_query_answer &answer);
	void      signRegisterJoinAnswer(const RequestInfo &rinfo, const gp_join_answer &answer);

protected:
  virtual bool validateHeaderType(const quint8 &type);
  virtual quint32 computeBodySize(const quint8 &type);
  virtual void handleRead(const quint8 &type, QDataStream &in);

};
