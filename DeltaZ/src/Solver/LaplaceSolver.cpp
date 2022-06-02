#include "dz/Solver/LaplaceSolver.hpp"

void LaplaceSolver::load(GeometryFile const& file)
{
   m_geometry.loadFile(file);
}

void LaplaceSolver::generateGrid()
{
   if (!m_geometry) return (void) ze::Console::Trace("No Geometry loaded to generate grid !");
   m_grid.configureGridFrom(m_geometry);
}

void LaplaceSolver::solve()
{
   int iterations = 1000;
   for (int i = 0; i < iterations; ++i)
      for (auto& element : m_grid.getNodes())
      {
         Node& node = element.second;
         if (node.isBoundary()) continue;

         Node::Neighbours& neighbours = node.getNeighbours();
         int axisInvolved = 0;
         float value = 0.f;
         if (neighbours.up && neighbours.down)     value += neighbours.up->getValue()
                                                          + neighbours.down->getValue(), axisInvolved++;
         if (neighbours.left && neighbours.right)  value += neighbours.left->getValue()
                                                          + neighbours.right->getValue(), axisInvolved++;
         if (axisInvolved)
            value /= 2.f * axisInvolved;
         node.setValue(value);
      }
}

