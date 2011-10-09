#pragma once

#include <Protocol/gameprotocol.h>
#include <QtGui/QDialog.h>
#include <ui_login.h>


class Game;

namespace Ui
{

class Login : public QDialog, public Ui::LogInDialog
{
Q_OBJECT
public:
    Login(Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Login();

	void setData(const gp_default_server_query_answer &data);

signals:
	void signLoginToGame();
private slots:
	void onLogin();

private:
	Game &game;
};
}
