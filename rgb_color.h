/*
RGB colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#pragma once
#include "base_color.h"

/**
 * An RGB color in {0,...,5}^3 space.
 */
class rgb_color : public color {
 private:
  /**
   * Red channel.
   */
  const color_t m_red;

  /**
   * Green channel.
   */
  const color_t m_green;

  /**
   * Blue channel.
   */
  const color_t m_blue;

  /**
   * The number of values possible for a channel.
   */
  constexpr static color_t CHANNEL_END = 6;

  /**
   * Uniformly squeeze the color range.
   *
   * @param original Original color parameter.
   * @return A value uniformly distributed in {0,...,5}.
   */
  static color_t squeeze(color_t original) noexcept;

 public:
  rgb_color() = delete;

  /**
   * Explicitly set underlying RGB channels after squeezing.
   * If convert is false: inputs take values in {0,...,5}.
   * If convert is true: inputs may be any color_t value.
   *
   * @param red_in    The red channel.
   * @param green_in  The green channel.
   * @param blue_in   The blue channel.
   * @param convert   Conversion flag from true RGB.
   */
  explicit rgb_color(color_t red_in, color_t green_in, color_t blue_in,
                     bool convert = true);

  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t code() const override;

 private:
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  color* clone() const override;
};
