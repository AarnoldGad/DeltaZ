#include "dz/Geometry.hpp"

#include <zucchini/zucchini.hpp>
#include <yaml-cpp/yaml.h>

Geometry::Geometry()
   : m_precision{} {}

void Geometry::loadFile(std::filesystem::path const& file)
{
   YAML::Node geometry = YAML::LoadFile(file);
   YAML::Node points = geometry["points"];

   m_precision = geometry["precision"].as<double>();
   m_nodes.clear();
   m_nodes.reserve(points.size());

   for (auto point : points)
      m_nodes.push_back(Node({ point.second["pos"][0].as<double>(),
                               point.second["pos"][1].as<double>() },
                               point.second["value"].as<double>()));
}
