module;

#include <cassert>
#include <iostream>

module RTIOW.Vec3;

[[nodiscard]] Vec3 Vec3::random()
{
  return Vec3(random_double(), random_double(), random_double());
}

[[nodiscard]] Vec3 Vec3::random(double min, double max)
{
  return Vec3(
    random_double(min, max),
    random_double(min, max),
    random_double(min, max)
  );
}

std::ostream &operator<<(std::ostream &out, Vec3 const &v)
{
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

[[nodiscard]] Vec3 random_in_unit_disk()
{
  while (true) {
    auto const p{ Vec3(random_double(-1, 1), random_double(-1, 1), 0) };
    if (p.length_squared() < 1) return p;
  }
}

[[nodiscard]] Vec3 random_in_unit_sphere()
{
  while (true) {
    auto const p{ Vec3::random(-1, 1) };
    if (p.length_squared() < 1) return p;
  }
}

[[nodiscard]] Vec3 random_unit_vector()
{
  return unit_vector(random_in_unit_sphere());
}

[[nodiscard]] Vec3 random_on_hemisphere(Vec3 const &normal)
{
  Vec3 const on_unit_sphere{ random_unit_vector() };
  auto const result{ dot(on_unit_sphere, normal) > 0.0 ? on_unit_sphere :
                                                         -on_unit_sphere };
  assert(
    dot(normal, result) > 0.0
    && "Output vector is not in same hemisphere as input normal"
  );
  return result;
}
