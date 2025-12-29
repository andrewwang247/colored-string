/*
Greyscale colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * Greyscale colors.
 *
 * Goes from black to white as numbers increase.
 */
enum class grey : color_t {
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
  G23
};

/**
 * A greyscale color taking on 24 possible values.
 */
class greyscale_color final : public singular_color {
 public:
  greyscale_color() = delete;

  /**
   * Explicitly sets underlying grey color.
   *
   * @param color_in Input color.
   */
  explicit greyscale_color(grey color_in);

 private:
  static constexpr auto OFFSET = 232;
  /**
   * Polymorphic cloning.
   *
   * @return A new copy of the color.
   */
  std::unique_ptr<color> clone() const override;
};
