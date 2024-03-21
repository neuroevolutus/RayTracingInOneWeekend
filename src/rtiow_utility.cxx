module;

#include <limits>
#include <random>

export module RTIOW.Utility;

// Constants
export constexpr double infinity{ std::numeric_limits<double>::infinity() };
export constexpr double pi{ 3.1415926535897932385 };

// Utility Functions
export [[nodiscard]] constexpr double degrees_to_radians(double degrees
) noexcept
{
  return degrees * pi / 180.0;
}

// Returns a random real in [0, 1).
export [[nodiscard]] double random_double();

// Returns a random real in [min, max).
export [[nodiscard]] double random_double(double min, double max);
