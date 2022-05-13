#ifndef ZGRAPHCIS_HPP
#define ZGRAPHCIS_HPP

#include <zucchini/defines.hpp>

// Common
#include <zgraphics/Common/Colors.hpp>
#include <zgraphics/Common/Context.hpp>
#include <zgraphics/Common/Image.hpp>

// Rendering
#include <zgraphics/Window/Window.hpp>
#include <zgraphics/Window/ContextSettings.hpp>
#include <zgraphics/Window/FrameBufferSettings.hpp>
#include <zgraphics/Window/WindowSettings.hpp>

// Renderer
#include <zgraphics/Renderer/Shader.hpp>
#include <zgraphics/Renderer/Texture.hpp>

#include <zgraphics/Renderer/Buffers/VertexArray.hpp>
#include <zgraphics/Renderer/Buffers/VertexBuffer.hpp>
#include <zgraphics/Renderer/Buffers/IndexBuffer.hpp>

#include <zgraphics/Renderer/Renderer.hpp>
#include <zgraphics/Renderer/DefaultRenderer.hpp>
#include <zgraphics/Renderer/Vertex.hpp>
#include <zgraphics/Renderer/Vertex2D.hpp>
#include <zgraphics/Renderer/Transform.hpp>

#include <zgraphics/Renderer/ViewProjection.hpp>
#include <zgraphics/Camera/OrthographicCamera.hpp>
#include <zgraphics/Camera/Camera.hpp>

#include <zgraphics/Renderer/Mesh.hpp>
#include <zgraphics/Renderer/TexturedMesh.hpp>
#include <zgraphics/Renderer/Sprite.hpp>

// Text
#include <zgraphics/Text/Font.hpp>
//#include <zgraphics/Text/BitmapFont.hpp>
#include <zgraphics/Text/Glyph.hpp>
#include <zgraphics/Text/Encoding.hpp>

// Input
#include <zgraphics/Input/Keyboard.hpp>
#include <zgraphics/Input/Mouse.hpp>
#include <zgraphics/Input/Joystick.hpp>

// Events
#include <zgraphics/Input/Event/KeyEvents.hpp>
#include <zgraphics/Input/Event/MouseEvents.hpp>
#include <zgraphics/Window/Event/WindowEvents.hpp>
#include <zgraphics/Window/Event/FrameBufferResisedEvent.hpp>

#endif // ZGRAPHCIS_HPP
