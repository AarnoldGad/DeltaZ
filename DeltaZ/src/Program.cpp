#include "dz/Program.hpp"

#if defined(_WIN32)
   #include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
   #include <sys/types.h>
   #include <unistd.h>
#endif

ze::Arguments Program::s_arguments;

unsigned Program::s_pid =
#if defined(_WIN32)
   static_cast<unsigned>(GetCurrentProcessId());
#elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
   static_cast<unsigned>(getpid());
#else
   0;
#endif

void Program::Configure(int argc, char* argv[])
{
   s_arguments.configure(argc, argv);
}

ze::Arguments const* Program::GetArguments() noexcept
{
   return &s_arguments;
}

int Program::GetPID() noexcept
{
   return s_pid;
}

