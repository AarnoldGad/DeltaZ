#include "dz/ResultApp.hpp"

#include "dz/TextRenderer.hpp"
#include "dz/LaplaceSolver.hpp"
#include "dz/Grid.hpp"
#include "dz/Geometry.hpp"
#include "dz/NodeVertex.hpp"

#include <glad/glad.h>

void ResultApp::show(Geometry const& geometry, Grid const& results)
{
   init();
   configureContext(3, 3);
   openWindow();
   m_window->setColor(zg::Colors::White);

   m_layer = std::make_unique<ResultLayer>(m_window.get());
   m_layer->load(geometry, results);

   mainLoop();

   terminate();
}

void ResultApp::mainLoop()
{
   glm::ivec2 fbSize = m_window->getFramebufferSize();

   while (!m_window->shouldClose())
   {
      m_window->clear();

      m_layer->render();

      m_window->draw();
      zg::Context::PollEvents();
   }
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

ResultApp::~ResultApp()
{

}

