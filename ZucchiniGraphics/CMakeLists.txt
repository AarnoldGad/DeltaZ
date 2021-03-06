CMAKE_MINIMUM_REQUIRED(VERSION 3.20 FATAL_ERROR)

PROJECT(ZGraphics
        VERSION 0.7.0
        LANGUAGES C CXX
        )

SET(CMAKE_CONFIGURATION_TYPES Debug Release)

SET(ZGraphics_VERSION_STAGE "ex")
SET(ZGraphics_VERSION_DAY 05)
SET(ZGraphics_VERSION_MONTH 05)
SET(ZGraphics_VERSION_YEAR 22)

MESSAGE(STATUS "Configuring ZGraphics ${ZGraphics_VERSION_MAJOR}-${ZGraphics_VERSION_MINOR}.${ZGraphics_VERSION_PATCH}${ZGraphics_VERSION_STAGE} of ${ZGraphics_VERSION_MONTH}/${ZGraphics_VERSION_DAY}${ZGraphics_VERSION_YEAR}...")

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Freetype 2.10.0 REQUIRED)

IF(UNIX AND NOT APPLE)
   FIND_PACKAGE(X11 REQUIRED)
ENDIF()

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

SET(CMAKE_DEBUG_POSTFIX -d)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

CONFIGURE_FILE(config.hpp.in zgconfig.hpp @ONLY NEWLINE_STYLE LF)

IF(NOT TARGET zucchini)
   ADD_SUBDIRECTORY(ZucchiniLib)
ENDIF()

ADD_SUBDIRECTORY(ZGraphics/deps/glfw)
ADD_SUBDIRECTORY(ZGraphics)

