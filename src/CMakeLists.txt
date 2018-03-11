set(SRCS
    aboutdialog.cpp
    countdowntimer.cpp
    darkStyle.cpp
    main.cpp
    mainwindow.cpp
    settingswidget.cpp)
if(WIN32)
    list(APPEND SRCS 
        alarmdialog.cpp
        idletimer.cpp)
endif(WIN32)

set(UI_HEADERS 
    aboutdialog.ui
    mainwindow.ui
    settingswidget.ui)
if(WIN32)
    list(APPEND UI_HEADERS
        alarmdialog.ui)
endif(WIN32)

qt5_add_resources(QRCS 
    res/darkstyle.qrc
    res/res.qrc)

add_executable(stretch-timer ${SRCS} ${UI_HEADERS} ${QRCS})

set(LIBS Qt5::Widgets)
if(UNIX)
    list(APPEND LIBS
        Qt5::Multimedia)
endif(UNIX)
if(WIN32)
    list(APPEND LIBS
        Qt5::WinMain)
endif(WIN32)

target_link_libraries(stretch-timer ${LIBS})

