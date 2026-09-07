/*
Bright colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "singular_color.h"

/**
 * @brief A bright palette color.
 */
class bright_color final : public singular_color {
 private:
  static constexpr color_t OFFSET{8};

 public:
  /**
   * @brief Explicitly sets underlying palette color.
   * @param palette_in Input palette.
   */
  explicit bright_color(palette palette_in) noexcept;

  std::unique_ptr<color> clone() const override;
};
