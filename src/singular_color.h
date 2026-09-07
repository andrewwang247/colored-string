/*
Singular colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include "base_color.h"

/**
 * @brief Standard palette colors.
 */
enum class palette : color_t {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,

  END
};

/**
 * @brief Cast to palette type.
 * @param col The color to cast.
 * @return The representative palette value.
 */
constexpr palette palette_cast(color_t col) noexcept {
  return static_cast<palette>(col);
}

/**
 * @brief Colors that are canonically described by a single value.
 */
class singular_color : public color {
 protected:
  color_t m_color;

  /**
   * @brief Argument constructor.
   * @param color_in The underlying color.
   * @param offset_in The ANSI code offset.
   */
  singular_color(color_t color_in, color_t offset_in) noexcept;

 public:
  color_t code() const noexcept override;
};
