#include "BuildPkgTask.h"

#include "SendPkgTask.h"
#include "../DebugUtils.h"


BuildPkgTask::BuildPkgTask()
	: rinfo_ok(false), load_ok(false)
{
}

void BuildPkgTask::buildAndQueue()
{
	//qDebug() << "BuildPkgTask::buildAndQueue()";

	DebugUtils::echoBlock(block);

	emit signDataPkgBuilt(DataPacket(getClientID(), block));
	//qDebug() << "BuildPkgTask::buildAndQueue() END";
}

gp_header BuildPkgTask::generateHeader(const quint8 &type, const bool &answer, const quint32 &request_id)
{
	gp_header header;
	header.type = type;
	header.size = sizeof(gp_header) - sizeof(gp_header_prefix);
	header.flags.answer = answer;
	header.request_id = request_id;

	return header;
}

void BuildPkgTask::initReplyPkg(const quint8 &type)
{
	clearDataBlock();
	loadDefaultHeaderOptions(type);

	header.flags.answer = true;

	addToBlock<gp_header>(header);
}

void BuildPkgTask::initRequestPkg(const quint8 &type)
{
	clearDataBlock();
	loadDefaultHeaderOptions(type);

	header.flags.answer = false;

	addToBlock<gp_header>(header);
}

void BuildPkgTask::loadDefaultHeaderOptions(const quint8 &type)
{
	header.type = type;
	header.size = sizeof(gp_header) - sizeof(gp_header_prefix);
}

void BuildPkgTask::set(const RequestInfo &rinfo)
{
	this->rinfo = rinfo;
	header.request_id = this->rinfo.getRequestId();

	rinfo_ok = true;
}

void BuildPkgTask::setLoadOK()
{
	load_ok = true;
}
