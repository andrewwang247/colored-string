/*
Utility functions for colors and numerics.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>

#include "rgb_color.h"

/**
 * @brief Constexpr noexcept utility functions for colors and numerics.
 */
namespace util {

/**
 * @brief Default allowed floating point imprecision.
 */
static constexpr double EPSILON = 1e-4;

/**
 * @brief Normalize specifier values to [0, 1] range.
 * @param cs The enum input value.
 * @return The normalized floating point value.
 */
constexpr double normalize(color_specifier auto cs) noexcept {
  constexpr auto denom = color_cast(decltype(cs)::END) - 1;
  return std::abs(static_cast<double>(cs)) / denom;
}

/**
 * @brief Normalize color values to [0, 1] range.
 * @param color The color input value.
 * @return The normalized floating point value.
 */
constexpr double normalize(color_t color) noexcept {
  constexpr auto denom = std::numeric_limits<color_t>::max();
  return std::abs(static_cast<double>(color)) / denom;
}

/**
 * @brief Denormalize values back to channel range.
 * @param normed Normalized value in [0, 1] range.
 * @return Denormalized channel.
 */
constexpr channel denormalize(double normed) noexcept {
  constexpr auto multiplier = color_cast(channel::END) - 1;
  const auto expanded = std::lround(multiplier * normed);
  return static_cast<channel>(expanded);
}

/**
 * @brief Approximate equality to deal with floating point imprecision.
 * @param lhs Left side to compare.
 * @param rhs Right side to compare.
 * @param epsilon The allowed quantity of imprecision.
 * @return Whether lhs and rhs are within epsilon of each other.
 */
constexpr bool almost_eq(double lhs, double rhs,
                         double epsilon = EPSILON) noexcept {
  return std::abs(lhs - rhs) < epsilon;
}

}  // namespace util
