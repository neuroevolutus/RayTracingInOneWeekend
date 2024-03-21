module;

#include <algorithm>

export module RTIOW.Interval;

import RTIOW.Utility;

export struct Interval
{
  double min{}, max{};

  constexpr Interval()
    : min{ +infinity }
    , max{ -infinity } {} // Default interval is empty
  constexpr Interval(double min, double max): min{ min }, max{ max } {}

  [[nodiscard]] constexpr double size() { return max - min; }

  [[nodiscard]] constexpr Interval expand(double delta)
  {
    auto const padding{ delta / 2 };
    return Interval(min - padding, max + padding);
  }

  [[nodiscard]] constexpr bool contains(double x) const noexcept
  {
    return min <= x && x <= max;
  }

  [[nodiscard]] constexpr bool surrounds(double x) const noexcept
  {
    return min < x && x < max;
  }

  [[nodiscard]] constexpr double clamp(double x) const noexcept
  {
    return std::clamp(x, min, max);
  }
};

export constexpr Interval empty{};
export constexpr Interval universe(-infinity, +infinity);
