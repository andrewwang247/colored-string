/*
Standard palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#pragma once
#include "base_color.h"

/**
 * A standard palette color.
 */
class standard_color final : public color {
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
  color_t code() const noexcept override;

 private:
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  color* clone() const override;
};
