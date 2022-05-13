#include "zepch.hpp"

#include "zucchini/Math/Math.hpp"

#include <cmath>

namespace ze
{
   double pi()
   {
      static double pi = std::acos(-1.0);
      return pi;
   }
}
