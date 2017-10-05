#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T18:55:38
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StretchTimer
TEMPLATE = app

win32:LIBS += -luser32

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    countdowntimer.cpp \
    settingswidget.cpp \
    aboutdialog.cpp
win32:SOURCES += \
    idletimer.cpp \
    alarmdialog.cpp

HEADERS  += \
    mainwindow.h \
    version.h \
    countdowntimer.h \
    settingswidget.h \
    aboutdialog.h \
    common.h
win32:HEADERS += \
    idletimer.h \
    alarmdialog.h \

FORMS += \
    mainwindow.ui \
    settingswidget.ui \
    aboutdialog.ui
win32:FORMS += \
    alarmdialog.ui

RC_ICONS = resources/icon.ico

RESOURCES += \
    res.qrc
