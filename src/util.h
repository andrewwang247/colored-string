/*
Utility functions for colors and numerics.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <functional>
#include <limits>
#include <ranges>
#include <string_view>
#include <system_error>

#include "rgb_color.h"

/**
 * @brief Constexpr noexcept utility functions for colors and numerics.
 */
namespace util {

/**
 * @brief Default allowed floating point imprecision.
 */
static constexpr auto EPSILON = 1e-4;

/**
 * @brief Number of digits required to represent color_t as base 10 string.
 */
static constexpr auto COLOR_DIGITS = std::numeric_limits<color_t>::digits10 + 1;

using col_str_buffer = std::array<char, COLOR_DIGITS>;

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

/**
 * @brief Convert a color to its base 10 string representation.
 * @param buffer The array to write characters to.
 * @param col The color to convert into its string representation.
 * @return A string_view backed by buffer of the produced string.
 * @throws system_error if color could not be converted to chars.
 */
constexpr std::string_view color_to_str(col_str_buffer& buffer, color_t col) {
  const auto [ptr, ec] = std::to_chars(buffer.begin(), buffer.end(), col);
  if (ec != std::errc{}) {
    throw std::system_error(std::make_error_code(ec),
                            "Could not convert color to chars");
  }
  return {buffer.begin(), ptr};
}

template <typename Comp, typename Proj>
bool is_strictly_monotonic(std::ranges::random_access_range auto&& items,
                           Comp comp, Proj proj) {
  return std::ranges::adjacent_find(items, comp, proj) == items.end();
}

/**
 * @brief Validate that a range is sorted and strictly increasing.
 * @param items The range to validate.
 * @param proj Optional projection for items in range.
 * @return Whether proj(items[i]) < proj(items[j]) whenever i < j.
 */
template <typename Proj = std::identity>
bool is_strictly_ascending(std::ranges::random_access_range auto&& items,
                           Proj proj = {}) {
  return is_strictly_monotonic(items, std::ranges::greater_equal{}, proj);
}

/**
 * @brief Validate that a range is sorted and strictly decreasing.
 * @param items The range to validate.
 * @param proj Optional projection for items in range.
 * @return Whether proj(items[i]) > proj(items[j]) whenever i < j.
 */
template <typename Proj = std::identity>
bool is_strictly_descending(std::ranges::random_access_range auto&& items,
                            Proj proj = {}) {
  return is_strictly_monotonic(items, std::ranges::less_equal{}, proj);
}

}  // namespace util
