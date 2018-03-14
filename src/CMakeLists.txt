# Source files
set(SRCS
    aboutdialog.cpp
    countdowntimer.cpp
    darkstyle.cpp
    main.cpp
    mainwindow.cpp
    settingswidget.cpp)
if(WIN32 OR UNIX)
    list(APPEND SRCS 
        alarmdialog.cpp
        idletimer.cpp)
endif(WIN32 OR UNIX)

# Header files (non class related)
set(HEADERS
    common.h
    version.h)

# Qt UI headers
set(UI_HEADERS 
    aboutdialog.ui
    mainwindow.ui
    settingswidget.ui)
if(WIN32 OR UNIX)
    list(APPEND UI_HEADERS
        alarmdialog.ui)
endif(WIN32 OR UNIX)

# Qt resource files
qt5_add_resources(QRCS 
    res/darkstyle.qrc
    res/res.qrc)

add_executable(stretch-timer ${SRCS} ${HEADERS} ${UI_HEADERS} ${QRCS})

# Libraries
set(LIBS Qt5::Widgets)
if(UNIX)
    list(APPEND LIBS
        Qt5::Multimedia # Sound notification
        Xss Xext X11)   # User idle recognition
endif(UNIX)
if(WIN32)
    list(APPEND LIBS
        Qt5::WinMain)   # Needed? Todo: Test without on Windows
endif(WIN32)

# Link to libraries
target_link_libraries(stretch-timer ${LIBS})
