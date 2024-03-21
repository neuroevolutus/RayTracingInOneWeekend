module;

#include <optional>

export module RTIOW.Material.Base;

import RTIOW.HitRecord;
import RTIOW.Ray;
import RTIOW.ScatterRecord;

export struct Material
{
  virtual ~Material() = default;
  virtual std::optional<ScatterRecord>
  scatter(Ray const &in, HitRecord const &record) const = 0;
};
