/*
Greyscale colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#pragma once
#include "base_color.h"

/**
 * A greyscale color taking on 24 possible values.
 */
class greyscale_color final : public color {
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
  color_t code() const noexcept override;

 private:
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  color* clone() const override;
};
