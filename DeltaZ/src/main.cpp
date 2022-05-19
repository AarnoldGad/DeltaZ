#include <iostream>

#include "dz/Program.hpp"
#include "dz/LaplaceSolver.hpp"
#include "dz/ResultApp.hpp"

#include <glad/glad.h>

int main(int argc, char* argv[])
{
   Program::Configure(argc, argv);

   // Load Geometry : File extension "dzg" for "DeltaZ Geometry"
   Geometry geometry;
   geometry.loadFile("geometries/square.dzg");

   // Initialise domain from geometry
   LaplaceSolver solver;
   solver.generateDomainFrom(geometry);

//   // Solve equation
//   solver.solve();
   Grid const& results = solver.getGrid();

   // Show results
   ResultApp resultInterface;
   resultInterface.show(geometry, results);

   return 0;
}
