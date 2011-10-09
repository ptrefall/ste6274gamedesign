#include "ClientThread.h"
#include "Client.h"
#include "SocketParseTask.h"
#include "SocketPackTask.h"
#include <Game/Game.h>
#include <Game/GameOptions.h>
#include <QThread>
#include <QThreadPool>
#include <QMutexLocker>
#include <iostream>

ClientThread::ClientThread(Game &game, Client &client, QObject *parent)
: game(game), client(client), QObject(parent), thread_running(false), 
  connect_to_host(false), connect_to_game_host(false), is_game_port_valid(false),
  socket(NULL_PTR), game_socket(NULL_PTR), request_count(0)
{
	//setAutoDelete(false);
	//QThreadPool::globalInstance()->start(this);
	run();
}

ClientThread::~ClientThread()
{
	//stopThread();
}

void ClientThread::run()
{
	socket = new QTcpSocket();
	socketParseTask = new SocketParseTask(*this);

	connect(&client, SIGNAL(signConnectToHost(const QHostAddress&, const quint16 &)), this, SLOT(connectToHost(const QHostAddress&, const quint16 &)));
	connect(&client, SIGNAL(signLoginToGame()), this, SLOT(loginToGame()));
	connect(socket, SIGNAL(hostFound()), this, SLOT(hostFound()));
	connect(socket, SIGNAL(connected()), this, SLOT(connectionSucceeded()));
	connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
	connect(socket, SIGNAL(readyRead()), this, SLOT(readReady()));

	
	thread_running = true;
	/*while(thread_running)
	{
		//Do something cool
		if(socket->bytesAvailable() > 0)
		{
			std::cout << "Bytes available!" << std::endl;
		}
		update();
		Sleep(1);
	}*/
}

void ClientThread::connectToHost(const QHostAddress& address, const quint16 &port)
{
	//QMutexLocker scoped_lock(&threadMutex);
	this->address = address;
	this->port = port;
	connect_to_host = true;
}

void ClientThread::hostFound()
{
	emit signHostFound();
	//socket->waitForConnected(1000);
}

void ClientThread::connectionSucceeded()
{
	emit signHandshakeSucceeded();

	// Create and pack a connect request package
	gp_connect_request request;
	request.connect_flag = GP_CONNECT_FLAG_CONNECT;
	
	SocketPackTask<gp_connect_request> task = SocketPackTask<gp_connect_request>(*this, GP_REQUEST_TYPE_CONNECT, false, request, request_count);
	task.run(false);
	//socket->waitForReadyRead(1000);
}

void ClientThread::game_hostFound()
{
}

void ClientThread::game_connectionSucceeded()
{
}

void ClientThread::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
	{
    case QAbstractSocket::RemoteHostClosedError:	emit signHandshakeFailed("Remote host closed");		break;
    case QAbstractSocket::HostNotFoundError:		emit signHandshakeFailed("Host not found");			break;
    case QAbstractSocket::ConnectionRefusedError:	emit signHandshakeFailed("Connection refused");		break;
    default:										emit signHandshakeFailed("Unknown error");			break;
    };
}

void ClientThread::readReady()
{
	socketParseTask->run(*socket);
}

void ClientThread::game_readReady()
{
	socketParseTask->run(*game_socket);
}

void ClientThread::queueParsedPacket(Packet *packet, bool game_packet)
{
	//QMutexLocker scoped_lock(&threadMutex);
	if(game_packet)
		parsedGamePackets.push_back(packet);
	else
		parsedPackets.push_back(packet);
}

void ClientThread::queuePackedPacket(const QByteArray &block, bool game_packet)
{
	//QMutexLocker scoped_lock(&threadMutex);
	if(game_packet)
		packedGamePackets.push_back(block);
	else
		packedPackets.push_back(block);
}

void ClientThread::update()
{
	{
		if(thread_running == false)
			return;
	}

	//Check if we should attempt to connec to the host
	{
		//QMutexLocker scoped_lock(&threadMutex);
		if(connect_to_host)
		{
			socket->connectToHost(address, port);
			connect_to_host = false;
		}
		else if(connect_to_game_host)
		{
			game_socket->connectToHost(address, game_port);
			connect_to_game_host = false;
		}
	}

	//Handle packed packets in mutex scope
	{
		//QMutexLocker scoped_lock(&threadMutex);
		if(!packedPackets.empty())
		{
			T_Vector<QByteArray>::Type temp = packedPackets;
			packedPackets.clear();
			//scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				sendPackedPacket(temp[i], false);
		}
	}

	//Handle packed game packets in mutex scope
	{
		//QMutexLocker scoped_lock(&threadMutex);
		if(!packedGamePackets.empty())
		{
			T_Vector<QByteArray>::Type temp = packedGamePackets;
			packedGamePackets.clear();
			//scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				sendPackedPacket(temp[i], true);
		}
	}

	//Handle parsed packets in mutex scope
	{
		//QMutexLocker scoped_lock(&threadMutex);
		if(!parsedPackets.empty())
		{
			T_Vector<Packet*>::Type temp = parsedPackets;
			parsedPackets.clear();
			//scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				handleParsedPacket(temp[i]);
		}
	}

	//Handle parsed game packets in mutex scope
	{
		//QMutexLocker scoped_lock(&threadMutex);
		if(!parsedGamePackets.empty())
		{
			T_Vector<Packet*>::Type temp = parsedGamePackets;
			parsedGamePackets.clear();
			//scoped_lock.unlock();

			for(unsigned int i = 0; i < temp.size(); i++)
				handleParsedGamePacket(temp[i]);
		}
	}
}

