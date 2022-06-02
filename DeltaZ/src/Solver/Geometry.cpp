#include "dz/Solver/Geometry.hpp"

#include <zucchini/zucchini.hpp>
#include "dz/defines.hpp"

Geometry::Geometry()
   : m_precision{}, m_mode(Mode::Closed) {}

void Geometry::loadFile(std::filesystem::path const& file)
{
   m_armatures.clear();
   YAML::Node geometry = YAML::LoadFile(file);

   m_precision = geometry["precision"].as<float>();
   m_mode = static_cast<Mode>(geometry["mode"].as<int>());

   YAML::Node armatures = geometry["armatures"];

   int i = 0;
   m_armatures.resize(armatures.size());
   for (auto armature : armatures)
   {
      for (auto node : armature["nodes"])
      {
         m_armatures.at(i).push_back(Node(node["pos"].as<glm::vec2>(),
                                          node["value"].as<double>()));
      }
      ++i;
   }
}
