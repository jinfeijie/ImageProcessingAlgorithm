/********************************************************************************
** Form generated from reading UI file 'dcmRegionGrow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCMREGIONGROW_H
#define UI_DCMREGIONGROW_H

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

class Ui_CDCMRegionGrowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CDCMRegionGrowClass)
    {
        if (CDCMRegionGrowClass->objectName().isEmpty())
            CDCMRegionGrowClass->setObjectName(QStringLiteral("CDCMRegionGrowClass"));
        CDCMRegionGrowClass->resize(600, 400);
        menuBar = new QMenuBar(CDCMRegionGrowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CDCMRegionGrowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CDCMRegionGrowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CDCMRegionGrowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CDCMRegionGrowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CDCMRegionGrowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CDCMRegionGrowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CDCMRegionGrowClass->setStatusBar(statusBar);

        retranslateUi(CDCMRegionGrowClass);

        QMetaObject::connectSlotsByName(CDCMRegionGrowClass);
    } // setupUi

    void retranslateUi(QMainWindow *CDCMRegionGrowClass)
    {
        CDCMRegionGrowClass->setWindowTitle(QApplication::translate("CDCMRegionGrowClass", "CDCMRegionGrow", 0));
    } // retranslateUi

};

namespace Ui {
    class CDCMRegionGrowClass: public Ui_CDCMRegionGrowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCMREGIONGROW_H
