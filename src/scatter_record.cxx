export module RTIOW.ScatterRecord;

import RTIOW.Color;
import RTIOW.Ray;

export struct ScatterRecord
{
  Ray   scattered_ray{};
  Color attenuation{};
};
