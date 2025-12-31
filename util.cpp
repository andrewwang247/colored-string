/*
Utility functions for colors and numerics.

Copyright 2026. Andrew Wang.
*/
#include "util.h"

#include <limits>

#include "rgb_color.h"
using std::numeric_limits;

double util::normalize(channel ch) noexcept {
  constexpr color_t denom{color_cast(channel::END) - 1};
  return abs(static_cast<double>(ch)) / denom;
}

double util::normalize(color_t color) noexcept {
  constexpr color_t denom{numeric_limits<color_t>::max()};
  return abs(static_cast<double>(color)) / denom;
}

bool util::almost_eq(double lhs, double rhs, double epsilon) noexcept {
  return abs(lhs - rhs) < epsilon;
}

bool util::almost_less(double lhs, double rhs, double epsilon) noexcept {
  return lhs + epsilon < rhs;
}
