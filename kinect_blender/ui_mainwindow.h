/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCapture;
    QAction *actionLoad_Motion;
    QAction *actionSave_Motion;
    QAction *actionExit;
    QAction *actionRun;
    QAction *actionStop;
    QAction *actionCreate;
    QAction *actionExport_to_blender;
    QAction *actionRecord;
    QAction *actionExport_to_blender_2;
    QAction *actionConnect;
    QAction *actionRun_Motion;
    QAction *actionStop_Motion;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSkeleton;
    QMenu *menuSkeleton_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(254, 118);
        actionCapture = new QAction(MainWindow);
        actionCapture->setObjectName(QStringLiteral("actionCapture"));
        actionLoad_Motion = new QAction(MainWindow);
        actionLoad_Motion->setObjectName(QStringLiteral("actionLoad_Motion"));
        actionSave_Motion = new QAction(MainWindow);
        actionSave_Motion->setObjectName(QStringLiteral("actionSave_Motion"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QStringLiteral("actionCreate"));
        actionExport_to_blender = new QAction(MainWindow);
        actionExport_to_blender->setObjectName(QStringLiteral("actionExport_to_blender"));
        actionRecord = new QAction(MainWindow);
        actionRecord->setObjectName(QStringLiteral("actionRecord"));
        actionExport_to_blender_2 = new QAction(MainWindow);
        actionExport_to_blender_2->setObjectName(QStringLiteral("actionExport_to_blender_2"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionRun_Motion = new QAction(MainWindow);
        actionRun_Motion->setObjectName(QStringLiteral("actionRun_Motion"));
        actionStop_Motion = new QAction(MainWindow);
        actionStop_Motion->setObjectName(QStringLiteral("actionStop_Motion"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 254, 27));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuSkeleton = new QMenu(menuBar);
        menuSkeleton->setObjectName(QStringLiteral("menuSkeleton"));
        menuSkeleton_2 = new QMenu(menuBar);
        menuSkeleton_2->setObjectName(QStringLiteral("menuSkeleton_2"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSkeleton->menuAction());
        menuBar->addAction(menuSkeleton_2->menuAction());
        menuFile->addAction(actionLoad_Motion);
        menuFile->addAction(actionSave_Motion);
        menuFile->addAction(actionRun_Motion);
        menuFile->addAction(actionStop_Motion);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSkeleton->addAction(actionConnect);
        menuSkeleton->addAction(actionRun);
        menuSkeleton->addAction(actionStop);
        menuSkeleton->addAction(actionRecord);
        menuSkeleton_2->addAction(actionCreate);
        menuSkeleton_2->addAction(actionExport_to_blender_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCapture->setText(QApplication::translate("MainWindow", "Capture", 0));
        actionLoad_Motion->setText(QApplication::translate("MainWindow", "Load Motion", 0));
        actionSave_Motion->setText(QApplication::translate("MainWindow", "Save Motion", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionRun->setText(QApplication::translate("MainWindow", "Run", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0));
        actionCreate->setText(QApplication::translate("MainWindow", "Create", 0));
        actionExport_to_blender->setText(QApplication::translate("MainWindow", "Export to blender", 0));
        actionRecord->setText(QApplication::translate("MainWindow", "Record", 0));
        actionExport_to_blender_2->setText(QApplication::translate("MainWindow", "Export to blender", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionRun_Motion->setText(QApplication::translate("MainWindow", "Run Motion", 0));
        actionStop_Motion->setText(QApplication::translate("MainWindow", "Stop Motion", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuSkeleton->setTitle(QApplication::translate("MainWindow", "Kinect", 0));
        menuSkeleton_2->setTitle(QApplication::translate("MainWindow", "Skeleton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
