module;

#include <memory>
#include <optional>
#include <vector>

export module RTIOW.HittableObjectList;

import RTIOW.HittableObject;
import RTIOW.HitRecord;
import RTIOW.Interval;
import RTIOW.Ray;

export class HittableObjectList: public HittableObject
{
  std::vector<std::shared_ptr<HittableObject>> objects{};

  public:
  constexpr HittableObjectList() {}
  explicit HittableObjectList(std::shared_ptr<HittableObject> object);

  constexpr void clear() { objects.clear(); }

  void add(std::shared_ptr<HittableObject> object);

  [[nodiscard]] std::optional<HitRecord>
  hit(Ray const &ray, Interval ray_t) const override;
};
