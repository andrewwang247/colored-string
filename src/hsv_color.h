/*
Hue Saturation Value

Copyright 2026. Andrew Wang.
*/
#pragma once
#include "cylindrical.h"
#include "true_color.h"

/**
 * @brief HSV colors.
 */
class hsv_color : public cylindrical {
 public:
  explicit hsv_color() = default;
  explicit hsv_color(true_color tc) noexcept;
  hsv_color(double hue_in, double sat_in, double val_in) noexcept;

  true_color to_rgb() const noexcept override;
};
