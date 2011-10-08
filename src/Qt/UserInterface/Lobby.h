#pragma once

#include <Protocol/gameprotocol.h>
#include <QtGui/QDialog.h>
#include <ui_lobby.h>

class Game;

namespace Ui
{

class MainMenu;
class Connect;

class Lobby : public QDialog, public Ui::LobbyDialog
{
Q_OBJECT
public:
    Lobby(MainMenu *menu, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Lobby();

	void setData(const gp_default_server_query_answer &data);

private slots:
	void onClose();
	void onEnterGame();
	void onChatPost();

private:
	MainMenu *menu;
	Game &game;
};
}
