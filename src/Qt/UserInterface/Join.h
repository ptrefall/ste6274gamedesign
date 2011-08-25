#pragma once

#include <QtGui/QDialog.h>
#include <ui_join.h>

class MainMenu;

class Join : public QDialog, public Ui::JoinDialog
{
Q_OBJECT
public:
    Join(MainMenu *menu, QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~Join();

private slots:
	void onClose();

private:
	MainMenu *menu;
};
