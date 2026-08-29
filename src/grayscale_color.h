/*
Grayscale colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * @brief Grayscale colors.
 *
 * Goes from black to white as numbers increase.
 */
enum class gray : color_t {
  G0,
  G1,
  G2,
  G3,
  G4,
  G5,
  G6,
  G7,
  G8,
  G9,
  G10,
  G11,
  G12,
  G13,
  G14,
  G15,
  G16,
  G17,
  G18,
  G19,
  G20,
  G21,
  G22,
  G23,

  END
};

/**
 * @brief A grayscale color taking on 24 possible values.
 */
class grayscale_color final : public singular_color {
 private:
  static constexpr auto OFFSET = 232;

 public:
  /**
   * @brief Explicitly sets underlying gray color.
   * @param color_in Input gray scale indicator.
   */
  explicit grayscale_color(gray gray_in) noexcept;

  std::unique_ptr<color> clone() const override;
};
