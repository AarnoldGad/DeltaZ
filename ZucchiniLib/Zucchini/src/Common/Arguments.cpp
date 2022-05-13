#include "zucchini/Common/Arguments.hpp"

namespace ze
{
   Arguments::Arguments(int argc, char* argv[])
   {
      setArguments(argc, argv);
   }

   void Arguments::setArguments(int argc, char* argv[])
   {
      m_arguments.clear();
      m_arguments.resize(argc);

      for (int i = 0; i < argc; ++i)
         m_arguments.push_back({ argv[i] });
   }

   std::vector<ze::Arguments::Argument>::const_iterator Arguments::find(std::string const& value) const
   {
      auto found = std::find_if(m_arguments.begin(), m_arguments.end(),
                                [&value](Argument const& argument) { return argument.value == value; });
      return found;
   }
}
