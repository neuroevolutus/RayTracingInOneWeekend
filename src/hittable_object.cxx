module;

#include <optional>

export module RTIOW.HittableObject;

import RTIOW.HitRecord;
import RTIOW.Interval;
import RTIOW.Ray;

export struct HittableObject
{
  virtual ~HittableObject() = default;
  [[nodiscard]] virtual std::optional<HitRecord>
  hit(Ray const &r, Interval ray_t) const = 0;
};
