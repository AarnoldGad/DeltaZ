#include "dz/Program.hpp"

#if defined(_WIN32)
   #include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
   #include <sys/types.h>
   #include <unistd.h>
#endif

bool Program::s_initialised = false;
ze::Arguments Program::s_arguments;

unsigned Program::s_pid =
#if defined(_WIN32)
   static_cast<unsigned>(GetCurrentProcessId());
#elif defined(__linux__) || defined(__APPLE__) || defined(__MACH__)
   static_cast<unsigned>(getpid());
#else
   0;
#endif

void Program::Initialise(int argc, char* argv[])
{
   zg::Context::Initialise();
   zg::Context::LoadFreetype();

   s_initialised = true;
}

ze::Arguments const* Program::GetArguments() noexcept
{
   return &s_arguments;
}

int Program::GetPID() noexcept
{
   return s_pid;
}

void Program::Terminate()
{
   zg::Context::Terminate();

   s_initialised = false;
}

