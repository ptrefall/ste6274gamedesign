#pragma once

#include <QtGui/QDialog.h>
#include <Qt/UserInterface/ui_mainMenu.h>

class MainMenu : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
    MainMenu(QWidget *parent = 0, Qt::WFlags flags = 0);
    virtual ~MainMenu();
};
