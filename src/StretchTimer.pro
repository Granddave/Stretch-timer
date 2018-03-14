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
    aboutdialog.cpp \
    darkstyle.cpp
win32:SOURCES += \
    idletimer.cpp \
    alarmdialog.cpp

HEADERS  += \
    mainwindow.h \
    version.h \
    countdowntimer.h \
    settingswidget.h \
    aboutdialog.h \
    common.h \
    darkstyle.h
win32:HEADERS += \
    idletimer.h \
    alarmdialog.h \

FORMS += \
    mainwindow.ui \
    settingswidget.ui \
    aboutdialog.ui
win32:FORMS += \
    alarmdialog.ui

RC_ICONS = res/icon.ico

RESOURCES += \
    res/res.qrc \
    res/darkstyle.qrc
