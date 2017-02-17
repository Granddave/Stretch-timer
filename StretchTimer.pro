#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T18:55:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StretchTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    alarm.cpp

HEADERS  += mainwindow.h \
    alarm.h

FORMS    += mainwindow.ui

RC_ICONS = myappico.ico

RESOURCES += \
    res.qrc
