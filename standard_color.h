/*
Standard colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * A standard palette color.
 */
class standard_color final : public singular_color {
 public:
  standard_color() = default;

  /**
   * Explicitly sets underlying palette color.
   *
   * @param palette_in Input palette.
   */
  explicit standard_color(palette palette_in);

 private:
  static constexpr auto OFFSET = 0;
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  std::unique_ptr<color> clone() const override;
};
