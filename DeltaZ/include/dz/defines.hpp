#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <zgraphics/zgraphics.hpp>
#include <yaml-cpp/yaml.h>

namespace YAML
{
   template<>
   struct convert<glm::vec2>
   {
      static Node encode(glm::vec2 const& rhs)
      {
         Node node;
         node.push_back(rhs.x);
         node.push_back(rhs.y);
         return node;
      }

      static bool decode(Node const& node, glm::vec2& rhs)
      {
         if (!node.IsSequence() || node.size() != 2)
            return false;

         rhs.x = node[0].as<float>();
         rhs.y = node[1].as<float>();
         return true;
      }
   };
}

#endif // DEFINES_HPP
