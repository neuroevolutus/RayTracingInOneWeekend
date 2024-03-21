module;

#include <optional>

export module RTIOW.Material.Dielectric;

import RTIOW.HitRecord;
import RTIOW.Material.Base;
import RTIOW.Ray;
import RTIOW.ScatterRecord;

export class Dielectric: public Material
{
  double index_of_refraction{};

  [[nodiscard]] static constexpr double
  reflectance(double cosine, double refraction_index)
  {
    // Use Schlick's approximation for reflectance.
    auto const r0{
      std::pow((1 - refraction_index) / (1 + refraction_index), 2)
    };
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }

  public:
  explicit constexpr Dielectric(double index_of_refraction)
    : index_of_refraction{ index_of_refraction }
  {}

  [[nodiscard]] std::optional<ScatterRecord>
  scatter(Ray const &in, HitRecord const &record) const override;
};
