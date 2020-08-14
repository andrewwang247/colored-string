/*
ANSI 8-bit 256 color representation.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#pragma once
#include <type_traits>

/**
 * 8-bit ANSI color type.
 */
using color_t = unsigned char;

/**
 * Convert integer types to color_t.
 *
 * @param arg The input integer.
 * @return A color_t with the same value.
 */
color_t operator"" _c(unsigned long long arg) noexcept;

/**
 * Cast to underlying type.
 *
 * @param item The item to cast.
 * @return The underlying type of item.
 */
template <typename T>
constexpr auto underlying(T item) {
  return static_cast<std::underlying_type_t<T>>(item);
}

/**
 * Standard palette colors.
 */
enum class palette : color_t {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE
};

/**
 * RGB channel values for ANSI.
 */
enum class channel : color_t { C0, C1, C2, C3, C4, C5 };

/**
 * Greyscale colors.
 *
 * Goes from black to white as numbers increase.
 */
enum class grey : color_t {
  G0,
  G1,
  G2,
  G3,
  G4,
  G5,
  G6,
  G7,
  G8,
  G9,
  G10,
  G11,
  G12,
  G13,
  G14,
  G15,
  G16,
  G17,
  G18,
  G19,
  G20,
  G21,
  G22,
  G23
};
