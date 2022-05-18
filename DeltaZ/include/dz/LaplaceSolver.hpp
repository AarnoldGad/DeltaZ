#ifndef LAPLACESOLVER_HPP
#define LAPLACESOLVER_HPP

#include "dz/Geometry.hpp"
#include "dz/Grid.hpp"

class Result
{

};

class LaplaceSolver
{
public:
   Result solve();
   void generateDomainFrom(Geometry const& geometry);

private:
   Grid m_grid;
};

#endif // LAPLACESOLVER_HPP

