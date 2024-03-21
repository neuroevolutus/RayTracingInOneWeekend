module;

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>

export module RTIOW.Camera;

import RTIOW.Color;
import RTIOW.HittableObject;
import RTIOW.HitRecord;
import RTIOW.Interval;
import RTIOW.Material.Base;
import RTIOW.Ray;
import RTIOW.Utility;
import RTIOW.Vec3;

export class Camera
{
  std::size_t image_height{};   // Rendered image height
  Point3      center{};         // Camera center
  Point3      pixel_00_loc{};   // Location of pixel (0, 0)
  Vec3        pixel_delta_u{};  // Offset to pixel to the right
  Vec3        pixel_delta_v{};  // Offset to pixel below
  Vec3        u{}, v{}, w{};    // Camera-relative basis vectors
  Vec3        defocus_disk_u{}; // Defocus disk horizontal radius
  Vec3        defocus_disk_v{}; // Defocus disk vertical radius

  constexpr void initialize() noexcept
  {
    image_height
      = std::max(1uz, static_cast<std::size_t>(image_width / aspect_ratio));

    center = look_from;

    // Determine viewport dimensions.
    auto const theta{ degrees_to_radians(vertical_field_of_view_in_degrees) };
    auto const viewport_height{ std::tan(theta / 2) * 2 * focus_distance };
    auto const viewport_width{
      viewport_height * static_cast<double>(image_width) / image_height
    };

    // Calculate the u, v and w unit basis vectors for the camera coordinate
    // frame.
    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(v_up, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and vertical viewport edges.
    auto const viewport_u{ viewport_width
                           * u };  // Vector across viewport horizontal edge
    auto const viewport_v{ viewport_height
                           * -v }; // Vector down viewport vertical edge

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto const viewport_upper_left{ center - focus_distance * w - viewport_u / 2
                                    - viewport_v / 2 };
    pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    auto const defocus_radius{
      focus_distance
      * std::tan(degrees_to_radians(defocus_angle_in_degrees / 2))
    };
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }

  // Returns a random point in the camera defocus disk.
  [[nodiscard]] Point3 defocus_disk_sample() const;

  [[nodiscard]] constexpr Color
  ray_color(Ray const &ray, std::ptrdiff_t depth, HittableObject const &world)
    const
  {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) return Color(0, 0, 0);
    HitRecord record{};
    if (auto const hit_record{ world.hit(ray, Interval(1E-3, infinity)) }) {
      if (auto const scatter_record{
            hit_record->material->scatter(ray, *hit_record) })
        return scatter_record->attenuation
             * ray_color(scatter_record->scattered_ray, depth - 1, world);
      else
        return Color(0, 0, 0);
    }
    auto const unit_direction{ unit_vector(ray.direction()) };
    auto const a{ 0.5 * (unit_direction.y() + 1.0) };
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  }

  // Get a randomly sampled camera ray for the pixel at location (i, j)
  // originating from the camera defocus disk.
  [[nodiscard]] constexpr Ray get_ray(std::size_t i, std::size_t j) const
  {
    // Get a randomly sampled camera ray
    auto const pixel_center{ pixel_00_loc + i * pixel_delta_u
                             + j * pixel_delta_v };
    auto const pixel_sample{ pixel_center + pixel_sample_square() };
    auto const ray_origin{ defocus_angle_in_degrees <= 0 ?
                             center :
                             defocus_disk_sample() };
    auto const ray_direction{ pixel_sample - ray_origin };
    return Ray(ray_origin, ray_direction);
  }


  // Returns a random point in the square surrounding a pixel at the origin.
  [[nodiscard]] Vec3 pixel_sample_square() const;

  public:
  double      aspect_ratio{ 1.0 };     // Ratio of image width over image height
  std::size_t image_width{ 100 };      // Rendered image width in pixel count
  std::size_t samples_per_pixel{ 10 }; // Count of random samples for each pixel
  std::size_t max_depth{ 10 }; // Maximum number of ray bounces into scene

  double vertical_field_of_view_in_degrees{ 90 };
  Point3 look_from{ Point3(0, 0, -1) }; // Point camera is looking from
  Point3 look_at{ Point3(0, 0, 0) };    // Point camera is looking at
  Vec3   v_up{ Vec3(0, 1, 0) };         // Camera-relative "up" direction

  double
    defocus_angle_in_degrees{}; // Variation angle of rays through each pixel
  double focus_distance{
    10
  }; // Distance from camera look point to plane of perfect focus

  void render(HittableObject const &world);
};
