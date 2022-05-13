#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <zucchini/zucchini.hpp>
#include <zgraphics/zgraphics.hpp>

class Program
{
public:
   static void Initialise(int argc, char* argv[]);

   static ze::Arguments const* GetArguments() noexcept;
   static int GetPID() noexcept;

   // Load Geometry
   // Solve Geometry
   // Show Results Window

   static void Terminate();

private:
   Program() = delete;

   static bool s_initialised;
   static ze::Arguments s_arguments;
   static unsigned s_pid;
};

#endif // PROGRAM_HPP

