cmake_minimum_required(VERSION 2.8.12)
project(stretch-timer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, RCC & UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(${X11_INCLUDE_DIR})

find_package(Qt5 REQUIRED Core Widgets)
if(UNIX)
    find_package(Qt5 REQUIRED Multimedia)
    find_package(X11 REQUIRED)
endif(UNIX)

# Needed?
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif(WIN32)

add_subdirectory(src)
