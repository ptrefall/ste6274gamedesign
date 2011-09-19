#include "DebugUtils.h"


void DebugUtils::echoHeader(const gp_header &header)
{
	qDebug() << "Header pkg:";
	qDebug() << headerToString( header );
}

void DebugUtils::echoBlock(const QByteArray &block)
{
	QByteArray b = block;

	qDebug() << "----------> Echo Block! START";
	QDataStream in(&b, QIODevice::ReadOnly);

	// read header
	gp_header header;
	in.readRawData( (char*)(&header), sizeof(header) );

	switch(header.type) 
	{
	case GP_REQUEST_TYPE_ERROR: 
		{
			gp_client_error_response error;
			in.readRawData( (char*)(&error), sizeof(gp_client_error_response) );
		}break;
	case GP_REQUEST_TYPE_CONNECT: 
		{
			gp_connect_request query;
			in.readRawData( (char*)(&query), sizeof(gp_connect_request) );
		}break;
	};
	qDebug() << "-- block size: " << block.size();
	DebugUtils::echoHeader(header);

	qDebug() << "----------> Echo Block END!";
}

QString DebugUtils::headerToString(const gp_header &header)
{
	QString str;

	QString type_str;
	switch( header.type )
	{
		case GP_REQUEST_TYPE_PING:                  type_str = "Ping!";                 break;
		case GP_REQUEST_TYPE_CONNECT:               type_str = "Connect/Disconnect";    break;
		case GP_REQUEST_TYPE_JOIN:                  type_str = "Join/Part";             break;
		case GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY:  type_str = "Default server query";  break;
		case GP_REQUEST_TYPE_TEST:                  type_str = "Test!";                 break;
		case GP_REQUEST_TYPE_ERROR:                 type_str = "Error!";                break;
		default:                                    type_str = "NOT VALID!!";			break;
	};

	str.append( QString( " Prefix: id - %1\n" ).arg( header.prefix.id ) );
	str.append( QString( " Size: %1\n" ).arg(header.size) );
	str.append( QString( " Type: %1 %2\n" ).arg(header.type).arg(type_str) );
	str.append( QString( " Flags: \n" ) );
	str.append( QString( "  - Answer: %1\n" ).arg( ( header.flags.answer ? "TRUE" : "FALSE" ) ) );
	str.append( QString( " Request ID: %1\n" ).arg(header.request_id) );

	return str;
}
