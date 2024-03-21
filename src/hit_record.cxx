module;

#include <memory>

export module RTIOW.HitRecord;

import RTIOW.Ray;
import RTIOW.Vec3;

class Material;

export struct HitRecord
{
  Point3                    p{};
  Vec3                      normal{};
  std::shared_ptr<Material> material{};
  double                    time{};
  bool                      front_face{};

  constexpr void set_face_normal(Ray const &r, Vec3 const &outward_normal)
  {
    // Sets the hit record normal vector.
    // NOTE: the parameter `outward_normal` is assumed to have unit length.
    front_face = dot(r.direction(), outward_normal) < 0;
    normal     = front_face ? outward_normal : -outward_normal;
  }
};
