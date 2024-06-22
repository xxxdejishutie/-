#-------------------------------------------------
#
# Project created by QtCreator 2024-06-06T09:40:45
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app

LIBS+=-lWs2_32
SOURCES += main.cpp\
        mainwindow.cpp \
    udp.cpp \
    doordialog.cpp \
    timer.cpp \
    cwarning.cpp \
    temprature.cpp

HEADERS  += mainwindow.h \
    udp.h \
    doordialog.h \
    timer.h \
    cwarning.h \
    temprature.h

FORMS    += mainwindow.ui \
    doordialog.ui \
    timer.ui \
    cwarning.ui \
    temprature.ui

RESOURCES += \
    res.qrc
