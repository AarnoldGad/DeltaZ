#include "dz/ResultApp.hpp"

#include "dz/TextRenderer.hpp"
#include "dz/LaplaceSolver.hpp"

#include <glad/glad.h>

ResultApp::ResultApp()
   : m_shader(nullptr), m_textShader(nullptr), m_font(nullptr),
     m_camera({ 800.f, 600.f }, { 0.f, 0.f }) {}

void ResultApp::show(Result const& results)
{
   init();
   configureContext(3, 3);
   openWindow();

   loadResults(results);
   loadResources();
   configureRenderers();

   mainLoop();

   terminate();
}

void ResultApp::mainLoop()
{
   glm::ivec2 fbSize = m_window->getFramebufferSize();

   while (!m_window->shouldClose())
   {
      m_window->clear();
      glViewport(0, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
      m_textRenderer->renderText(*m_textShader, *m_font, "Screen 1", { 0.f, 0.f, 0.f }, 1.f);
      glViewport(fbSize.x / 2, fbSize.y / 2, fbSize.x / 2, fbSize.y / 2);
      m_textRenderer->renderText(*m_textShader, *m_font, "Screen 2", { 0.f, 0.f, 0.f }, 1.f);
      glViewport(0, 0, fbSize.x / 2, fbSize.y / 2);
      m_textRenderer->renderText(*m_textShader, *m_font, "Screen 3", { 0.f, 0.f, 0.f }, 1.f);
      glViewport(fbSize.x / 2, 0, fbSize.x / 2, fbSize.y / 2);
      m_textRenderer->renderText(*m_textShader, *m_font, "Screen 4", { 0.f, 0.f, 0.f }, 1.f);
      m_window->draw();
      zg::Context::PollEvents();
   }
}

void ResultApp::loadResults(Result const& results)
{

}

void ResultApp::init()
{
   zg::Context::Initialise();
   zg::Context::LoadFreetype();
}

void ResultApp::terminate()
{
   m_window.reset();
   zg::Context::Terminate();
}

void ResultApp::configureContext(int major, int minor)
{
   zg::ContextSettings context;
   context.versionMajor = major;
   context.versionMinor = minor;
   context.openglProfile = zg::ContextSettings::Profile::Any;

   zg::Window::Configure({}, context, {});
}

void ResultApp::openWindow()
{
   m_window = zg::Window::Make("DeltaZ", { 800, 600 });
   m_window->setColor(zg::Colors::Black);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ResultApp::configureRenderers()
{
   m_renderer = std::make_unique<zg::DefaultRenderer>();
   m_textRenderer = std::make_unique<TextRenderer>();

   zg::VertexLayout layout;
   layout.add(zg::VertexAttribute::Type::Vec2, "vPos");
   layout.add(zg::VertexAttribute::Type::Vec4, "vColor");
   layout.add(zg::VertexAttribute::Type::Vec2, "vTexCoord");
   
   m_textRenderer->setLayout(layout);
   m_textRenderer->setViewProjection(&m_camera);

   m_renderer->setLayout(layout);
   m_renderer->setViewProjection(&m_camera);
}

void ResultApp::loadResources()
{
   ze::ResourceManager<zg::Shader>::AddSearchPath("assets/shaders");
   ze::ResourceManager<zg::Font>::AddSearchPath("assets/fonts");

   m_shader = ze::ResourceManager<zg::Shader>::Load("default", "default.vs", "default.fs");
   m_textShader = ze::ResourceManager<zg::Shader>::Load("text", "default.vs", "text.fs");
   m_font = ze::ResourceManager<zg::Font>::Load("arial", zg::FontFile("Arial.ttf"), 48);
}

ResultApp::~ResultApp()
{

}

