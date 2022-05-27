#ifndef RESULTAPP_HPP
#define RESULTAPP_HPP

#include "dz/Solver/LaplaceSolver.hpp"
#include "dz/Graphics/TextRenderer.hpp"
#include "dz/Graphics/ResultLayer.hpp"

#include <zgraphics/zgraphics.hpp>

class Grid;
class Geometry;

class ResultApp
{
public:
   void show(Results const& results);

   ~ResultApp();

private:
   void init();
   void terminate();

   void configureContext(int major, int minor);
   void openWindow();

   void mainLoop();

   std::unique_ptr<zg::Window> m_window;
   std::unique_ptr<ResultLayer> m_layer;
};

#endif // RESULTAPP_HPP

