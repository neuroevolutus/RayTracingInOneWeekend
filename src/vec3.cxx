module;

#include <array>
#include <cassert>
#include <cmath>
#include <compare>

export module RTIOW.Vec3;

import RTIOW.Utility;

export class Vec3
{
  std::array<double, 3> v{};

  public:
  constexpr Vec3() {}
  constexpr Vec3(double v1, double v2, double v3): v{ v1, v2, v3 } {}

  constexpr std::strong_ordering operator<=>(Vec3 const &other
  ) const & = default;

  [[nodiscard]] constexpr double x() const noexcept { return v[0]; }
  [[nodiscard]] constexpr double y() const noexcept { return v[1]; }
  [[nodiscard]] constexpr double z() const noexcept { return v[2]; }

  [[nodiscard]] constexpr double r() const noexcept { return v[0]; }
  [[nodiscard]] constexpr double g() const noexcept { return v[1]; }
  [[nodiscard]] constexpr double b() const noexcept { return v[2]; }

  [[nodiscard]] constexpr Vec3 operator-() const noexcept
  {
    return Vec3(-v[0], -v[1], -v[2]);
  }

  [[nodiscard]] constexpr double operator[](std::size_t i) const noexcept
  {
    return v[i];
  }

  [[nodiscard]] constexpr double &operator[](std::size_t i) noexcept
  {
    return v[i];
  }

  [[nodiscard]] constexpr Vec3 operator+(Vec3 const &other) const noexcept
  {
    return Vec3(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2]);
  }

  [[nodiscard]] constexpr Vec3 operator-(Vec3 const &other) const noexcept
  {
    return Vec3(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2]);
  }

  [[nodiscard]] constexpr Vec3 operator*(Vec3 const &other) const noexcept
  {
    return Vec3(v[0] * other.v[0], v[1] * other.v[1], v[2] * other.v[2]);
  }

  [[nodiscard]] constexpr Vec3 operator*(double time) const noexcept
  {
    return Vec3(v[0] * time, v[1] * time, v[2] * time);
  }

  [[nodiscard]] constexpr Vec3 operator/(double time) const noexcept
  {
    return *this * (1 / time);
  }

  constexpr Vec3 &operator+=(Vec3 const &other) noexcept
  {
    v[0] += other.v[0];
    v[1] += other.v[1];
    v[2] += other.v[2];
    return *this;
  }

  constexpr Vec3 &operator*=(double time) noexcept
  {
    v[0] *= time;
    v[1] *= time;
    v[2] *= time;
    return *this;
  }

  constexpr Vec3 &operator/=(double time) noexcept { return *this *= 1 / time; }

  [[nodiscard]] constexpr double length_squared() const noexcept
  {
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
  }

  [[nodiscard]] constexpr bool near_zero() const
  {
    // Return true if the vector is close to zero in all dimensions.
    constexpr double s{ 1E-8 };
    return std::fabs(v[0]) < s && std::fabs(v[1]) < s && std::fabs(v[2]) < s;
  }

  [[nodiscard]] constexpr double length() const noexcept
  {
    return std::sqrt(length_squared());
  }

  [[nodiscard]] static Vec3 random();

  [[nodiscard]] static Vec3 random(double min, double max);
};

export [[nodiscard]] constexpr Vec3 operator*(double t, Vec3 const &v) noexcept
{
  return v * t;
}

// Point3 is just an alias for Vec3 but useful for geometric clarity in the
// code.
export using Point3 = Vec3;

export constexpr auto zero{ Vec3(0, 0, 0) };

// Vector utility functions
export std::ostream &operator<<(std::ostream &out, Vec3 const &v);

export [[nodiscard]] constexpr double dot(Vec3 const &u, Vec3 const &v) noexcept
{
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

export [[nodiscard]] constexpr Vec3 cross(Vec3 const &u, Vec3 const &v) noexcept
{
  auto const result{ Vec3(
    u.y() * v.z() - u.z() * v.y(),
    u.z() * v.x() - u.x() * v.z(),
    u.x() * v.y() - u.y() * v.x()
  ) };
  assert(
    std::abs(dot(result, u)) <= 1E15 && std::abs(dot(result, v)) <= 1E15
    && "Cross product is not perpendicular to its operands"
  );
  return result;
}

export [[nodiscard]] constexpr Vec3 unit_vector(Vec3 v) noexcept
{
  auto const result{ v / v.length() };
  assert(
    std::abs(dot(result, result) - 1.0) <= 1E15
    && "Output vector is not of unit length"
  );
  return result;
}

export [[nodiscard]] Vec3 random_in_unit_disk();
export [[nodiscard]] Vec3 random_in_unit_sphere();
export [[nodiscard]] Vec3 random_unit_vector();
export [[nodiscard]] Vec3 random_on_hemisphere(Vec3 const &normal);

export [[nodiscard]] constexpr Vec3 reflect(Vec3 const &v, Vec3 const &normal)
{
  return v - 2 * dot(v, normal) * normal;
}

export [[nodiscard]] constexpr Vec3
refract(Vec3 const &v, Vec3 const &normal, double eta_over_eta_prime)
{
  auto const cos_theta{ std::fmin(dot(-v, normal), 1.0) };
  Vec3 const ray_out_perpendicular{ eta_over_eta_prime
                                    * (v + cos_theta * normal) };
  Vec3 const ray_out_parallel{
    -std::sqrt(std::fabs(1.0 - ray_out_perpendicular.length_squared())) * normal
  };
  return ray_out_perpendicular + ray_out_parallel;
}
