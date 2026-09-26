/*
Cylindrical coordinate color representation.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <cmath>
#include <compare>
#include <concepts>

#include "true_color.h"

/**
 * @brief Base cylindrical representation.
 */
class cylindrical {
 protected:
  double chroma{}, hue{}, lightness{}, saturation{}, value{};

  explicit cylindrical() = default;
  explicit cylindrical(true_color tc) noexcept;
  cylindrical(double hue_in, double sat_in) noexcept;

 public:
  /**
   * @brief Convert cylindrical color into RGB coordinates.
   * @return 24 bit RGB representation of this.
   */
  virtual true_color to_rgb() const noexcept = 0;

  cylindrical(const cylindrical&) = default;
  cylindrical& operator=(const cylindrical&) = default;
  virtual ~cylindrical();

  friend bool operator==(const cylindrical& lhs,
                         const cylindrical& rhs) noexcept;

  friend std::partial_ordering operator<=>(const cylindrical& lhs,
                                           const cylindrical& rhs) noexcept;
};
