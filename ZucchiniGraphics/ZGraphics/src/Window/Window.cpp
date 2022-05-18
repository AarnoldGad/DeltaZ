#include "zgpch.hpp"

#include "zgraphics/Window/Window.hpp"
#include "zgraphics/Common/Context.hpp"

#include "detail/Window/WindowImpl.hpp"

#include <GLFW/glfw3.h>

namespace zg
{
   void Window::Configure(WindowSettings window, ContextSettings context, FrameBufferSettings framebuffer)
   {
      glfwWindowHint(GLFW_RESIZABLE, window.resisable ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_VISIBLE, window.visible ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_DECORATED, window.decorated ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_FOCUSED, window.focused ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_AUTO_ICONIFY, window.autoIconify ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_FLOATING, window.floating ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_MAXIMIZED, window.maximised ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_CENTER_CURSOR, window.centerCursor ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_FOCUS_ON_SHOW, window.focusOnShow ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_SCALE_TO_MONITOR, window.scaleToMonitor ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_DOUBLEBUFFER, window.doubleBuffering ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_REFRESH_RATE, window.refreshRate >= 0 ? window.refreshRate : GLFW_DONT_CARE);
      //glfwWindowHint(GLFW_CONTEXT_NO_ERROR,        settings.noError ? GLFW_TRUE : GLFW_FALSE);

      glfwWindowHint(GLFW_RED_BITS, framebuffer.redBits >= 0 ? framebuffer.redBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_GREEN_BITS, framebuffer.greenBits >= 0 ? framebuffer.greenBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_BLUE_BITS, framebuffer.blueBits >= 0 ? framebuffer.blueBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_ALPHA_BITS, framebuffer.alphaBits >= 0 ? framebuffer.alphaBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_DEPTH_BITS, framebuffer.depthBits >= 0 ? framebuffer.depthBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_STENCIL_BITS, framebuffer.stencilBits >= 0 ? framebuffer.stencilBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_ACCUM_RED_BITS, framebuffer.accumRedBits >= 0 ? framebuffer.accumRedBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_ACCUM_GREEN_BITS, framebuffer.accumGreenBits >= 0 ? framebuffer.accumGreenBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_ACCUM_BLUE_BITS, framebuffer.accumBlueBits >= 0 ? framebuffer.accumBlueBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, framebuffer.accumAlphaBits >= 0 ? framebuffer.accumAlphaBits : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_SRGB_CAPABLE, framebuffer.srgbCapable ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, framebuffer.transparent ? GLFW_TRUE : GLFW_FALSE);

      //glfwWindowHint(GLFW_AUX_BUFFERS, 0);

      glfwWindowHint(GLFW_CLIENT_API, context.client == ContextSettings::ClientAPI::OpenGLES ? GLFW_OPENGL_ES_API : (
                                      context.client == ContextSettings::ClientAPI::OpenGL ? GLFW_OPENGL_API : GLFW_NO_API));
      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
      glfwWindowHint(GLFW_OPENGL_PROFILE, context.openglProfile == ContextSettings::Profile::Core ? GLFW_OPENGL_CORE_PROFILE : (
                                          context.openglProfile == ContextSettings::Profile::Compatibility ? GLFW_OPENGL_COMPAT_PROFILE : GLFW_OPENGL_ANY_PROFILE));
      glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
      glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context.versionMajor);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context.versionMinor);
      glfwWindowHint(GLFW_SAMPLES, context.samples >= 0 ? context.samples : GLFW_DONT_CARE);
      glfwWindowHint(GLFW_STEREO, context.stereo ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, context.forwardCompatibility ? GLFW_TRUE : GLFW_FALSE);
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, context.debugContext ? GLFW_TRUE : GLFW_FALSE);

      //glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, settings.cocoa.retinaFrameBuffer ? GLFW_TRUE : GLFW_FALSE);
      //glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, settings.cocoa.graphicsSwitching ? GLFW_TRUE : GLFW_FALSE);
      //glfwWindowHintString(GLFW_COCOA_FRAME_NAME,   settings.cocoa.frameName.c_str());

      //glfwWindowHintString(GLFW_X11_CLASS_NAME,    settings.x11.className.c_str());
      //glfwWindowHintString(GLFW_X11_INSTANCE_NAME, settings.x11.instanceName.c_str());
   }

   // TODO Check where to put/how to name this LoadAPI thing
   // TODO Rework this Context object
   [[nodiscard]]
   std::unique_ptr<Window> Window::Make(std::string const& title, glm::ivec2 size, glm::ivec2 pos)
   {
      std::unique_ptr<Window> window(new Window(title, size, pos));
      zg::Context::LoadAPI();
      return window;
   }

   Window::Window(std::string const& title, glm::ivec2 size, glm::ivec2 pos)
      : m_impl(std::make_unique<details::WindowImpl>(this, title, size, pos)) {}

   void Window::clear()
   {
      m_impl->clear();
   }

   void Window::draw()
   {
      m_impl->draw();
   }

   void Window::show()
   {
      m_impl->show();
   }

   void Window::hide()
   {
      m_impl->hide();
   }

   void Window::close()
   {
      m_impl->close();
   }

   void Window::setEventBus(ze::EventBus* bus) noexcept
   {
      m_impl->setEventBus(bus);
   }

   ze::EventBus* Window::getEventBus() const noexcept
   {
      return m_impl->getEventBus();
   }

   void* Window::getHandle() noexcept
   {
      return m_impl->getHandle();
   }

   void Window::setTitle(std::string const& title)
   {
      m_impl->setTitle(title);
   }

   void Window::setSize(int width, int height)
   {
      m_impl->setSize(width, height);
   }

   void Window::setSize(glm::ivec2 size)
   {
      m_impl->setSize(size);
   }

   void Window::setIcon(Image const& icon)
   {
      m_impl->setIcon(icon);
   }

   void Window::setPosition(int x, int y)
   {
      m_impl->setPosition(x, y);
   }

   void Window::setPosition(glm::ivec2 pos)
   {
      m_impl->setPosition(pos);
   }

   void Window::setOpacity(float opacity)
   {
      m_impl->setOpacity(opacity);
   }

   void Window::setVisible(bool visible)
   {
      m_impl->setVisible(visible);
   }

   void Window::setColor(float r, float g, float b, float a)
   {
      m_impl->setColor(r, g, b, a);
   }

   void Window::setColor(glm::vec4 color)
   {
      m_impl->setColor(color);
   }

   std::string const& Window::getTitle() const
   {
      return m_impl->getTitle();
   }

   glm::ivec2 Window::getSize() const
   {
      return m_impl->getSize();
   }

   glm::ivec2 Window::getFramebufferSize() const
   {
      return m_impl->getFramebufferSize();
   }

   glm::ivec2 Window::getPosition() const
   {
      return m_impl->getPosition();
   }

   float Window::getOpacity() const
   {
      return m_impl->getOpacity();
   }

   glm::vec4 Window::getColor() const
   {
      return m_impl->getColor();
   }

   bool Window::isVisible() const
   {
      return m_impl->isVisible();
   }

   bool Window::shouldClose() const
   {
      return m_impl->shouldClose();
   }

   Window::~Window() = default;
}
