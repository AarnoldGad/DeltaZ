#include <iostream>

#include "dz/Program.hpp"
#include "dz/defines.hpp"

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
   std::filesystem::path file = "geometries/";
   if (Program::GetArguments()->size() > 1)
      file /= Program::GetArguments()->getArgument(2)->value;
   else // Load Geometry : File extension "dzg" for "DeltaZ Geometry"
      file /= "square.dzg";

   LaplaceSolver solver;
   solver.load(GeometryFile(file));

   std::cout << file << std::endl;
   return 0;

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
