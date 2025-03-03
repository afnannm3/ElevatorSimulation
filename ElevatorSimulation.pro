QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui widgets
INCLUDEPATH += $$[QT_INSTALL_HEADERS]
LIBS += -L$$[QT_INSTALL_LIBS] -lQt5Core -lQt5Gui -lQt5Widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Administrator.cpp \
    AudioSystem.cpp \
    Building.cpp \
    ControlSystem.cpp \
    Display.cpp \
    Elevator.cpp \
    Floor.cpp \
    MainWindow.cpp \
    Passenger.cpp \
    SafetyEvent.cpp \
    main.cpp

HEADERS += \
    Administrator.h \
    AudioSystem.h \
    Building.h \
    ControlSystem.h \
    Display.h \
    Elevator.h \
    Floor.h \
    MainWindow.h \
    Passenger.h \
    SafetyEvent.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
