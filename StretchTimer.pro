#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T18:55:38
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StretchTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    countdowntimer.cpp \
    settingswidget.cpp

HEADERS  += mainwindow.h \
    version.h \
    countdowntimer.h \
    settingswidget.h

FORMS    += mainwindow.ui \
    settingswidget.ui

RC_ICONS = resources/icon.ico

RESOURCES += \
    res.qrc
