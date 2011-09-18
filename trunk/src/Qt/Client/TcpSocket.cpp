#include "TcpSocket.h"
#include <QTcpSocket>

void TcpSocket::send(const QByteArray &pkg)
{
	int num_bytes_written = write(pkg);
	//qDebug() << "** " << num_bytes_written << " bytes of data written.";
}
