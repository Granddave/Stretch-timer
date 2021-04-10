cmake_minimum_required(VERSION 3.7.2)

project(StretchTimer)

include(${CMAKE_SOURCE_DIR}/cmake/gitversion.cmake)
gitversion()

set(EXECUTABLE_NAME "stretch-timer")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_PACKAGE_NAME ${EXECUTABLE_NAME})
set(CPACK_PACKAGE_CONTACT "davidisaksson93@gmail.com")
set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Stretch Timer")
set(CPACK_PACKAGE_DESCRIPTION "Stretch Timer is an application that help people to stand up and stretch between their work sessions.")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5widgets5, libqt5multimedia5, libxss1")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
if(UNIX)
    include(GNUInstallDirs)
    find_package(Qt5 COMPONENTS Multimedia REQUIRED)
    find_package(X11 COMPONENTS Xss REQUIRED)
endif()

if (CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER_WARNINGS -Wall -Wextra -Wpedantic -Werror)
endif()
if (MSVC)
    set(COMPILER_WARNINGS /W4 /WX)
endif()

add_subdirectory(src)

if(UNIX)
    include(CPack)
endif()
