ADD_LIBRARY(zgraphics)

IF(WIN32)
   SET(BUILD_SHARED_LIBS OFF)
ELSE()
   SET(BUILD_SHARED_LIBS ON)
ENDIF()

# Properties
SET_TARGET_PROPERTIES(zgraphics PROPERTIES
                      OUTPUT_NAME zgraphics
                      VERSION ${ZGraphics_VERSION_MAJOR}.${ZGraphics_VERSION_MINOR}.${ZGraphics_VERSION_PATCH}
                      SOVERSION ${ZGraphics_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON
                      CXX_EXTENSIONS OFF
                      FOLDER "ZGraphics"
                      )

SET(IMPL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/impl")
SET(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(HPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/zgraphics")
SET(CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
SET(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps")

# Precompiled Header
TARGET_PRECOMPILE_HEADERS(zgraphics PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:zgpch.hpp>")

# Defines
TARGET_COMPILE_DEFINITIONS(zgraphics PRIVATE
                           $<$<CONFIG:Debug>:_DEBUG>
                           $<$<CONFIG:Release>:NDEBUG>
                           )

# Public Include Dirs
TARGET_INCLUDE_DIRECTORIES(zgraphics PUBLIC
                           "${INCLUDE_DIR}"
                           "${DEPS_DIR}/glad/include"
                           "${PROJECT_BINARY_DIR}"
                           )

# Private Include Dirs
TARGET_INCLUDE_DIRECTORIES(zgraphics PRIVATE
                           "${IMPL_DIR}"

                           "${DEPS_DIR}/glfw/include"
                           "${DEPS_DIR}/stb/include"
                           ${FREETYPE_INCLUDE_DIR_freetype2}
                           )

# System Include Dirs
TARGET_INCLUDE_DIRECTORIES(zgraphics SYSTEM PRIVATE
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/include>
                           $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/include>
                           )

TARGET_SOURCES(zgraphics PRIVATE
               ${INCLUDE_DIR}/zgpch.hpp
               ${HPP_DIR}/defines.hpp
               ${HPP_DIR}/platform.hpp
               ${HPP_DIR}/zgraphics.hpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Camera/Camera.hpp
               ${HPP_DIR}/Camera/Camera.inl
               ${HPP_DIR}/Camera/OrthographicCamera.hpp
               ${HPP_DIR}/Camera/OrthographicCamera.inl

               ${CPP_DIR}/Camera/Camera.cpp
               ${CPP_DIR}/Camera/OrthographicCamera.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Common/Colors.hpp
               ${HPP_DIR}/Common/Context.hpp
               ${HPP_DIR}/Common/Image.hpp
               ${HPP_DIR}/Common/Image.inl

               ${CPP_DIR}/Common/Context.cpp
               ${CPP_DIR}/Common/Image.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Input/Event/KeyEvents.hpp
               ${HPP_DIR}/Input/Event/KeyEvents.inl
               ${HPP_DIR}/Input/Event/MouseEvents.hpp
               ${HPP_DIR}/Input/Event/MouseEvents.inl

               ${HPP_DIR}/Input/Keyboard.hpp
               ${HPP_DIR}/Input/Mouse.hpp

               ${CPP_DIR}/Input/Event/KeyEvents.cpp
               ${CPP_DIR}/Input/Event/MouseEvents.cpp

               ${CPP_DIR}/Input/Keyboard.cpp
               ${CPP_DIR}/Input/Mouse.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Renderer/Buffers/Buffer.hpp
               ${HPP_DIR}/Renderer/Buffers/Buffer.inl
               ${HPP_DIR}/Renderer/Buffers/IndexBuffer.hpp
               ${HPP_DIR}/Renderer/Buffers/IndexBuffer.inl
               ${HPP_DIR}/Renderer/Buffers/VertexArray.hpp
               ${HPP_DIR}/Renderer/Buffers/VertexArray.inl
               ${HPP_DIR}/Renderer/Buffers/VertexBuffer.hpp
               ${HPP_DIR}/Renderer/Buffers/VertexLayout.hpp
               ${HPP_DIR}/Renderer/Buffers/VertexLayout.inl

               ${HPP_DIR}/Renderer/DefaultRenderer.hpp
               ${HPP_DIR}/Renderer/Mesh.hpp
               ${HPP_DIR}/Renderer/TexturedMesh.hpp
               ${HPP_DIR}/Renderer/Shader.hpp
               ${HPP_DIR}/Renderer/Shader.inl
               ${HPP_DIR}/Renderer/Texture.hpp
               ${HPP_DIR}/Renderer/Texture.inl
               ${HPP_DIR}/Renderer/Sprite.hpp
               ${HPP_DIR}/Renderer/Sprite.inl
               ${HPP_DIR}/Renderer/Transform.hpp
               ${HPP_DIR}/Renderer/Transform.inl
               ${HPP_DIR}/Renderer/Vertex.hpp
               ${HPP_DIR}/Renderer/Vertex2D.hpp
               ${HPP_DIR}/Renderer/Vertex2D.inl
               ${HPP_DIR}/Renderer/ViewProjection.hpp

               ${CPP_DIR}/Renderer/Buffers/Buffer.cpp
               ${CPP_DIR}/Renderer/Buffers/IndexBuffer.cpp
               ${CPP_DIR}/Renderer/Buffers/VertexArray.cpp
               ${CPP_DIR}/Renderer/Buffers/VertexBuffer.cpp
               ${CPP_DIR}/Renderer/Buffers/VertexLayout.cpp

               ${CPP_DIR}/Renderer/DefaultRenderer.cpp
               ${CPP_DIR}/Renderer/Shader.cpp
               ${CPP_DIR}/Renderer/Texture.cpp
               ${CPP_DIR}/Renderer/Sprite.cpp
               ${CPP_DIR}/Renderer/Transform.cpp
               ${CPP_DIR}/Renderer/Vertex2D.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Text/Font.hpp
               ${HPP_DIR}/Text/Font.inl
               ${HPP_DIR}/Text/Glyph.hpp
               ${HPP_DIR}/Text/Glyph.inl
               ${HPP_DIR}/Text/Encoding.hpp
               
               ${CPP_DIR}/Text/Font.cpp
               ${CPP_DIR}/Text/Glyph.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${HPP_DIR}/Window/Event/FrameBufferResisedEvent.hpp
               ${HPP_DIR}/Window/Event/FrameBufferResisedEvent.inl
               ${HPP_DIR}/Window/Event/WindowEvents.hpp
               ${HPP_DIR}/Window/Event/WindowEvents.inl

               ${HPP_DIR}/Window/Window.hpp
               ${HPP_DIR}/Window/ContextSettings.hpp
               ${HPP_DIR}/Window/WindowSettings.hpp
               ${HPP_DIR}/Window/FrameBufferSettings.hpp

               ${CPP_DIR}/Window/Event/FrameBufferResisedEvent.cpp
               ${CPP_DIR}/Window/Event/WindowEvents.cpp

               ${CPP_DIR}/Window/Window.cpp
               )

TARGET_SOURCES(zgraphics PRIVATE
               ${IMPL_DIR}/detail/Common/ContextImpl.hpp
               ${IMPL_DIR}/detail/Input/KeyboardImpl.hpp
               ${IMPL_DIR}/detail/Input/MouseImpl.hpp
               ${IMPL_DIR}/detail/Window/WindowImpl.hpp
               ${IMPL_DIR}/detail/Window/WindowImpl.inl

               ${IMPL_DIR}/detail/Common/ContextImpl.cpp
               ${IMPL_DIR}/detail/Input/KeyboardImpl.cpp
               ${IMPL_DIR}/detail/Input/MouseImpl.cpp
               ${IMPL_DIR}/detail/Window/WindowImpl.cpp
               )

# Dependencies
TARGET_SOURCES(zgraphics PRIVATE
               ${DEPS_DIR}/glad/src/glad.c
               ${DEPS_DIR}/stb/src/stb_image.c
               )

# System Lib Dirs
TARGET_LINK_DIRECTORIES(zgraphics PRIVATE
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/lib>
                        $<$<PLATFORM_ID:Linux,Darwin>:/usr/local/lib>
                        )

# Linking
TARGET_LINK_LIBRARIES(zgraphics PRIVATE
                      zucchini
                      glfw
                      Freetype::Freetype

                      $<$<PLATFORM_ID:Linux>:X11::X11>
                      OpenGL::GL

                      "$<$<PLATFORM_ID:Darwin>:-framework Cocoa>"
                      "$<$<PLATFORM_ID:Darwin>:-framework IOKit>"
   
                      Threads::Threads
                      ${CMAKE_DL_LIBS}
                      )

