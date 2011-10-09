#include "Login.h"
#include <Qt/Client/Client.h>
#include <Game/Game.h>
#include <Game/GameOptions.h>

using namespace Ui;

Login::Login(Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), game(game)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	GameOptions &opt = game.getOptions();
	name_lineEdit->setText(opt.player_name.c_str());
	race_lineEdit->setText(opt.player_race.c_str());
	class_lineEdit->setText(opt.player_class.c_str());

	connect(login_button, SIGNAL(clicked()), SLOT(onLogin()));

	connect(this, SIGNAL(signLoginToGame()), &game.getClient(), SLOT(loginToGame()));
}
Login::~Login()
{
}

void Login::setData(const gp_default_server_query_answer &data)
{
	if(data.request_flags.team_list == 0)
		team_comboBox->hide();
	else
	{
		if(data.team_list.count == 0)
			team_comboBox->hide();
		else
		{
			for(unsigned int i = 0; i < data.team_list.count; i++)
			{
				team_comboBox->addItem(data.team_list.list[i].name);
			}
		}
	}
}

void Login::onLogin()
{
	//Use ip:port and try to connect to the server
	GameOptions &opt = game.getOptions();
	opt.player_name = name_lineEdit->text().toAscii().constData();
	opt.player_race = race_lineEdit->text().toAscii().constData();
	opt.player_class = class_lineEdit->text().toAscii().constData();

	//opt.port = (int)atoi(linePort->text().toAscii().constData());
	
	this->hide();
	//show game ui

	emit signLoginToGame();
}
