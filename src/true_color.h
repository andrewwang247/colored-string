/*
ANSI 24 bit true color.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <compare>
#include <cstdint>
#include <string>
#include <string_view>

using color_t = std::uint8_t;

/**
 * @brief ANSI 24 bit true color
 */
class true_color {
 public:
  color_t red, green, blue;

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

  auto operator<=>(const true_color&) const = default;
};
