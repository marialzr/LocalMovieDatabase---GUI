/********************************************************************************
** Form generated from reading UI file 'lmdbgui.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LMDBGUI_H
#define UI_LMDBGUI_H

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

class Ui_LMDBguiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LMDBguiClass)
    {
        if (LMDBguiClass->objectName().isEmpty())
            LMDBguiClass->setObjectName(QStringLiteral("LMDBguiClass"));
        LMDBguiClass->resize(600, 400);
        menuBar = new QMenuBar(LMDBguiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        LMDBguiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LMDBguiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LMDBguiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LMDBguiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        LMDBguiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LMDBguiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LMDBguiClass->setStatusBar(statusBar);

        retranslateUi(LMDBguiClass);

        QMetaObject::connectSlotsByName(LMDBguiClass);
    } // setupUi

    void retranslateUi(QMainWindow *LMDBguiClass)
    {
        LMDBguiClass->setWindowTitle(QApplication::translate("LMDBguiClass", "LMDBgui", 0));
    } // retranslateUi

};

namespace Ui {
    class LMDBguiClass: public Ui_LMDBguiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LMDBGUI_H
