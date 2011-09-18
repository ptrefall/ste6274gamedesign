#include "TcpParseTask.h"

#include "TcpSocket.h"

QString TcpParseTask::debugGetHeaderRequestTypeText(quint8 request_type)
{
	QString type_str;
	switch( request_type ) 
	{
		case GP_REQUEST_TYPE_PING:                  type_str = "Ping!";                 break;
		case GP_REQUEST_TYPE_CONNECT:               type_str = "Connect/Disconnect";    break;
		case GP_REQUEST_TYPE_JOIN:                  type_str = "Join/Part";             break;
		case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:  type_str = "Default server query";  break;
		case GP_REQUEST_TYPE_TEST:                  type_str = "Test!";                 break;
		case GP_REQUEST_TYPE_ERROR:                 type_str = "Error!";                break;
		default:                                    type_str = "NOT VALID!!";
	};
	return type_str;
}

void TcpParseTask::run() 
{
	/*qDebug() << "Fetching request!";
	qDebug() << " - bytes avalable:  " << _socket->bytesAvailable();

	QDataStream in(_socket);
	in.setVersion( QDataStream::Qt_4_7 );

	// If header has not been read: fetch it
	if( !_valid_header_read ) 
	{

		// INVARIANT:
		//    unles a valid packet of some sort is located/defined by a valid header
		//    _valid header_read is not to be set, hence it will be false.

		// Reset body size
		_body_size = 0;

		// If not enough bytes to read the header is available return to fetch more
		if( _socket->bytesAvailable() < (int)sizeof(gp_header) )
			return;

		// Read header
		in.readRawData( (char*)(&_header), sizeof(gp_header) );

		// If header prefix is wrong, dismiss and return for more data
		if( _header.prefix.id != _header_template.id )
			return;

		// Disregard if marked as an answer packet
		if( _header.flags.answer ) 
		{
			emit signQueueClientError( getRequestInfo(),
									 GP_ERROR_QUERY_INVALID_RECIEVER_TYPE );
			return;
		}

		// Validate header type
		if( !validateHeaderType( _header.type ) ) 
		{

			emit signQueueClientError( getRequestInfo(), GP_ERROR_QUERY_INVALID_TYPE );

			return;
		}

		// Compute body size (Protected by INVARIANT)
		_body_size = computeBodySize( _header.type );
	}

	// DEBUG START
	if( _header.prefix.id == _header_template.id )
		qDebug() << "Header Prefix OK!!";
	else
		qDebug() << "Header Prefix NOT OK!!";

	qDebug() << "Header!";
	qDebug() << " p.r:          " << _header.prefix._reserved;
	qDebug() << " p.id:         " << _header.prefix.id;
	qDebug() << " s:            " << _header.size;
	qDebug() << " t:            " << _header.type << debugGetHeaderRequestTypeText( _header.type );
	qDebug() << " a:            " << _header.flags.answer;
	qDebug() << " r:            " << _header.request_id;

	qDebug() << "Header valid:  " << _valid_header_read << " " << ( _valid_header_read ? "yes" : "no" );
	qDebug() << "Pkg body size: " << _body_size;
	// DEBUG END

	qDebug() << " - bytes avalable2: " << _socket->bytesAvailable();
	
	// Return and wait for more data if data available is less then the required body data size
	if( _socket->bytesAvailable() < _body_size )
		return;

	// Handle request
	handleRequest( _header.type, in );

	// Reset the valid header stat so we can look for new packages
	_valid_header_read = false;

	// If buffer data available is greater or equal to the header size, look for extra packages.
	if( _socket->bytesAvailable() >= sizeof(gp_header) )
		run();*/
}
