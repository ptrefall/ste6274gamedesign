#pragma once

#include <QtGui/QDialog.h>
#include <ui_options.h>

class MainMenu;
class Game;

class Options : public QDialog, public Ui::OptionsDialog
{
Q_OBJECT
public:
    Options(MainMenu *menu, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Options();

private slots:
	void onClose();
	void onSave();

private:
	MainMenu *menu;
	Game &game;
};
