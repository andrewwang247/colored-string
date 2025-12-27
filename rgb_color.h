/*
RGB colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#pragma once
#include "base_color.h"

/**
 * An RGB color in {0,...,5}^3 space.
 */
class rgb_color final : public color {
 private:
  /**
   * Red channel.
   */
  const channel m_red;

  /**
   * Green channel.
   */
  const channel m_green;

  /**
   * Blue channel.
   */
  const channel m_blue;

  /**
   * The number of values possible for a channel.
   */
  static constexpr color_t CHANNEL_END = 6;

  /**
   * Uniformly squeeze the color range.
   *
   * @param original Original color parameter.
   * @return A value uniformly distributed in {0,...,5}.
   */
  static channel squeeze(color_t original) noexcept;

 public:
  rgb_color() = delete;

  /**
   * Explicitly set underlying RGB channels.
   *
   * @param red_in    The red channel.
   * @param green_in  The green channel.
   * @param blue_in   The blue channel.
   */
  explicit rgb_color(channel red_in, channel green_in, channel blue_in);

  /**
   * Explicitly set underlying RGB channels after squeezing.
   *
   * @param red_in    The red channel.
   * @param green_in  The green channel.
   * @param blue_in   The blue channel.
   */
  explicit rgb_color(color_t red_in, color_t green_in, color_t blue_in);

  /**
   * See below.
   *
   * @return The 8-bit ANSI color code.
   */
  color_t code() const noexcept override;

 private:
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  color* clone() const override;
};
