/*
ANSI 8-bit 256 color representations.
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
constexpr color_t operator"" _c(unsigned long long arg) noexcept {
  return static_cast<color_t>(arg);
}

/**
 * Cast to underlying type.
 *
 * @param obj The object to cast.
 * @return Underlying type of obj.
 */
template <typename T>
constexpr auto underlying(T obj) {
  return static_cast<std::underlying_type_t<T>>(obj);
}

/**
 * Abstract interface for all color types.
 */
class color {
 public:
  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  virtual color_t get() const = 0;
};

/**
 * Standard color palette.
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
 * A standard palette color.
 */
class standard_color : color {
 private:
  /**
   * The underlying palette color.
   */
  const palette m_color;

 public:
  standard_color() = delete;

  /**
   * Explicitly sets underlying palette color.
   *
   * @param color_in Input color.
   */
  explicit standard_color(palette color_in);

  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t get() const override;
};

/**
 * A high intensity palette color.
 */
class high_intensity_color : standard_color {
 public:
  high_intensity_color() = delete;

  /**
   * Explicitly sets underlying palette color.
   *
   * @param color_in Input color.
   */
  explicit high_intensity_color(palette color_in);

  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t get() const override;
};

/**
 * An RGB color in {0,...,5}^3 space.
 */
class rgb_color : color {
 private:
  /**
   * Red channel.
   */
  const color_t red;

  /**
   * Green channel.
   */
  const color_t green;

  /**
   * Blue channel.
   */
  const color_t blue;

  /**
   * The highest parameter value possible for a channel upon output.
   */
  constexpr static int MAX_DIM = 6;

  /**
   * Uniformly squeeze the color range.
   *
   * @param original Can take on values in {0,...,255}.
   * @return A value uniformly distributed in {0,...,5}.
   */
  static color_t squeeze(color_t original);

 public:
  rgb_color() = delete;

  /**
   * Explicitly set underlying RGB channels after squeezing.
   * Inputs take values in {0,...,255}.
   *
   * @param red_in    The red channel.
   * @param green_in  The green channel.
   * @param blue_in   The blue channel.
   */
  rgb_color(color_t red_in, color_t green_in, color_t blue_in);

  /**
   * Converts standard 256^3 RGB channels into 6^3 channels.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t get() const override;
};

/**
 * Standard greyscale palette.
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

class greyscale_color : public color {
 private:
  /**
   * The underlying grey color.
   */
  const grey m_color;

 public:
  greyscale_color() = delete;

  /**
   * Explicitly sets underlying grey color.
   *
   * @param color_in Input color.
   */
  explicit greyscale_color(grey color_in);

  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t get() const override;
};
