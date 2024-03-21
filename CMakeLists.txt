cmake_minimum_required(VERSION 3.29)

project(RTIOW CXX)
set(VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(RTIOW_raytracer)
add_library(RTIOW::raytracer ALIAS RTIOW_raytracer)

set_target_properties(RTIOW_raytracer PROPERTIES OUTPUT_NAME RTIOWraytracer
                                                 EXPORT_NAME raytracer)

target_compile_features(RTIOW_raytracer PUBLIC cxx_std_23)

target_sources(
  RTIOW_raytracer
  PRIVATE src/camera.cpp
          src/color.cpp
          src/dielectric.cpp
          src/hittable_object_list.cpp
          src/lambertian.cpp
          src/metal.cpp
          src/rtiow_utility.cpp
          src/sphere.cpp
          src/vec3.cpp
  PUBLIC FILE_SET
         rtiow_cxx_modules
         TYPE
         CXX_MODULES
         FILES
         src/camera.cxx
         src/color.cxx
         src/dielectric.cxx
         src/hit_record.cxx
         src/hittable_object.cxx
         src/hittable_object_list.cxx
         src/interval.cxx
         src/lambertian.cxx
         src/metal.cxx
         src/material.cxx
         src/material_base.cxx
         src/ray.cxx
         src/rtiow.cxx
         src/rtiow_utility.cxx
         src/scatter_record.cxx
         src/sphere.cxx
         src/vec3.cxx)

include(GNUInstallDirs)

install(
  TARGETS RTIOW_raytracer
  EXPORT RTIOW
  FILE_SET rtiow_cxx_modules
  DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(
  EXPORT RTIOW
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/RTIOW"
  NAMESPACE RTIOW::)
