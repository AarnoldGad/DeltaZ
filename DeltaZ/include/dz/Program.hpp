#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <zucchini/zucchini.hpp>
#include <zgraphics/zgraphics.hpp>

class Program
{
public:
   static void Configure(int argc, char* argv[]);

   static ze::Arguments const* GetArguments() noexcept;
   static int GetPID() noexcept;

private:
   Program() = delete;

   static ze::Arguments s_arguments;
   static unsigned s_pid;
};

#endif // PROGRAM_HPP