T_Vector<Packet*>::Type ClientThread::getParsedGamePackets()
{
	/*T_Vector<Packet*>::Type temp;

	QMutexLocker scoped_lock(&threadMutex);
	if(parsedPackets.empty())
		return temp;
	temp = parsedPackets;
	parsedPackets.clear();
	scoped_lock.unlock();*/

	if(parsedGamePackets.empty())
		return parsedGamePackets;

	T_Vector<Packet*>::Type temp = parsedGamePackets;
	return temp;
}

void ClientThread::sendPackedPacket(const QByteArray &block, bool game_packet)
{
	qint64 bytes_written = 0;
	if(game_packet)
		bytes_written = game_socket->write(block);
	else
		bytes_written = socket->write(block);
	
	if(bytes_written == 0)
	{
		return;
	}
}

void ClientThread::handleParsedPacket(Packet *packet)
{
	if(packet->isConAns())
		handleConnectAnswer(packet->getConAns());
	else if(packet->isDsqAns())
		handleDsqAnswer(packet->getDsqAns());
	else if(packet->isJoinAns())
		handleJoinAnswer(packet->getJoinAns());
}

void ClientThread::handleParsedGamePacket(Packet *packet)
{
	if(packet->isVerReq())
		handleClientVerificationRequest(packet->getVerReq());
	else if(packet->isGameUpd())
		handleGameUpdate(packet->getGameUpd());
}

void ClientThread::handleConnectAnswer(const gp_connect_answer &answer)
{
	if(answer.state == GP_CONNECT_FLAG_CONNECT)
	{
		client.setClientId(answer.client_id);
		emit signConnectSucceeded();

		//Create and pack a default server query package
		gp_default_server_query request; //Use default protocol settings...
		
		SocketPackTask<gp_default_server_query> task = SocketPackTask<gp_default_server_query>(*this, GP_REQUEST_TYPE_DEFAULT_SERVER_QUERY, false, request, request_count);
		task.run(false);
	}
	else
	{

	}
}

void ClientThread::handleDsqAnswer(const gp_default_server_query_answer &answer)
{
	if(answer.request_flags.server_info)
	{
		game_port = (quint16)answer.server_info.connect_port;
		is_game_port_valid = true;
		GameOptions &opt = game.getOptions();

		if(answer.request_flags.team_list)
		{
			if(answer.team_list.count)
				opt.player_team_id = answer.team_list.list[0].id;
			else
				opt.player_team_id = 0;
		}
		else
			opt.player_team_id = 0;

		emit signMoveToLobby(answer);
	}
}

void ClientThread::handleJoinAnswer(const gp_join_answer &answer)
{
	if(answer.state == GP_JOIN_FLAG_JOIN)
	{
		client.setValidationCode(answer.validation_code);

		if(is_game_port_valid)
		{
			game_socket = new QTcpSocket();

			connect(game_socket, SIGNAL(hostFound()), this, SLOT(game_hostFound()));
			connect(game_socket, SIGNAL(connected()), this, SLOT(game_connectionSucceeded()));
			connect(game_socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
			connect(game_socket, SIGNAL(readyRead()), this, SLOT(game_readReady()));

			connect_to_game_host = true;
		}
	}
}

void ClientThread::handleClientVerificationRequest(const bool /*request*/)
{
	if(client.isIdValid() == false || client.isValidationCodeValid() == false)
		return;

	gp_client_verification_answer answer;
	answer.client_id = client.getId();
	answer.vcode = client.getValidationCode();

	SocketPackTask<gp_client_verification_answer> task = SocketPackTask<gp_client_verification_answer>(*this, GP_REQUEST_TYPE_CLIENT_VERIFICATION, true, answer, request_count);
	task.run(true);
}

void ClientThread::loginToGame()
{
	GameOptions &opt = game.getOptions();

	//Create a join request package
	gp_join_request request;
	request.client_id = client.getId();
	if(opt.player_name.size() < 64)
	{
		memcpy(request.player_name, opt.player_name.c_str(), opt.player_name.size());
		request.player_name[opt.player_name.size()] = '\0';
	}
	if(opt.player_race.size() < 32)
	{
		memcpy(request.race, opt.player_race.c_str(), opt.player_race.size());
		request.race[opt.player_race.size()] = '\0';
	}
	if(opt.player_class.size() < 32)
	{
		memcpy(request.class_, opt.player_class.c_str(), opt.player_class.size());
		request.class_[opt.player_class.size()] = '\0';
	}
	request.flags.join_flag = GP_JOIN_FLAG_JOIN;
	request.flags.client_type = GP_JOIN_CLIENT_TYPE_PLAYER;

	request.team_id = opt.player_team_id;

	SocketPackTask<gp_join_request> task = SocketPackTask<gp_join_request>(*this, GP_REQUEST_TYPE_JOIN, false, request, request_count);
	task.run(false);
}

void ClientThread::handleGameUpdate(const gp_game_update &answer)
{
	
}
