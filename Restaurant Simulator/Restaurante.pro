#-------------------------------------------------
#
# Project created by QtCreator 2019-09-15T22:18:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Restaurante
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        assignerform.cpp \
        assignerthread.cpp \
        cashierform.cpp \
        cashierthread.cpp \
        cheffform.cpp \
        cheffthread.cpp \
        client.cpp \
        configform.cpp \
        controller.cpp \
        diningroom.cpp \
        dishwasherform.cpp \
        dishwasherthread.cpp \
        entrythread.cpp \
        kitchenroom.cpp \
        main.cpp \
        mainwindow.cpp \
        menu.cpp \
        menuform.cpp \
        pauseform.cpp \
        queueform.cpp \
        refreshthread.cpp \
        restaurant.cpp \
        startupform.cpp \
        tableform.cpp \
        tablethread.cpp \
        waiter.cpp \
        waiterform.cpp \
        waiterthread.cpp \
        waitingform.cpp

HEADERS += \
        assignerform.h \
        assignerthread.h \
        cashierform.h \
        cashierthread.h \
        cheffform.h \
        cheffthread.h \
        client.h \
        configform.h \
        controller.h \
        diningroom.h \
        dishwasherform.h \
        dishwasherthread.h \
        entrythread.h \
        kitchenroom.h \
        mainwindow.h \
        menu.h \
        menuform.h \
        pauseform.h \
        queueform.h \
        refreshthread.h \
        restaurant.h \
        startupform.h \
        tableform.h \
        tablethread.h \
        templates.h \
        waiter.h \
        waiterform.h \
        waiterthread.h \
        waitingform.h

FORMS += \
        assignerform.ui \
        cashierform.ui \
        cheffform.ui \
        configform.ui \
        dishwasherform.ui \
        mainwindow.ui \
        menuform.ui \
        pauseform.ui \
        queueform.ui \
        startupform.ui \
        tableform.ui \
        waiterform.ui \
        waitingform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
