/*
Bright colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * A bright palette color.
 */
class bright_color final : public singular_color {
 public:
  bright_color() = default;

  /**
   * Explicitly sets underlying palette color.
   *
   * @param color_in Input color.
   */
  explicit bright_color(palette color_in);

 private:
  static constexpr auto OFFSET = 8;
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  std::unique_ptr<color> clone() const override;
};
