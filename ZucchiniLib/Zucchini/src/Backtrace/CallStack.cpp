#include <backward.hpp>
#include <ostream>
#include <sstream>

#include "zucchini/Backtrace/CallStack.hpp"

namespace ze
{
   CallStack::CallStack(RangedInt<0, 32> const size, int const skip)
   {
      // Load stacktrace
      backward::StackTrace stacktrace;
      stacktrace.load_here(size);
      stacktrace.skip_n_firsts(skip);

      m_threadID = stacktrace.thread_id();

      // Construct frames
      m_frames.reserve(size);

      backward::TraceResolver resolver;
      resolver.load_stacktrace(stacktrace);
      for (size_t i = 0; i < stacktrace.size(); ++i)
      {
         backward::ResolvedTrace trace = resolver.resolve(stacktrace[i]);
         m_frames.emplace_back(trace.idx, trace.object_filename, trace.object_function, trace.source.line, trace.source.col);
      }

      // Because we want most recent call last
      std::reverse(m_frames.begin(), m_frames.end());
   }

   void CallStack::print(std::ostream& os) const
   {
      os << "Stack trace from thread #" << getThreadID();
      if (getThreadID() == 0)
         os << " (main)";
      os << " (most recent call last)\n";

      for (auto& frame : m_frames)
      {
         os << "#"         << frame.index
            << "\tat "     << frame.func
            << ", line "   << (frame.line   > 0 ? frame.line   : '#')
            << ", column"  << (frame.column > 0 ? frame.column : '#')
            << " in file " << frame.file << '\n';
      }

      os << std::endl;
   }

   CallStack Stacktrace(RangedInt<0, 32> const size, int const skip)
   {
      return CallStack(size, skip + 1);
   }
}
