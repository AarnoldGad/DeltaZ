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
               ${HPP_DIR}/Program.hpp

               ${HPP_DIR}/Graphics/GeometryShape.hpp
               ${HPP_DIR}/Graphics/GeometryShape.inl
               ${HPP_DIR}/Graphics/GridShape.hpp
               ${HPP_DIR}/Graphics/GridShape.inl
               ${HPP_DIR}/Graphics/Legend.hpp
               ${HPP_DIR}/Graphics/Legend.inl
               ${HPP_DIR}/Graphics/TextRenderer.hpp
               ${HPP_DIR}/Graphics/ResultRenderer.hpp
               ${HPP_DIR}/Graphics/NodeVertex.hpp
               ${HPP_DIR}/Graphics/NodeVertex.inl
               ${HPP_DIR}/Graphics/ResultApp.hpp
               ${HPP_DIR}/Graphics/ResultLayer.hpp

               ${HPP_DIR}/Solver/Geometry.hpp
               ${HPP_DIR}/Solver/Geometry.inl
               ${HPP_DIR}/Solver/Grid.hpp
               ${HPP_DIR}/Solver/Grid.inl
               ${HPP_DIR}/Solver/LaplaceSolver.hpp
               ${HPP_DIR}/Solver/LaplaceSolver.inl
               ${HPP_DIR}/Solver/Node.hpp
               ${HPP_DIR}/Solver/Node.inl

               ${CPP_DIR}/Program.cpp
               ${CPP_DIR}/main.cpp

               ${CPP_DIR}/Graphics/GeometryShape.cpp
               ${CPP_DIR}/Graphics/GridShape.cpp
               ${CPP_DIR}/Graphics/Legend.cpp
               ${CPP_DIR}/Graphics/NodeVertex.cpp
               ${CPP_DIR}/Graphics/ResultApp.cpp
               ${CPP_DIR}/Graphics/ResultLayer.cpp
               ${CPP_DIR}/Graphics/TextRenderer.cpp
               ${CPP_DIR}/Graphics/ResultRenderer.cpp

               ${CPP_DIR}/Solver/LaplaceSolver.cpp
               ${CPP_DIR}/Solver/Grid.cpp
               ${CPP_DIR}/Solver/Node.cpp
               ${CPP_DIR}/Solver/Geometry.cpp
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

