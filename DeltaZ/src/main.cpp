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
      file /= Program::GetArguments()->getArgument(1)->value;
   else // Load Geometry : File extension "dzg" for "DeltaZ Geometry"
      file /= "square.dzg";

   ze::Console::Print("Loading geometry...");
   LaplaceSolver solver;
   solver.load(GeometryFile(file));

   // generate grid from geometry
   ze::Console::Print("Generating grid...");
   solver.generateGrid();

   // Solve equation
   ze::Console::Print("Solving domain...");
   solver.solve();
   Results results = solver.getResults();

   // Show results
   ResultApp resultInterface;
   resultInterface.show(results);

   return 0;
}
