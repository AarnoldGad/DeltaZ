#include "dz/Solver/Geometry.hpp"

#include <zucchini/zucchini.hpp>
#include "dz/defines.hpp"

Geometry::Geometry()
   : m_precision{}, m_mode(Mode::Closed) {}

void Geometry::loadFile(std::filesystem::path const& file)
{
   m_armatures.clear();
   YAML::Node geometry = YAML::LoadFile(file);
   YAML::Node armatures = geometry["armatures"];

   m_precision = geometry["precision"].as<float>();
   m_mode = static_cast<Mode>(geometry["mode"].as<int>());

   int i = 0;
   for (auto nodes : armatures)
   {
      for (auto vertex : nodes.second)
         m_armatures[i].push_back(Node(vertex.second["pos"].as<glm::vec2>(),
                                       vertex.second["value"].as<double>()));
      ++i;
   }
}
