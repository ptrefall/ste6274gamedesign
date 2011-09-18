#pragma once

#include "../RequestInfo.h"
#include <Protocol/gameprotocol.h>

#include <QObject>
#include <QRunnable>

class TcpSocket;

class TcpParseTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
	explicit TcpParseTask() {}

	const quint32 &getClientId() const { return client_id; }
	RequestInfo getRequestInfo() const { return RequestInfo(getClientId(), header.request_id); }

	void setClientId(const unsigned int &client_id) { this->client_id = client_id; }
	void setSocket(TcpSocket *socket) { this->socket = socket; }

signals:
	void signQueueClientError( RequestInfo rinfo, quint16 error );

protected:
	void run();

	/* INVARIANT
	computeBodySize() and handleHeaderType() will only be called if and only if
	header type is valid, hence validateHeaderType() must return true
	*/
	virtual bool validateHeaderType( quint8 type ) = 0;
	virtual quint32 computeBodySize( quint8 type ) = 0;
	virtual void handleRequest( quint8 type, QDataStream& in ) = 0;
	/* INVARIANT END */
private:
	TcpSocket *socket;

	bool valid_header_read;
	quint32 body_size;

	gp_header header;
	gp_header_prefix header_template;

	quint32 client_id;

	QString debugGetHeaderRequestTypeText(quint8 request_type);
};
