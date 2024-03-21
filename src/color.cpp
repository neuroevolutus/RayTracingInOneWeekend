module;

#include <cmath>
#include <cstddef>
#include <iostream>

module RTIOW.Color;

import RTIOW.Interval;

constexpr double linear_to_gamma(double linear_component)
{
  return std::sqrt(linear_component);
}

void write_color(
  std::ostream &out,
  Color         pixel_color,
  std::size_t   samples_per_pixel
)
{
  // Divide the color by the number of samples.
  auto const scale{ 1.0 / samples_per_pixel };

  // Divide the color by the number of samples
  // and then apply the linear to gamma transform.
  auto const r{ linear_to_gamma(pixel_color.r() * scale) };
  auto const g{ linear_to_gamma(pixel_color.g() * scale) };
  auto const b{ linear_to_gamma(pixel_color.b() * scale) };

  // Write the translated [0, 255] value of each color component.
  constexpr Interval intensity(0.000, 0.999);
  out << static_cast<std::size_t>(256.0 * intensity.clamp(r)) << ' '
      << static_cast<std::size_t>(256.0 * intensity.clamp(g)) << ' '
      << static_cast<std::size_t>(256.0 * intensity.clamp(b)) << '\n';
}
