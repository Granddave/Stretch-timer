QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stretch-timer 
TEMPLATE = app


CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
else {
    DESTDIR = build/release
}

#DEFINES += QT_NO_DEBUG_OUTPUT=1
OBJECTS_DIR = $${DESTDIR}
MOC_DIR = $${DESTDIR}
RCC_DIR = $${DESTDIR}
UI_DIR = $${DESTDIR}


win32:LIBS += -luser32
linux:LIBS += -lX11 -lXext -lXss

SOURCES += \
    src/main.cpp\
    src/mainwindow.cpp \
    src/countdowntimer.cpp \
    src/settingswidget.cpp \
    src/aboutdialog.cpp \
    src/darkstyle.cpp
win32|linux {
    SOURCES += \
        src/idletimer.cpp \
        src/alarmdialog.cpp
}

HEADERS  += \
    src/mainwindow.h \
    src/version.h \
    src/countdowntimer.h \
    src/settingswidget.h \
    src/aboutdialog.h \
    src/common.h \
    src/darkstyle.h
win32|linux {
    HEADERS += \
        src/idletimer.h \
        src/alarmdialog.h \
}

FORMS += \
    src/mainwindow.ui \
    src/settingswidget.ui \
    src/aboutdialog.ui
win32|linux {
    FORMS += \
        src/alarmdialog.ui
}

RC_ICONS = src/res/icon.ico

RESOURCES += \
    src/res/res.qrc \
    src/res/darkstyle.qrc
