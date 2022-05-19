#ifndef GEOEMTRY_HPP
#define GEOEMTRY_HPP

#include <filesystem>
#include "dz/Node.hpp"

class Geometry
{
public:
   void loadFile(std::filesystem::path const& file);

   float getPrecision() const noexcept;
   std::vector<Node>& getNodes() noexcept;
   std::vector<Node> const& getNodes() const noexcept;

   Geometry();

private:
   float m_precision;
   std::vector<Node> m_nodes;
};

#include "Geometry.inl"

#endif // GEOEMTRY_HPP

