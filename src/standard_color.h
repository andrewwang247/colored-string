/*
Standard colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include "singular_color.h"

/**
 * @brief A standard palette color.
 */
class standard_color final : public singular_color {
 private:
  static constexpr auto OFFSET = color_t{0};

 public:
  /**
   * @brief Explicitly sets underlying palette color.
   *
   * @param palette_in Input palette.
   */
  explicit standard_color(palette palette_in) noexcept;

  ~standard_color() noexcept override;
};
