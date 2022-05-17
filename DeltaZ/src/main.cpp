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
      font.loadFile(zg::FontFile("assets/fonts/Arial.ttf"), 48);

      using namespace ze::literals;
      zg::OrthographicCamera camera({ 800.f, 600.f }, { 0.f, 0.f });
      zg::Shader shader;
      zg::DefaultRenderer renderer;
      zg::Sprite sprite({ 1.f, 1.f });
      auto glyph = font.getGlyph(0xE9);
      sprite.setTexture(glyph.getTexture());
      sprite.setTextureRect(glyph.getRect());
      sprite.setPosition({ 0.f, 0.f, 0.f });
      sprite.setSize({ 300.f, 300.f });
      sprite.setOrigin({ 150.f, 150.f, 0.f });
      
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
