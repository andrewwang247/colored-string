/*
Bright palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * A bright palette color.
 */
class bright_color final : public color {
 private:
  /**
   * The underlying palette color.
   */
  const palette m_color;

 public:
  bright_color() = delete;

  /**
   * Explicitly sets underlying palette color.
   *
   * @param color_in Input color.
   */
  explicit bright_color(palette color_in);

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
  std::unique_ptr<color> clone() const override;
};
