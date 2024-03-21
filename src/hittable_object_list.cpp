module;

#include <memory>
#include <optional>
#include <vector>

module RTIOW.HittableObjectList;

HittableObjectList::HittableObjectList(std::shared_ptr<HittableObject> object)
{
  add(object);
}

void HittableObjectList::add(std::shared_ptr<HittableObject> object)
{
  objects.push_back(object);
}

[[nodiscard]] std::optional<HitRecord>
HittableObjectList::hit(Ray const &ray, Interval ray_t) const
{
  HitRecord list_record{};
  bool      hit_anything{};
  auto      closest_t_so_far{ ray_t.max };

  for (auto const &object: objects) {
    if (auto const record{
          object->hit(ray, Interval(ray_t.min, closest_t_so_far)) }) {
      hit_anything     = true;
      closest_t_so_far = record->time;
      list_record      = *record;
    }
  }
  return hit_anything ? std::optional{ list_record } : std::nullopt;
}
