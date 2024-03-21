module;

#include <optional>

module RTIOW.Material.Lambertian;

import RTIOW.Vec3;

[[nodiscard]] std::optional<ScatterRecord>
Lambertian::scatter(Ray const &in, HitRecord const &record) const
{
  auto const scatter_direction{ record.normal + random_unit_vector() };
  // Catch degenerate scatter direction
  return std::optional{
    ScatterRecord{
                  Ray(
                  record.p,
                  scatter_direction.near_zero() ? record.normal : scatter_direction
                  ), albedo}
  };
}
