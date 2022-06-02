#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "dz/Solver/Node.hpp"

#include <filesystem>

enum class Mode : int
{
   Closed = 1, Expanded
};

class Geometry
{
public:
   using Armature = std::vector<Node>;

   void loadFile(std::filesystem::path const& file);

   explicit operator bool() const noexcept;

   float getPrecision() const noexcept;
   Mode getMode() const noexcept;
   int getIterations() const noexcept;

   std::vector<Armature>& getArmatures() noexcept;
   std::vector<Armature> const& getArmatures() const noexcept;

   Geometry();

private:
   float m_precision;
   Mode m_mode;
   int m_iterations;
   std::vector<Armature> m_armatures;
};

#include "Geometry.inl"

#endif // GEOMETRY_HPP

