#ifndef RESULTAPP_HPP
#define RESULTAPP_HPP

#include "dz/TextRenderer.hpp"

#include <zgraphics/zgraphics.hpp>

class Result;

class ResultApp
{
public:
   void show(Result const& results);

   ResultApp();
   ~ResultApp();

private:
   void init();
   void terminate();

   void configureContext(int major, int minor);
   void openWindow();

   void configureRenderers();
   void loadResources();

   void loadResults(Result const& results);
   void mainLoop();

   std::unique_ptr<zg::Window> m_window;
   std::unique_ptr<zg::DefaultRenderer> m_renderer;
   std::unique_ptr<TextRenderer> m_textRenderer;

   zg::Shader* m_shader;
   zg::Shader* m_textShader;
   zg::Font* m_font;

   zg::OrthographicCamera m_camera;
};

#endif // RESULTAPP_HPP

