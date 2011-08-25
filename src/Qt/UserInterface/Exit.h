#pragma once

#include <QtGui/QDialog.h>
#include <ui_exit.h>

class MainMenu;

class Exit : public QDialog, public Ui::ExitDialog
{
Q_OBJECT
public:
    Exit(MainMenu *menu, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Exit();

private slots:
	void onClose();

private:
	MainMenu *menu;
};
