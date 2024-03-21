module;

#include <cstddef>
#include <iostream>

export module RTIOW.Color;

import RTIOW.Vec3;

export using Color = Vec3;

export void write_color(
  std::ostream &out,
  Color         pixel_color,
  std::size_t   samples_per_pixel
);
