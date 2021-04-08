cmake_minimum_required(VERSION 3.7.2)

function(gitversion)
    execute_process(COMMAND bash -c "git describe --tags | sed 's/^v//'"
        OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(VERSION ${GIT_VERSION} CACHE STRING "git version" FORCE)
    configure_file(
        "${CMAKE_SOURCE_DIR}/cmake/version.h.in"
        "${CMAKE_SOURCE_DIR}/src/version.h"
        @ONLY
    )
    message(STATUS "Git version tag: ${VERSION}")
endfunction()

