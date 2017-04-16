/********************************************************************************
** Form generated from reading UI file 'jrtest12.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JRTEST12_H
#define UI_JRTEST12_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_jrTest12Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *jrTest12Class)
    {
        if (jrTest12Class->objectName().isEmpty())
            jrTest12Class->setObjectName(QStringLiteral("jrTest12Class"));
        jrTest12Class->resize(600, 400);
        menuBar = new QMenuBar(jrTest12Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        jrTest12Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(jrTest12Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        jrTest12Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(jrTest12Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        jrTest12Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(jrTest12Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        jrTest12Class->setStatusBar(statusBar);

        retranslateUi(jrTest12Class);

        QMetaObject::connectSlotsByName(jrTest12Class);
    } // setupUi

    void retranslateUi(QMainWindow *jrTest12Class)
    {
        jrTest12Class->setWindowTitle(QApplication::translate("jrTest12Class", "jrTest12", 0));
    } // retranslateUi

};

namespace Ui {
    class jrTest12Class: public Ui_jrTest12Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JRTEST12_H
