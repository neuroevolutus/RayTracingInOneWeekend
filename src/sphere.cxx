module;

#include <memory>
#include <optional>

export module RTIOW.Sphere;

import RTIOW.HitRecord;
import RTIOW.HittableObject;
import RTIOW.Interval;
import RTIOW.Material;
import RTIOW.Ray;
import RTIOW.Vec3;

export class Sphere: public HittableObject
{
  Point3                    center{};
  double                    radius{};
  std::shared_ptr<Material> material{};

  public:
  Sphere(Point3 center, double radius, std::shared_ptr<Material> material);

  [[nodiscard]] std::optional<HitRecord>
  hit(Ray const &ray, Interval ray_t) const noexcept override;
};
