module;

#include <random>

module RTIOW.Utility;

static std::uniform_real_distribution<double> distribution(0.0, 1.0);
static std::seed_seq                          seed{ 1 };
static std::mt19937                           generator{ seed };

[[nodiscard]] double random_double() { return distribution(generator); }

[[nodiscard]] double random_double(double min, double max)
{
  return min + (max - min) * random_double();
}
