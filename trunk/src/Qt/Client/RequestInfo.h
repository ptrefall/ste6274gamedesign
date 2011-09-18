#pragma once

#include <QtGlobal>

class RequestInfo
{
public:
	RequestInfo() {}
	RequestInfo(quint32 cid, quint32 rid) : cid(cid), rid(rid) {}

	quint32 getCId() const { return cid; }
	quint32 getRId() const { return rid; }

private:
	quint32   cid;
	quint32   rid;
};
