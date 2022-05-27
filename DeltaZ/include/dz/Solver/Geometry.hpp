#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "dz/Solver/Node.hpp"

#include <filesystem>

class Geometry
{
public:
   void loadFile(std::filesystem::path const& file);

   explicit operator bool() const noexcept;

   float getPrecision() const noexcept;

   std::vector<Node>& getNodes() noexcept;
   std::vector<Node> const& getNodes() const noexcept;

   Geometry();

private:
   float m_precision;
   std::vector<Node> m_nodes;
};

#include "Geometry.inl"

#endif // GEOMETRY_HPP

