ADD_LIBRARY(zucchini)

IF(WIN32)
   SET(BUILD_SHARED_LIBS OFF)
ELSE()
   SET(BUILD_SHARED_LIBS ON)
ENDIF()

# Properties
SET_TARGET_PROPERTIES(zucchini PROPERTIES
                      OUTPUT_NAME zucchini 
                      VERSION ${ZucchiniLib_VERSION_MAJOR}.${ZucchiniLib_VERSION_MINOR}.${ZucchiniLib_VERSION_PATCH}
                      SOVERSION ${ZucchiniLib_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "ZEngine"
                      )

SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/zucchini")
SET(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

# Precompiled Header
TARGET_PRECOMPILE_HEADERS(zucchini PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:zepch.hpp>")

# Defines
TARGET_COMPILE_DEFINITIONS(zucchini PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

# Public Include Dirs
TARGET_INCLUDE_DIRECTORIES(zucchini PUBLIC
                           "${INCLUDE_DIR}"
                           "${DEPS_DIR}/fmt/include"
                           "${DEPS_DIR}/glm"
                           "${DEPS_DIR}/yaml-cpp/include"
                           "${PROJECT_BINARY_DIR}"
                           )

# Private Include Dirs
TARGET_INCLUDE_DIRECTORIES(zucchini PRIVATE
                           "${DEPS_DIR}/backward-cpp"
                           )

# System Include Dirs
TARGET_INCLUDE_DIRECTORIES(zucchini SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

TARGET_SOURCES(zucchini PRIVATE
               ${INCLUDE_DIR}/zepch.hpp
               ${HPP_DIR}/defines.hpp
               ${HPP_DIR}/platform.hpp
               ${HPP_DIR}/types.hpp
               ${HPP_DIR}/zucchini.hpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Backtrace/CallStack.hpp
               ${HPP_DIR}/Backtrace/CallStack.inl
               ${HPP_DIR}/Backtrace/StackFrame.hpp

               ${CPP_DIR}/Backtrace/CallStack.cpp
               ${CPP_DIR}/Backtrace/StackFrame.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Common/Arguments.hpp
               ${HPP_DIR}/Common/Arguments.inl
               ${HPP_DIR}/Common/Console.hpp
               ${HPP_DIR}/Common/Console.inl
               ${HPP_DIR}/Common/Functor.hpp
               ${HPP_DIR}/Common/Observer.hpp
               ${HPP_DIR}/Common/Random.hpp
               ${HPP_DIR}/Common/System.hpp

               ${CPP_DIR}/Common/Arguments.cpp
               ${CPP_DIR}/Common/Console.cpp
               ${CPP_DIR}/Common/Random.cpp
               ${CPP_DIR}/Common/System.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Debug/Assert.hpp
               ${HPP_DIR}/Debug/Assert.inl
               ${HPP_DIR}/Debug/Tee.hpp
               ${HPP_DIR}/Debug/Tee.inl
               ${HPP_DIR}/Debug/TodoBefore.hpp

               ${CPP_DIR}/Debug/Assert.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Event/Event.hpp
               ${HPP_DIR}/Event/Event.inl
               ${HPP_DIR}/Event/EventBus.hpp
               ${HPP_DIR}/Event/EventBus.inl
               ${HPP_DIR}/Event/EventDispatcher.hpp
               ${HPP_DIR}/Event/EventDispatcher.inl
               ${HPP_DIR}/Event/EventSubscriber.hpp
               ${HPP_DIR}/Event/EventSubscriber.inl

               ${CPP_DIR}/Event/Event.cpp
               ${CPP_DIR}/Event/EventBus.cpp
               ${CPP_DIR}/Event/EventDispatcher.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Log/Logger.hpp
               ${HPP_DIR}/Log/Logger.inl
               ${HPP_DIR}/Log/Writer.hpp
               ${HPP_DIR}/Log/StreamWriter.hpp
               ${HPP_DIR}/Log/StreamWriter.inl
               ${HPP_DIR}/Log/ConsoleWriter.hpp
               ${HPP_DIR}/Log/ConsoleWriter.inl
               ${HPP_DIR}/Log/FileWriter.hpp

               ${CPP_DIR}/Log/Logger.cpp
               ${CPP_DIR}/Log/ConsoleWriter.cpp
               ${CPP_DIR}/Log/StreamWriter.cpp
               ${CPP_DIR}/Log/FileWriter.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Math/Angle.hpp
               ${HPP_DIR}/Math/Angle.inl
               ${HPP_DIR}/Math/Math.hpp
               ${HPP_DIR}/Math/RangedNumeric.hpp
               ${HPP_DIR}/Math/RangedNumeric.inl

               ${CPP_DIR}/Math/Angle.cpp
               ${CPP_DIR}/Math/Math.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Memory/Allocator.hpp
               ${HPP_DIR}/Memory/New.hpp
               ${HPP_DIR}/Memory/New.inl
               ${HPP_DIR}/Memory/StandardAllocator.hpp
               ${HPP_DIR}/Memory/StandardAllocator.inl

               ${CPP_DIR}/Memory/New.cpp
               ${CPP_DIR}/Memory/StandardAllocator.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Resource/ResourceManager.hpp
               ${HPP_DIR}/Resource/ResourceManager.inl
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Signal/Signal.hpp
               ${HPP_DIR}/Signal/Signal.inl
               ${HPP_DIR}/Signal/Listener.hpp
               ${HPP_DIR}/Signal/Listener.inl
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Stream/OutputStream.hpp
               ${HPP_DIR}/Stream/FileOutputStream.hpp
               ${HPP_DIR}/Stream/FileOutputStream.inl

               ${CPP_DIR}/Stream/FileOutputStream.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Time/Time.hpp
               ${HPP_DIR}/Time/Time.inl
               ${HPP_DIR}/Time/Date.hpp
               ${HPP_DIR}/Time/Date.inl
               ${HPP_DIR}/Time/Chrono.hpp
               ${HPP_DIR}/Time/Chrono.inl

               ${CPP_DIR}/Time/Time.cpp
               ${CPP_DIR}/Time/Date.cpp
               ${CPP_DIR}/Time/Chrono.cpp
               )

TARGET_SOURCES(zucchini PRIVATE
               ${HPP_DIR}/Util/FileUtils.hpp
               ${HPP_DIR}/Util/StringUtils.hpp
               ${HPP_DIR}/Util/StringUtils.inl

               ${CPP_DIR}/Util/FileUtils.cpp
               )

# Dependencies
TARGET_SOURCES(zucchini PRIVATE
               ${DEPS_DIR}/glm/glm/detail/glm.cpp
               )

# System Lib Dirs
TARGET_LINK_DIRECTORIES(zucchini PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

# Add backward-cpp to search paths
LIST(APPEND CMAKE_PREFIX_PATH ${DEPS_DIR}/backward-cpp)
FIND_PACKAGE(Backward REQUIRED)

# Linking
TARGET_LINK_LIBRARIES(zucchini PRIVATE
                      fmt
                      Backward::Backward
                      yaml-cpp

                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      $<$<PLATFORM_ID:Windows>:version>
                      )

