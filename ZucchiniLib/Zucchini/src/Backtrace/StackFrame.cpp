#include "zepch.hpp"

#include "zucchini/Backtrace/StackFrame.hpp"

namespace ze
{
   StackFrame::StackFrame(size_t const index,
                          std::string const& file, std::string const& func,
                          size_t const line, size_t const col)
      : index(index), file(file), func(func), line(line), column(col) {}
}

