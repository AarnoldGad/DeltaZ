#include "zepch.hpp"

#include "zucchini/Debug/Assert.hpp"

#include "zucchini/Common/Random.hpp"

namespace ze
{
   std::default_random_engine Random::s_engine;

   void Random::Seed(unsigned int const seed)
   {
      s_engine.seed(seed);
   }

   uint32_t Random::GenerateInteger(uint32_t const minimum, uint32_t const maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      ZE_ASSERT(maximum <= std::default_random_engine::max(), "Maximum value is too high !");

      return static_cast<unsigned int>(s_engine()) % (maximum - minimum) + minimum;
   }

   float Random::GenerateFloat(float const minimum, float const maximum)
   {
      ZE_ASSERT(minimum < maximum, "Minimum value is greater than maximum !");
      ZE_ASSERT(maximum <= static_cast<float>(std::default_random_engine::max()), "Maximum value is too high !");

      return static_cast<float>(s_engine()) / static_cast<float>(std::default_random_engine::max()) / (maximum - minimum) + minimum;
   }
}
