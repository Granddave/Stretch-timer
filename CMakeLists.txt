cmake_minimum_required(VERSION 3.12)
project(StretchTimer)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
if(UNIX)
    find_package(Qt5 COMPONENTS Multimedia REQUIRED)
    find_package(X11 REQUIRED)
endif()

if (CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER_WARNINGS -Wall -Wextra -Wpedantic -Werror)
endif()
if (MSVC)
    set(COMPILER_WARNINGS /W4 /WX)
endif()

add_subdirectory(src)
