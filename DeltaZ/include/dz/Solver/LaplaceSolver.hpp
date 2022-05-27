#ifndef LAPLACESOLVER_HPP
#define LAPLACESOLVER_HPP

#include "dz/Solver/Geometry.hpp"
#include "dz/Solver/Grid.hpp"

struct Results
{
   Geometry const& geometry;
   Grid const& grid;
};

using GeometryFile = ze::NamedType<std::filesystem::path, struct GeometryFileParameter,
                                   ze::ImplicitlyConvertible, ze::Dereferenceable>;

class LaplaceSolver
{
public:
   void load(GeometryFile const& file);
   void generateGrid();
   void solve();
   Results getResults() const noexcept;

   LaplaceSolver() = default;

private:
   Geometry m_geometry;
   Grid m_grid;
};

#include "LaplaceSolver.inl"

#endif // LAPLACESOLVER_HPP

