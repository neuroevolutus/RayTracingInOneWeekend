export module RTIOW.Ray;

import RTIOW.Vec3;

export class Ray
{
  Point3 _origin{};
  Vec3   _direction{};

  public:
  constexpr Ray() {}
  constexpr Ray(Point3 const &_origin, Vec3 const &_direction)
    : _origin{ _origin }
    , _direction{ _direction }
  {}

  [[nodiscard]] constexpr Point3 origin() const noexcept { return _origin; }
  [[nodiscard]] constexpr Vec3 direction() const noexcept { return _direction; }

  [[nodiscard]] constexpr Point3 at(double time) const noexcept
  {
    return _origin + time * _direction;
  }
};
