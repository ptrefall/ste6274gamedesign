#pragma once

#include <types_config.h>
#include <QObject>

class ParsedData : public QObject
{
	Q_OBJECT
public:
	ParsedData() {}
	virtual ~ParsedData() {}

	virtual T_HashedString getType() { return T_HashedString("NOT_AVAILABLE"); };

	void emitSignal() { emit signParsedDataInvoked(this); }

signals:
	void signParsedDataInvoked(ParsedData *);
};
