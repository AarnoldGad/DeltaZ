/**
 * WindowImpl.hpp
 * 23 Feb 2022
 * Gaétan "The Aarnold" Jalin
 *
 * Copyright (C) 2020-2021 Gaétan Jalin
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source distribution.
 **/
#ifndef ZG_WINDOWIMPL_HPP
#define ZG_WINDOWIMPL_HPP

#include "zgraphics/defines.hpp"

#include "zgraphics/Window/Window.hpp"
#include "zgraphics/Common/Image.hpp"
#include "zgraphics/Input/Keyboard.hpp"
#include "zgraphics/Input/Mouse.hpp"

#include <GLFW/glfw3.h>

namespace zg { namespace details
{
   class ZG_DETAIL WindowImpl
   {
   public:
      void clear();
      void draw();

      void show();
      void hide();
      void close();

      void setEventBus(ze::EventBus* bus) noexcept;
      ze::EventBus* getEventBus() const noexcept;

      std::string const& getTitle() const;
      glm::ivec2 getSize() const;
      glm::ivec2 getFramebufferSize() const;
      // Image const& getIcon() const noexcept;
      glm::ivec2 getPosition() const;
      float getOpacity() const;
      bool isVisible() const;
      bool shouldClose() const;
      glm::vec4 getColor() const;

      void setTitle(std::string const& title);
      void setSize(int width, int height);
      void setSize(glm::ivec2 size);
      void setIcon(Image const& icon);
      void setPosition(int x, int y);
      void setPosition(glm::ivec2 pos);
      void setOpacity(float opacity);
      void setVisible(bool visible);
      void setColor(float r, float g, float b, float a);
      void setColor(glm::vec4 color);

      void* getHandle() noexcept;

      WindowImpl(Window* root, std::string const& title, glm::ivec2 size, glm::ivec2 pos = Window::PositionUndefined);
      ~WindowImpl();

   private:
      void open(std::string const& title, glm::ivec2 size, glm::ivec2 pos = Window::PositionUndefined);

      static void Moved(GLFWwindow* window, int x, int y);
      static void Resised(GLFWwindow* window, int width, int height);
      static void Closed(GLFWwindow* window);
      static void Refreshed(GLFWwindow* window);
      static void Focused(GLFWwindow* window, int focused);
      static void Iconified(GLFWwindow* window, int iconified);
      static void Maximised(GLFWwindow* window, int maximised);
      static void FramebufferResised(GLFWwindow* window, int width, int height);
      static void Scaled(GLFWwindow* window, float xscale, float yscale);

      static void KeyInput(GLFWwindow* window, int key, int scancode, int type, int modifiers);
      static void TextInput(GLFWwindow* window, uint32_t codepoint);

      static void CursorPositionInput(GLFWwindow* window, double x, double y);
      static void CursorEnterInput(GLFWwindow* window, int entered);
      static void MouseButtonInput(GLFWwindow* window, int button, int type, int mods);
      static void MouseWheelInput(GLFWwindow* window, double dx, double dy);
      static void DropInput(GLFWwindow* window, int count, char const* paths[]);

      template<typename EventType, typename... Args>
      static void PushEvent(GLFWwindow* window, Args&&... args);
      template<typename EventType>
      static void PushKeyEvent(GLFWwindow* window, int key, int scancode, int modifiers);
      template<typename EventType, typename... Args>
      static void PushMouseEvent(GLFWwindow* window, Args&&... args);

      Window* m_root;
      GLFWwindow* m_handle;
      ze::EventBus* m_eventBus;

      std::string m_title;
      glm::ivec2 m_size;
      glm::ivec2 m_pos;
      glm::vec4 m_color;
   };
}}

#include "WindowImpl.inl"

#endif // ZG_WINDOWIMPL_HPP
