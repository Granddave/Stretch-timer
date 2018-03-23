QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stretch-timer 
TEMPLATE = app

win32:LIBS += -luser32
linux:LIBS += -lX11 -lXext -lXss

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    countdowntimer.cpp \
    settingswidget.cpp \
    aboutdialog.cpp \
    darkstyle.cpp
win32|linux {
    SOURCES += \
        idletimer.cpp \
        alarmdialog.cpp
}

HEADERS  += \
    mainwindow.h \
    version.h \
    countdowntimer.h \
    settingswidget.h \
    aboutdialog.h \
    common.h \
    darkstyle.h
win32|linux {
    HEADERS += \
        idletimer.h \
        alarmdialog.h \
}

FORMS += \
    mainwindow.ui \
    settingswidget.ui \
    aboutdialog.ui
win32|linux {
    FORMS += \
        alarmdialog.ui
}

RC_ICONS = res/icon.ico

RESOURCES += \
    res/res.qrc \
    res/darkstyle.qrc
