#include "Lobby.h"
#include "MainMenu.h"
#include "Connect.h"
#include "Login.h"
#include <Game/Game.h>
#include <Game/GameOptions.h>
#include <QStandardItemModel.h>

using namespace Ui;

Lobby::Lobby(MainMenu *menu, Game &game, QWidget *parent, Qt::WFlags flags)
: QDialog(parent, flags), menu(menu), game(game)
{
    setupUi(this);

	QPalette palette = this->palette();
	palette.setColor(QPalette::Window, QColor(0,0,0,0));
	this->setPalette(palette);

	//connect(this, SIGNAL(close()), SLOT(onClose()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(onClose()));
	connect(enterGameButton, SIGNAL(clicked()), SLOT(onEnterGame()));
	connect(chatButton, SIGNAL(clicked()), SLOT(onChatPost()));
	//enterGameButton->setEnabled(false);
}
Lobby::~Lobby()
{
}

void Lobby::setData(const gp_default_server_query_answer &data)
{
	if(data.request_flags.map_info)
	{
		mapTitleLabel->setText(data.map_info.name);
		QString info = QString("Author: %0\nVersion: %1\nURL: %2").arg(data.map_info.author).arg(data.map_info.version).arg(data.map_info.url);
		mapinfoLabel->setText(info);
	}
	if(data.request_flags.player_list)
	{
		QStandardItemModel *model = new QStandardItemModel(data.player_list.count, 3);
		playerTableView->setModel(model);
		const gp_player_info_t &info_t = data.player_list.info_fields;
		
		for(gp_uint32 i = 0; i < data.player_list.count; i++)
		{	
			const gp_player_info &info = data.player_list.list[i];
			QStandardItem *item = new QStandardItem(QString("%0").arg(info.name));
			model->setItem(i, 0, item);
		}
	}
	menu->getLogin().setData(data);
}

void Lobby::onClose()
{
	this->hide();
	menu->show();
}

void Lobby::onEnterGame()
{
	this->hide();
	menu->getLogin().show();
}

void Lobby::onChatPost()
{
}
