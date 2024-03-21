module;

#include <cassert>
#include <cmath>
#include <memory>
#include <optional>

module RTIOW.Sphere;

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
  : center{ center }
  , radius{ radius }
  , material{ material }
{}

[[nodiscard]] std::optional<HitRecord>
Sphere::hit(Ray const &ray, Interval ray_t) const noexcept
{
  auto const oc{ ray.origin() - center };
  auto const a{ ray.direction().length_squared() };
  auto const half_b{ dot(oc, ray.direction()) };
  auto const c{ oc.length_squared() - std::pow(radius, 2) };

  auto const discriminant{ std::pow(half_b, 2) - a * c };
  if (discriminant < 0) return {};
  auto const sqrt_d{ std::sqrt(discriminant) };

  // Find the nearest square root that lies in the acceptable range.
  auto root{ (-half_b - sqrt_d) / a };
  if (!ray_t.surrounds(root)) {
    root = (-half_b + sqrt_d) / a;
    if (!ray_t.surrounds(root)) return {};
  }

  HitRecord record{};
  record.time = root;
  record.p    = ray.at(record.time);
  assert(
    (record.p - center).length_squared() - std::pow(radius, 2) <= 1E-9
    && "Hit point for sphere is not on sphere surface"
  );
  Vec3 const outward_normal{ (record.p - center) / radius };
  record.set_face_normal(ray, outward_normal);
  record.material = material;
  return std::optional{ record };
}
