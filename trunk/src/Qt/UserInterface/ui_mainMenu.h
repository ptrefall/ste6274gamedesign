/********************************************************************************
** Form generated from reading UI file 'mainMenu.ui'
**
** Created: Wed 24. Aug 12:14:10 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *joinButton;
    QPushButton *optionsButton;
    QPushButton *exitButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 300);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(120, 40, 160, 181));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(verticalLayoutWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        joinButton = new QPushButton(verticalLayoutWidget);
        joinButton->setObjectName(QString::fromUtf8("joinButton"));

        verticalLayout->addWidget(joinButton);

        optionsButton = new QPushButton(verticalLayoutWidget);
        optionsButton->setObjectName(QString::fromUtf8("optionsButton"));

        verticalLayout->addWidget(optionsButton);

        exitButton = new QPushButton(verticalLayoutWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        verticalLayout->addWidget(exitButton);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Main Menu", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("Dialog", "START", 0, QApplication::UnicodeUTF8));
        joinButton->setText(QApplication::translate("Dialog", "JOIN", 0, QApplication::UnicodeUTF8));
        optionsButton->setText(QApplication::translate("Dialog", "OPTIONS", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("Dialog", "EXIT", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
