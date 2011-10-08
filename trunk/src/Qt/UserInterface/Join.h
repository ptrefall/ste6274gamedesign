#pragma once

#include <QtGui/QDialog.h>
#include <ui_join.h>


class Game;

namespace Ui
{

class MainMenu;
class Connect;

class Join : public QDialog, public Ui::JoinDialog
{
Q_OBJECT
public:
    Join(MainMenu *menu, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Join();

	MainMenu &getMainMenu() { return *menu; }

private slots:
	void onClose();
	void onConnect();

private:
	MainMenu *menu;
	Game &game;
	Connect *con;
};
}
