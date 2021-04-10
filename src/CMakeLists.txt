cmake_minimum_required(VERSION 3.7.2)

add_executable(stretch-timer
    res/res.qrc
    aboutdialog.cpp
    aboutdialog.h
    aboutdialog.ui
    alarmdialog.cpp
    alarmdialog.h
    alarmdialog.ui
    common.h
    countdowntimer.cpp
    countdowntimer.h
    darkstyle.cpp
    darkstyle.h
    idletimer.cpp
    idletimer.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    settingswidget.cpp
    settingswidget.h
    settingswidget.ui
    version.h
)
set_target_properties(stretch-timer PROPERTIES
    AUTOMOC TRUE
    AUTORCC TRUE
    AUTOUIC TRUE
)
target_link_libraries(stretch-timer PRIVATE
    Qt5::Widgets
    $<$<PLATFORM_ID:Windows>:Qt5::WinMain> # Todo: Is this needed? Test without on Windows.
    $<$<PLATFORM_ID:Linux>:Qt5::Multimedia>
    $<$<PLATFORM_ID:Linux>:X11::Xss>
    $<$<PLATFORM_ID:Linux>:X11::X11>
)
target_include_directories(stretch-timer PRIVATE
    $<$<PLATFORM_ID:Linux>:${X11_INCLUDE_DIR}>
)
target_compile_options(stretch-timer PRIVATE
    ${COMPILER_WARNINGS}
)
set_target_properties(stretch-timer PROPERTIES
    CXX_STANDARD 17
)
set_target_properties(stretch-timer PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")

install(TARGETS stretch-timer DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(FILES res/logo.png RENAME stretch-timer.png DESTINATION "${CMAKE_INSTALL_DATADIR}/pixmaps")
configure_file("${CMAKE_SOURCE_DIR}/cmake/stretch-timer.desktop.in" "stretch-timer.desktop" @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/stretch-timer.desktop" DESTINATION "${CMAKE_INSTALL_DATADIR}/applications")
