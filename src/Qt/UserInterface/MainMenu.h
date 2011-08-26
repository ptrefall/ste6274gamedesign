#pragma once

#include <QtGui/QDialog.h>
#include <ui_mainMenu.h>

class QGraphicsScene;
class Game;

namespace Ui
{
class Join;
class Options;
class Exit;

class MainMenu : public QDialog, public Ui::MainMenuDialog
{
Q_OBJECT
public:
    MainMenu(QGraphicsScene *scene, Game &game, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~MainMenu();

private slots:
	void onJoinClicked();
	void onOptionsClicked();
	void onExitClicked();

private:
	Join *join;
	Options *options;
	Exit *exit;

};
}
