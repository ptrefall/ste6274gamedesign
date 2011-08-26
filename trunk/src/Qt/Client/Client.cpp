#include "client.h"

#include <Protocol/gameprotocol.h>
#include <QtNetwork>

Client::Client(QObject *parent)
	: QObject(parent)
{
	// Find host address
	/*QList<QHostAddress> ip_address_list = QNetworkInterface::allAddresses();
	for(int i = 0; i < ip_address_list.size(); i++)
	{
		if((ip_address_list.at(i) != QHostAddress::LocalHost) && ip_address_list.at(i).toIPv4Address())
		{
			ip_address = ip_address_list.at(i).toString();
			break;
		}
	}*/

	// If no external address were available use localhost
	if(ip_address.isEmpty())
		ip_address = QHostAddress(QHostAddress::LocalHost).toString();

	socket = new QTcpSocket(this);
//  connect( _socket, SIGNAL(readyRead()), this, SLOT(serverRequest()) );
	connect(socket, SIGNAL(connected()), this, SLOT(tcpConnectionSucceeded()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));



	request_id = 0;
}

Client::~Client()
{
  socket->abort();
  delete socket;
}

void Client::connectToServer(const QString &address, quint16 port )
{
  socket->abort();
  socket->connectToHost(address, port);
}

void Client::tcpConnectionSucceeded()
{
	emit connectionSucceeded();
}

void Client::sendTestPkgToServer()
{
  gp_header header;
  header.size = sizeof(gp_header) - sizeof(gp_header_prefix);
  header.type = GP_REQUEST_TYPE_TEST;
  header.flags.answer = 0;
  header.request_id = ++request_id;

  qDebug() << "Client: Header test data";
  qDebug() << " quint16 size:           " << sizeof(quint16);
  qDebug() << " header size:            " << sizeof(header);
  qDebug() << " gp header size:         " << sizeof(gp_header);
  qDebug() << " gp header flag size:    " << sizeof(gp_header_flags);
  qDebug() << " gp header prefix size:  " << sizeof(gp_header_prefix);
  qDebug() << " p:id:                   " << header.prefix.id;
  qDebug() << " s:                      " << header.size;
  qDebug() << " t:                      " << header.type;
  qDebug() << " a:                      " << header.flags.answer;
  qDebug() << " r:                      " << header.request_id;
  qDebug() << " ";
  qDebug() << " type is PING:           " << ( header.type == GP_REQUEST_TYPE_PING ? "yes" : "no" );
  qDebug() << " type is DEFAULT SERVER QUERY: " << ( header.type == GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY ? "yes" : "no" );
  qDebug() << " type is TEST:           " << ( header.type == GP_REQUEST_TYPE_TEST ? "yes" : "no" );
  qDebug() << " type is ERROR:          " << ( header.type == GP_REQUEST_TYPE_ERROR ? "yes" : "no" );


  QByteArray block;
  QDataStream out(&block, QIODevice::ReadWrite );
  out.setVersion( QDataStream::Qt_4_7 );

  // Reserve space for the block size information
//  out << (quint16)0;

  qDebug() << "--> block.size(1): " << block.size();

//  // Write data
  out.writeRawData( (char*)(&header), sizeof(gp_header) );

  qDebug() << "--> block.size(2): " << block.size();

  // Write the size of the expected block to the start of the block using the first 16 bits.
//  out.device()->seek(0);
//  out << (quint16)(block.size() - sizeof(quint16) );


  qDebug() << "--> block.size(3): " << block.size();



//  // TEST
//  gp_header header2;
//  out.device()->seek(0);
//  quint16 header2_blocksize;
//  out >> header2_blocksize;

//  out.readRawData( (char*)(&header2), sizeof(gp_header) );

//  qDebug() << "Client: Header test data (stream):";
//  qDebug() << " quint16 size:         " << sizeof(quint16);
//  qDebug() << " header size:          " << sizeof(header2);
//  qDebug() << " block size:           " << header2_blocksize;
//  qDebug() << " s:                    " << header2.size;
//  qDebug() << " t:                    " << header2.type;
//  qDebug() << " a:                    " << header2.flags.answer;
//  qDebug() << " r:                    " << header2.request_id;
//  qDebug() << " ";
//  qDebug() << " type is PING:         " << ( header2.type == GP_REQUEST_TYPE_PING ? "yes" : "no" );
//  qDebug() << " type is DEFAULT SERVER QUERY: " << ( header2.type == GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY ? "yes" : "no" );
//  qDebug() << " type is TEST:         " << ( header2.type == GP_REQUEST_TYPE_TEST ? "yes" : "no" );
//  qDebug() << " type is ERROR:        " << ( header2.type == GP_REQUEST_TYPE_ERROR ? "yes" : "no" );
//  // TEST END


  socket->write( block );
}

void Client::serverRequest()
{
  qDebug() << "Client: Incoming server request!";
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
		emit connectionFailed("Remote host closed");
        break;
    case QAbstractSocket::HostNotFoundError:
		emit connectionFailed("Host not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
		emit connectionFailed("Connection refused");
        break;
    default:
		emit connectionFailed("Unknown error");
		break;
    }
}
