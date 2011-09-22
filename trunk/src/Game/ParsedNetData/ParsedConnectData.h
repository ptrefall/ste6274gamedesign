#pragma once

#include <Qt/Client/ParsedData.h>

class ParsedConnectData : public ParsedData
{
public:
	ParsedConnectData(bool connect_accepted) : connect_accepted(connect_accepted) {}
	virtual ~ParsedConnectData() {}

	static T_HashedString getStaticType() { return T_HashedString("CONNECT"); }
	virtual T_HashedString getType() { return ParsedConnectData::getStaticType(); }

	const bool &getConnectAccepted() const { return connect_accepted; }

private:
	bool connect_accepted;
};
