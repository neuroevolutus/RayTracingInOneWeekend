module;

#include <optional>

export module RTIOW.Material.Metal;

import RTIOW.Color;
import RTIOW.HitRecord;
import RTIOW.Material.Base;
import RTIOW.Ray;
import RTIOW.ScatterRecord;

export class Metal: public Material
{
  Color  albedo{};
  double fuzz{};

  public:
  constexpr Metal(Color const &albedo, double fuzz)
    : albedo{ albedo }
    , fuzz{ fuzz < 1 ? fuzz : 1 }
  {}

  [[nodiscard]] std::optional<ScatterRecord>
  scatter(Ray const &in, HitRecord const &record) const override;
};
