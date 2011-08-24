#include "NetworkSession.h"

#include <QtNetwork>

NetworkSession::NetworkSession(QObject *parent)
	: QObject( parent )
{
	


	/*QNetworkConfigurationManager manager;
	
	if(manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) 
	{
		QNetworkConfiguration config = manager.defaultConfiguration();

		network_session = new QNetworkSession(config, this);
		connect(network_session, SIGNAL(opened()), this, SLOT(sessionOpened()));

		// Opening network session
		qDebug() << "Opening client network session!";
		network_session->open();
	}
	else
	{
		qDebug() << "Manager error!";
	}*/
}



void NetworkSession::sessionOpened()
{
	qDebug() << "Client network session opened!";
	emit signConnect(ip_address, 38555);
}
