#pragma once

#include "../RequestInfo.h"
#include "../DataPacket.h"

#include <Protocol/gameprotocol.h>

#include <QRunnable>
#include <QObject>
#include <QDataStream>

class BuildPkgTask : public QObject, public QRunnable
{
  Q_OBJECT
public:
	explicit BuildPkgTask();

	void set(const RequestInfo &rinfo);
	static gp_header generateHeader(const quint8 &type, const bool &answer, const quint32 &request_id);
	template<typename T> static void addToBlock(QByteArray &block, const T &t);

signals:
	void signDataPkgBuilt(const DataPacket &pkg);

protected:
	void buildAndQueue();
	quint32 getClientID() const { return rinfo.getClientId(); }
	void initRequestPkg(const quint8 &type);
	void initReplyPkg(const quint8 &type);
	bool isValid() const { return rinfo_ok & load_ok; }
	void setLoadOK();

	template <typename T> void addToBlock(const T &t);

private:
	gp_header header;
	QByteArray block;

	RequestInfo rinfo;

	bool rinfo_ok;
	bool load_ok;

	void clearDataBlock() { block.resize(0); }
	void loadDefaultHeaderOptions(const quint8 &type);
};

template <typename T>
void BuildPkgTask::addToBlock(const T &t)
{
  // Setup "out" stream
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_7);
  out.device()->seek(block.size());

  // Write data to block via stream
  out.writeRawData((char*)(&t), sizeof(T));
}

template <typename T>
void BuildPkgTask::addToBlock(QByteArray& block, const T &t)
{
  // Setup "out" stream
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_7);
  out.device()->seek(block.size());

  // Write data to block via stream
  out.writeRawData((char*)(&t), sizeof(T));
}
