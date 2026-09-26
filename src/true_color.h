/*
ANSI 24 bit true color.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <compare>
#include <concepts>
#include <cstdint>
#include <limits>
#include <string>
#include <string_view>

namespace channel {
using color_t = std::uint8_t;

static constexpr auto MAX = std::numeric_limits<color_t>::max();

template <typename T>
concept numeric = std::integral<T> || std::floating_point<T>;
}  // namespace channel

/**
 * @brief ANSI 24 bit true color
 */
class true_color {
 public:
  channel::color_t red, green, blue;

  /**
   * @brief Factory from hex code.
   * @param hex_code The hexadecimal string.
   * @return true_color represented by code.
   */
  static true_color from_hex(std::string_view hex_code);

  /**
   * @brief Convert color to hex code.
   * @return Hexadecimal string of this color.
   */
  std::string hex() const;

  /**
   * @brief Get the complement of a color.
   * @return Bitwise inversion of color.
   */
  true_color operator~() const noexcept;

  auto operator<=>(const true_color&) const = default;
};
