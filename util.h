/*
Utility functions for colors and numerics.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <initializer_list>

#include "rgb_color.h"

namespace util {
/**
 * Normalize channel values to [0, 1] range.
 * @param ch The channel input value.
 * @return The normalized floating point value.
 */
double normalize(channel ch) noexcept;

/**
 * Normalize color values to [0, 1] range.
 * @param color The color input value.
 * @return The normalized floating point value.
 */
double normalize(color_t color) noexcept;

/**
 * Approximate equality to deal with floating point imprecision.
 * @param lhs Left side to compare.
 * @param rhs Right side to compare.
 * @param epsilon The allowed quantity of imprecision.
 * @return Whether lhs and rhs are within epsilon of each other.
 */
bool almost_eq(double lhs, double rhs, double epsilon = 1e-4) noexcept;

/**
 * Approximate comparison to deal with floating point imprecision.
 * @param lhs Left side to compare.
 * @param rhs Right side to compare.
 * @param epsilon The allowed quantity of imprecision.
 * @return Whether lhs is more than epsilon less than rhs.
 */
bool almost_less(double lhs, double rhs, double epsilon = 1e-4) noexcept;

/**
 * Variadic argmax over arbitrary arguments.
 * @param args The values to compute argmax over.
 * @return The index to the maximum.
 */
template <typename T>
ptrdiff_t var_argmax(std::initializer_list<T> args);
}  // namespace util

// TEMPLATED IMPLEMENTATIONS

template <typename T>
ptrdiff_t util::var_argmax(std::initializer_list<T> args) {
  const auto idx_max{std::max_element(args.begin(), args.end())};
  return idx_max - args.begin();
}
