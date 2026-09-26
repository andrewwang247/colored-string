/*
Channel numerics.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <cmath>
#include <concepts>
#include <stdexcept>

#include "true_color.h"

namespace channel {

/**
 * @brief Check that a value is within a closed range.
 * @param value The value to check.
 * @tparam Left The left bound of the range.
 * @tparam Right The right bound of the range.
 */
template <auto Left, auto Right>
constexpr void validate_range(auto value) {
  static_assert(Left < Right);
  if (value < Left || value > Right) {
    throw std::invalid_argument("Input is outside of desired range.");
  }
}

/**
 * @brief Normalize color_t values to [0, 1] range.
 * @param color The color input value.
 * @return The normalized floating point value.
 */
constexpr double normalize(color_t color) noexcept {
  return static_cast<double>(color) / MAX;
}

/**
 * @brief Denormalize values back to color_t range.
 * @param normed Normalized value in [0, 1] range.
 * @return Denormalized color_t value.
 */
constexpr color_t denormalize(std::floating_point auto normed) {
  validate_range<0, 1>(normed);
  const auto expanded = std::lround(MAX * normed);
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
