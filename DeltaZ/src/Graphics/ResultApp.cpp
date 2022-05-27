#include "dz/Graphics/ResultApp.hpp"

#include "dz/Solver/LaplaceSolver.hpp"
#include "dz/Solver/Grid.hpp"
#include "dz/Solver/Geometry.hpp"
#include "dz/Graphics/TextRenderer.hpp"
#include "dz/Graphics/NodeVertex.hpp"

#include <glad/glad.h>

ze::EventBus* GetEventBus();

void ResultApp::show(Results const& results)
{
   init();
   configureContext(3, 3);
   openWindow();

   m_layer = std::make_unique<ResultLayer>(m_window.get());
   m_layer->load(results.geometry, results.grid);

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
      ::GetEventBus()->dispatchEvents();

      ze::Sleep(ze::Milliseconds(20));
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
   m_window->setColor(zg::Colors::White);
}

ResultApp::~ResultApp() {}

