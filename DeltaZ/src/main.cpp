#include <iostream>

#include "dz/Program.hpp"
#include "dz/TextRenderer.hpp"
#include <glad/glad.h>

void ConfigureWindow(int major, int minor)
{
   zg::ContextSettings context;
   context.versionMajor = major;
   context.versionMinor = minor;
   context.openglProfile = zg::ContextSettings::Profile::Any;

   zg::Window::Configure({}, context, {});
}

int main(int argc, char* argv[])
{
   Program::Initialise(argc, argv);

   {
      ConfigureWindow(3, 3);
      auto window = zg::Window::Make("DeltaZ", { 800, 600 });
      window->setColor(zg::Colors::Black);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      ze::ResourceManager<zg::Shader>::AddSearchPath("assets/shaders");
      ze::ResourceManager<zg::Font>::AddSearchPath("assets/fonts");

      zg::Shader* shader = ze::ResourceManager<zg::Shader>::Load("default", "default.vs", "default.fs");
      zg::Shader* textShader = ze::ResourceManager<zg::Shader>::Load("text", "default.vs", "text.fs");
      zg::Font* font = ze::ResourceManager<zg::Font>::Load("arial", zg::FontFile("Arial.ttf"), 48);

      using namespace ze::literals;
      zg::OrthographicCamera camera({ 800.f, 600.f }, { 0.f, 0.f });
      
      zg::VertexLayout layout;
      layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
      layout.add(zg::VertexAttribute::Type::Vec4, "vColor");
      layout.add(zg::VertexAttribute::Type::Vec2, "vTexCoord");
      
      TextRenderer textRenderer;
      textRenderer.setLayout(layout);
      textRenderer.setViewProjection(&camera);
      zg::DefaultRenderer renderer;
      renderer.setLayout(layout);
      renderer.setViewProjection(&camera);
      glm::ivec2 fbSize = window->getFramebufferSize();

      while (!window->shouldClose())
      {
         window->clear();
         glViewport(0, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
         textRenderer.renderText(*textShader, *font, "Screen 1", { 0.f, 0.f, 0.f }, 1.f);
         glViewport(fbSize.x / 2, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
         textRenderer.renderText(*textShader, *font, "Screen 2", { 0.f, 0.f, 0.f }, 1.f);
         glViewport(0, 0, fbSize.x / 2, fbSize.y / 2);
         textRenderer.renderText(*textShader, *font, "Screen 3", { 0.f, 0.f, 0.f }, 1.f);
         glViewport(fbSize.x / 2, 0, fbSize.x / 2, fbSize.y / 2);
         textRenderer.renderText(*textShader, *font, "Screen 4", { 0.f, 0.f, 0.f }, 1.f);
         window->draw();
         zg::Context::PollEvents();
      }

      window.reset();
   }

   Program::Terminate();

   return 0;
}
