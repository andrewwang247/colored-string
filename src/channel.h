/*
Channel numerics.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <cassert>
#include <cmath>
#include <concepts>
#include <limits>

#include "true_color.h"

namespace channel {
static constexpr auto MAX_COLOR = std::numeric_limits<color_t>::max();

/**
 * @brief Normalize color_t values to [0, 1] range.
 * @param color The color input value.
 * @return The normalized floating point value.
 */
constexpr double normalize(color_t color) noexcept {
  return static_cast<double>(color) / MAX_COLOR;
}

/**
 * @brief Denormalize values back to color_t range.
 * @param normed Normalized value in [0, 1] range.
 * @return Denormalized color_t value.
 */
constexpr color_t denormalize(std::floating_point auto normed) noexcept {
  assert(0. <= normed && normed <= 1.);
  const auto expanded = std::lround(MAX_COLOR * normed);
  return static_cast<color_t>(expanded);
}

/**
 * @brief Approximate equality for floating point types.
 * @param lhs Left number to compare.
 * @param rhs Right number to compare.
 * @return Whether lhs and rhs are within epsilon of each other.
 */
constexpr bool almost_eq(std::floating_point auto lhs,
                         std::floating_point auto rhs) noexcept {
  static constexpr auto EPSILON = 1e-4;
  return std::abs(lhs - rhs) < EPSILON;
}
}  // namespace channel
