#pragma once

#include <Qt/Client/ParsedData.h>

class ParsedJoinData : public ParsedData
{
public:
	ParsedJoinData() {}
	virtual ~ParsedJoinData() {}

	static T_HashedString getStaticType() { return T_HashedString("JOIN"); }
	virtual T_HashedString getType() { return ParsedJoinData::getStaticType(); }
};
