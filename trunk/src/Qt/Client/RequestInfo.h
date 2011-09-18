#pragma once

#include <QtGlobal>

class RequestInfo
{
public:
	RequestInfo() : client_id(0), request_id(0) {}
	RequestInfo(const quint32 &client_id, const quint32 &request_id) : client_id(client_id), request_id(request_id) {}

	quint32 getClientId() const { return client_id; }
	quint32 getRequestId() const { return request_id; }

private:
	quint32   client_id;
	quint32   request_id;
};
