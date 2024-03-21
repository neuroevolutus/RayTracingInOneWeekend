module;

#include <optional>

export module RTIOW.Material.Lambertian;

import RTIOW.Color;
import RTIOW.HitRecord;
import RTIOW.Material.Base;
import RTIOW.Ray;
import RTIOW.ScatterRecord;

export class Lambertian: public Material
{
  Color albedo{};

  public:
  explicit constexpr Lambertian(Color const &albedo): albedo{ albedo } {}

  [[nodiscard]] std::optional<ScatterRecord>
  scatter(Ray const &in, HitRecord const &record) const override;
};
