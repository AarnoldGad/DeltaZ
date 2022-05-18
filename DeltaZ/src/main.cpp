#include <iostream>

#include "dz/Program.hpp"
#include "dz/ResultApp.hpp"

#include <glad/glad.h>

int main(int argc, char* argv[])
{
   Program::Configure(argc, argv);

   // Load Geometry : File extension "dzg" for "DeltaZ Geometry"

   // Initialise domain from geometry

//   // Solve equation

   // Show results
   ResultApp resultInterface;
//   resultInterface.show(results);

   return 0;
}
