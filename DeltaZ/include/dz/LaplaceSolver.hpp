#ifndef LAPLACESOLVER_HPP
#define LAPLACESOLVER_HPP

#include "dz/Geometry.hpp"
#include "dz/Grid.hpp"

class LaplaceSolver
{
public:
   void solve();
   void generateDomainFrom(Geometry const& geometry);

   Grid const& getGrid() const noexcept;
   
   LaplaceSolver() = default;

private:
   Grid m_grid;
};

#include "LaplaceSolver.inl"

#endif // LAPLACESOLVER_HPP

