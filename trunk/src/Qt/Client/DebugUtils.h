#pragma once

#include <Protocol/gameprotocol.h>

#include <QString>
#include <QDataStream>
#include <QDebug>


class DebugUtils
{
public:
	static void echoBlock(const QByteArray &block);
	static void echoHeader(const gp_header &header);
	static QString headerToString(const gp_header &header);
};
