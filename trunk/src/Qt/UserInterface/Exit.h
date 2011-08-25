#pragma once

#include <QtGui/QDialog.h>
#include <ui_exit.h>

class MainMenu;
class Game;

class Exit : public QDialog, public Ui::ExitDialog
{
Q_OBJECT
public:
    Exit(MainMenu *menu, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Exit();

private slots:
	void onClose();
	void onExit();

private:
	MainMenu *menu;
};
