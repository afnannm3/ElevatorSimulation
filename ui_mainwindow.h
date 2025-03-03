/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *passengerSetup;
    QTextEdit *passengerSetupText;
    QGroupBox *simulationControl;
    QVBoxLayout *verticalLayout;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *continueButton;
    QPushButton *stopButton;
    QGroupBox *safetyEvents;
    QVBoxLayout *verticalLayout_2;
    QPushButton *fireButton;
    QPushButton *powerOutButton;
    QGroupBox *elevator1Controls;
    QVBoxLayout *verticalLayout_4;
    QPushButton *elevator1Help;
    QPushButton *elevator1DoorObstacle;
    QPushButton *elevator1Overload;
    QPushButton *elevator1OpenDoor;
    QPushButton *elevator1CloseDoor;
    QLabel *simulationStepLabel;
    QGroupBox *logConsole;
    QTextEdit *logText;
    QGroupBox *elevator2Controls;
    QVBoxLayout *verticalLayout_3;
    QPushButton *elevator2Help;
    QPushButton *elevator2DoorObstacle;
    QPushButton *elevator2Overload;
    QHBoxLayout *horizontalLayout;
    QPushButton *elevator2OpenDoor;
    QPushButton *elevator2CloseDoor;
    QMenuBar *menubar;
    QMenu *menuGUI;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1032, 636);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        passengerSetup = new QGroupBox(centralwidget);
        passengerSetup->setObjectName(QString::fromUtf8("passengerSetup"));
        passengerSetup->setGeometry(QRect(690, 390, 250, 150));
        passengerSetupText = new QTextEdit(passengerSetup);
        passengerSetupText->setObjectName(QString::fromUtf8("passengerSetupText"));
        passengerSetupText->setGeometry(QRect(0, 20, 256, 192));
        simulationControl = new QGroupBox(centralwidget);
        simulationControl->setObjectName(QString::fromUtf8("simulationControl"));
        simulationControl->setGeometry(QRect(690, 220, 141, 162));
        verticalLayout = new QVBoxLayout(simulationControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        startButton = new QPushButton(simulationControl);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        pauseButton = new QPushButton(simulationControl);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        verticalLayout->addWidget(pauseButton);

        continueButton = new QPushButton(simulationControl);
        continueButton->setObjectName(QString::fromUtf8("continueButton"));

        verticalLayout->addWidget(continueButton);

        stopButton = new QPushButton(simulationControl);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout->addWidget(stopButton);

        safetyEvents = new QGroupBox(centralwidget);
        safetyEvents->setObjectName(QString::fromUtf8("safetyEvents"));
        safetyEvents->setGeometry(QRect(850, 220, 151, 100));
        verticalLayout_2 = new QVBoxLayout(safetyEvents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        fireButton = new QPushButton(safetyEvents);
        fireButton->setObjectName(QString::fromUtf8("fireButton"));

        verticalLayout_2->addWidget(fireButton);

        powerOutButton = new QPushButton(safetyEvents);
        powerOutButton->setObjectName(QString::fromUtf8("powerOutButton"));

        verticalLayout_2->addWidget(powerOutButton);

        elevator1Controls = new QGroupBox(centralwidget);
        elevator1Controls->setObjectName(QString::fromUtf8("elevator1Controls"));
        elevator1Controls->setGeometry(QRect(700, 20, 125, 193));
        verticalLayout_4 = new QVBoxLayout(elevator1Controls);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        elevator1Help = new QPushButton(elevator1Controls);
        elevator1Help->setObjectName(QString::fromUtf8("elevator1Help"));

        verticalLayout_4->addWidget(elevator1Help);

        elevator1DoorObstacle = new QPushButton(elevator1Controls);
        elevator1DoorObstacle->setObjectName(QString::fromUtf8("elevator1DoorObstacle"));

        verticalLayout_4->addWidget(elevator1DoorObstacle);

        elevator1Overload = new QPushButton(elevator1Controls);
        elevator1Overload->setObjectName(QString::fromUtf8("elevator1Overload"));

        verticalLayout_4->addWidget(elevator1Overload);

        elevator1OpenDoor = new QPushButton(elevator1Controls);
        elevator1OpenDoor->setObjectName(QString::fromUtf8("elevator1OpenDoor"));

        verticalLayout_4->addWidget(elevator1OpenDoor);

        elevator1CloseDoor = new QPushButton(elevator1Controls);
        elevator1CloseDoor->setObjectName(QString::fromUtf8("elevator1CloseDoor"));

        verticalLayout_4->addWidget(elevator1CloseDoor);

        simulationStepLabel = new QLabel(centralwidget);
        simulationStepLabel->setObjectName(QString::fromUtf8("simulationStepLabel"));
        simulationStepLabel->setGeometry(QRect(840, 370, 200, 30));
        logConsole = new QGroupBox(centralwidget);
        logConsole->setObjectName(QString::fromUtf8("logConsole"));
        logConsole->setGeometry(QRect(10, 10, 541, 591));
        logText = new QTextEdit(logConsole);
        logText->setObjectName(QString::fromUtf8("logText"));
        logText->setGeometry(QRect(0, 20, 541, 561));
        elevator2Controls = new QGroupBox(centralwidget);
        elevator2Controls->setObjectName(QString::fromUtf8("elevator2Controls"));
        elevator2Controls->setGeometry(QRect(850, 20, 125, 193));
        verticalLayout_3 = new QVBoxLayout(elevator2Controls);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        elevator2Help = new QPushButton(elevator2Controls);
        elevator2Help->setObjectName(QString::fromUtf8("elevator2Help"));

        verticalLayout_3->addWidget(elevator2Help);

        elevator2DoorObstacle = new QPushButton(elevator2Controls);
        elevator2DoorObstacle->setObjectName(QString::fromUtf8("elevator2DoorObstacle"));

        verticalLayout_3->addWidget(elevator2DoorObstacle);

        elevator2Overload = new QPushButton(elevator2Controls);
        elevator2Overload->setObjectName(QString::fromUtf8("elevator2Overload"));

        verticalLayout_3->addWidget(elevator2Overload);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        verticalLayout_3->addLayout(horizontalLayout);

        elevator2OpenDoor = new QPushButton(elevator2Controls);
        elevator2OpenDoor->setObjectName(QString::fromUtf8("elevator2OpenDoor"));

        verticalLayout_3->addWidget(elevator2OpenDoor);

        elevator2CloseDoor = new QPushButton(elevator2Controls);
        elevator2CloseDoor->setObjectName(QString::fromUtf8("elevator2CloseDoor"));

        verticalLayout_3->addWidget(elevator2CloseDoor);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1032, 22));
        menuGUI = new QMenu(menubar);
        menuGUI->setObjectName(QString::fromUtf8("menuGUI"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuGUI->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Elevator System Simulation", nullptr));
        passengerSetup->setTitle(QCoreApplication::translate("MainWindow", "Passenger Setup", nullptr));
        simulationControl->setTitle(QCoreApplication::translate("MainWindow", "Simulation Control", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        continueButton->setText(QCoreApplication::translate("MainWindow", "Continue", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        safetyEvents->setTitle(QCoreApplication::translate("MainWindow", "Building Safety Events", nullptr));
        fireButton->setText(QCoreApplication::translate("MainWindow", "Fire", nullptr));
        powerOutButton->setText(QCoreApplication::translate("MainWindow", "Power Out", nullptr));
        elevator1Controls->setTitle(QCoreApplication::translate("MainWindow", "Elevator 1", nullptr));
        elevator1Help->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        elevator1DoorObstacle->setText(QCoreApplication::translate("MainWindow", "Door Obstacle", nullptr));
        elevator1Overload->setText(QCoreApplication::translate("MainWindow", "Overload", nullptr));
        elevator1OpenDoor->setText(QCoreApplication::translate("MainWindow", "Open Door", nullptr));
        elevator1CloseDoor->setText(QCoreApplication::translate("MainWindow", "Close Door", nullptr));
        simulationStepLabel->setText(QCoreApplication::translate("MainWindow", "Simulation Step: 0", nullptr));
        logConsole->setTitle(QCoreApplication::translate("MainWindow", "Log Console", nullptr));
        elevator2Controls->setTitle(QCoreApplication::translate("MainWindow", "Elevator 2", nullptr));
        elevator2Help->setText(QCoreApplication::translate("MainWindow", "Help", nullptr));
        elevator2DoorObstacle->setText(QCoreApplication::translate("MainWindow", "Door Obstacle", nullptr));
        elevator2Overload->setText(QCoreApplication::translate("MainWindow", "Overload", nullptr));
        elevator2OpenDoor->setText(QCoreApplication::translate("MainWindow", "Open Door", nullptr));
        elevator2CloseDoor->setText(QCoreApplication::translate("MainWindow", "Close Door", nullptr));
        menuGUI->setTitle(QCoreApplication::translate("MainWindow", "GUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
