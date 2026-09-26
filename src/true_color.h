/*
ANSI 24 bit true color.

Copyright 2026. Andrew Wang.
*/
#pragma once
#include <compare>
#include <cstdint>

using color_t = std::uint8_t;

/**
 * @brief ANSI 24 bit true color
 */
struct true_color {
  color_t red, green, blue;

  auto operator<=>(const true_color&) const = default;
};
