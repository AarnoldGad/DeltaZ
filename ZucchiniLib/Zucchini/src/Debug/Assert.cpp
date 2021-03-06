#include "zepch.hpp"

#include "zucchini/Debug/Assert.hpp"

#include "zucchini/Common/Console.hpp"

[[noreturn]] void ze::AssertHandler::handle(SourceLocation const& location, char const* expression, char const* message) noexcept
{
   Console::Trace("{0}::{1} ({2}) : Assertion failed \"{3}\" : {4}",
                  location.file, location.function, location.line, expression, (message ? message : "No more information"));
   std::abort();
}

