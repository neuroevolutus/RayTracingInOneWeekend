module;

#include <cstddef>
#include <iostream>

module RTIOW.Camera;

[[nodiscard]] Point3 Camera::defocus_disk_sample() const
{
  auto const p{ random_in_unit_disk() };
  return center + p[0] * defocus_disk_u + p[1] * defocus_disk_v;
}

[[nodiscard]] Vec3 Camera::pixel_sample_square() const
{
  auto const px{ -0.5 + random_double() };
  auto const py{ -0.5 + random_double() };
  return px * pixel_delta_u + py * pixel_delta_v;
}

void Camera::render(HittableObject const &world)
{
  initialize();
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (std::size_t j{}; j < image_height; ++j) {
    std::cerr << "\rScan lines remaining: " << image_height - j << ' ';
    for (std::size_t i{}; i < image_width; ++i) {
      Color pixel_color(0, 0, 0);
      for (std::size_t sample{}; sample < samples_per_pixel; ++sample) {
        Ray const r{ get_ray(i, j) };
        pixel_color += ray_color(r, max_depth, world);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }
  std::cerr << "\rDone.                 \n";
}
