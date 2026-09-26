/*
Hue Saturation Lightness

Copyright 2026. Andrew Wang.
*/
#pragma once
#include "cylindrical.h"
#include "true_color.h"

class hsl_color : public cylindrical {
 public:
  explicit hsl_color() = default;
  explicit hsl_color(true_color tc) noexcept;
  hsl_color(double hue_in, double sat_in, double light_in) noexcept;

  true_color to_rgb() const noexcept override;
};
