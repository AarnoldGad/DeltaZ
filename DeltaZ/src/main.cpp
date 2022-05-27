#include <iostream>

#include "dz/Program.hpp"

#include "dz/Graphics/ResultApp.hpp"
#include "dz/Solver/LaplaceSolver.hpp"

ze::EventBus* GetEventBus()
{
   static ze::EventBus bus;
   return &bus;
}

int main(int argc, char* argv[])
{
   Program::Configure(argc, argv);

   // Load Geometry : File extension "dzg" for "DeltaZ Geometry"
   LaplaceSolver solver;
   solver.load(GeometryFile("geometries/square.dzg"));

   // generate grid from geometry
   solver.generateGrid();

   // Solve equation
   solver.solve();
   Results results = solver.getResults();

   // Show results
   ResultApp resultInterface;
   resultInterface.show(results);

   return 0;
}
