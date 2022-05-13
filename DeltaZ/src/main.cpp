#include <iostream>

#include "dz/Program.hpp"
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

      zg::Font font;
      font.loadFile("assets/fonts/RobotoMono.ttf", 48);

      using namespace ze::literals;
      zg::OrthographicCamera camera({ 2.f, 2.f }, { 1.f, 1.f });
      zg::Shader shader;
      zg::DefaultRenderer renderer;
      zg::Sprite sprite({ 1.f, 1.f });
      auto glyph = font.getGlyph(90);
      sprite.setTexture(glyph.getTexture());
      sprite.setPosition({ 1.f, 1.f, 0.f });
      
      zg::VertexLayout layout;
      layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
      layout.add(zg::VertexAttribute::Type::Vec4, "vColor");
      layout.add(zg::VertexAttribute::Type::Vec2, "vTexCoord");
      renderer.setLayout(layout);
      renderer.setViewProjection(&camera);

      shader.loadFile("assets/shaders/default.vs", "assets/shaders/text.fs");

      while (!window->shouldClose())
      {
         window->clear();
         renderer.submit(sprite, sprite.getTransformationMatrix());
         renderer.render(shader);
         window->draw();
         zg::Context::PollEvents();
      }

      window.reset();
   }

   Program::Terminate();

   return 0;
}
