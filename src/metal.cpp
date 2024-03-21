module;

#include <optional>

module RTIOW.Material.Metal;

import RTIOW.Vec3;

[[nodiscard]] std::optional<ScatterRecord>
Metal::scatter(Ray const &in, HitRecord const &record) const
{
  Vec3 const reflected{ reflect(unit_vector(in.direction()), record.normal) };
  Ray const scattered{ Ray(record.p, reflected + fuzz * random_unit_vector()) };
  if (dot(scattered.direction(), record.normal) > 0)
    return std::optional{
      ScatterRecord{scattered, albedo}
    };
  else
    return std::nullopt;
}
