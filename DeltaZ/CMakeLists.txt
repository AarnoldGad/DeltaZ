ADD_EXECUTABLE(deltaz)

SET_TARGET_PROPERTIES(deltaz PROPERTIES
                      OUTPUT_NAME DeltaZ
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "DeltaZ"
                      )

SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/dz")
SET(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

TARGET_COMPILE_DEFINITIONS(deltaz PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

TARGET_INCLUDE_DIRECTORIES(deltaz PUBLIC
                           "${INCLUDE_DIR}"
                           "${PROJECT_BINARY_DIR}"
                           )

TARGET_INCLUDE_DIRECTORIES(deltaz SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

TARGET_SOURCES(deltaz PRIVATE
               ${CPP_DIR}/main.cpp

               ${HPP_DIR}/Program.hpp
               ${CPP_DIR}/Program.cpp
               )

TARGET_LINK_DIRECTORIES(deltaz PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

TARGET_LINK_LIBRARIES(deltaz PRIVATE
                      zucchini
                      zgraphics

                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      )

