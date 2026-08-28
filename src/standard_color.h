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
 private:
  static constexpr auto OFFSET = 0;

 public:
  /**
   * @brief Explicitly sets underlying palette color.
   *
   * @param palette_in Input palette.
   */
  explicit standard_color(palette palette_in) noexcept;

  std::unique_ptr<color> clone() const override;
};
