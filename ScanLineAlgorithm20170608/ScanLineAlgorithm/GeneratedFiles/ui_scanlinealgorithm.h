/********************************************************************************
** Form generated from reading UI file 'scanlinealgorithm.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANLINEALGORITHM_H
#define UI_SCANLINEALGORITHM_H

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

class Ui_CScanLineAlgorithmClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CScanLineAlgorithmClass)
    {
        if (CScanLineAlgorithmClass->objectName().isEmpty())
            CScanLineAlgorithmClass->setObjectName(QStringLiteral("CScanLineAlgorithmClass"));
        CScanLineAlgorithmClass->resize(600, 400);
        menuBar = new QMenuBar(CScanLineAlgorithmClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CScanLineAlgorithmClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CScanLineAlgorithmClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CScanLineAlgorithmClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CScanLineAlgorithmClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CScanLineAlgorithmClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CScanLineAlgorithmClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CScanLineAlgorithmClass->setStatusBar(statusBar);

        retranslateUi(CScanLineAlgorithmClass);

        QMetaObject::connectSlotsByName(CScanLineAlgorithmClass);
    } // setupUi

    void retranslateUi(QMainWindow *CScanLineAlgorithmClass)
    {
        CScanLineAlgorithmClass->setWindowTitle(QApplication::translate("CScanLineAlgorithmClass", "CScanLineAlgorithm", 0));
    } // retranslateUi

};

namespace Ui {
    class CScanLineAlgorithmClass: public Ui_CScanLineAlgorithmClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANLINEALGORITHM_H
