module;

#include <optional>

module RTIOW.Material.Dielectric;

import RTIOW.Color;
import RTIOW.Utility;
import RTIOW.Vec3;

[[nodiscard]] std::optional<ScatterRecord>
Dielectric::scatter(Ray const &in, HitRecord const &record) const
{
  // Assume ambient environment is air, which has index of refraction 1.0
  double const refraction_ratio{ record.front_face ? 1.0 / index_of_refraction :
                                                     index_of_refraction };
  Vec3 const   unit_direction{ unit_vector(in.direction()) };
  double const cos_theta{ std::fmin(dot(-unit_direction, record.normal), 1.0) };
  double const sin_theta{ std::sqrt(1.0 - std::pow(cos_theta, 2)) };
  bool const   cannot_refract{ refraction_ratio * sin_theta > 1.0
                             || reflectance(cos_theta, refraction_ratio)
                                  > random_double() };
  Vec3 const   direction{
    cannot_refract ? reflect(unit_direction, record.normal) :
                       refract(unit_direction, record.normal, refraction_ratio)
  };
  return std::optional{
    ScatterRecord{Ray(record.p, direction), Color(1.0, 1.0, 1.0)}
  };
}
