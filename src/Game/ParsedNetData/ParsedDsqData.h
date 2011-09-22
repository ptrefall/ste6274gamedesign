#pragma once

#include <Qt/Client/ParsedData.h>

class ParsedDsqData : public ParsedData
{
public:
	ParsedDsqData() {}
	virtual ~ParsedDsqData() {}

	static T_HashedString getStaticType() { return T_HashedString("DSQ"); }
	virtual T_HashedString getType() { return ParsedDsqData::getStaticType(); }
};
