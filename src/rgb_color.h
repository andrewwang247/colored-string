/*
RGB colors.

Copyright 2026. Andrew Wang.
*/
#pragma once

#include <memory>

#include "base_color.h"

/**
 * @brief RGB channel values for ANSI.
 *
 * Higher values correspond to stronger RGB channel input.
 */
enum class channel : color_t { C0, C1, C2, C3, C4, C5, END };

/**
 * @brief Cast to channel type.
 * @param col The color to cast.
 * @return The representative channel value.
 */
constexpr channel channel_cast(color_t col) noexcept {
  return static_cast<channel>(col);
}

/**
 * @brief An RGB color in {0,...,5}^3 space.
 */
class rgb_color final : public color {
 private:
  static constexpr color_t OFFSET{16};
  channel m_red, m_green, m_blue;

 public:
  /**
   * @brief Explicitly set underlying RGB channels.
   * @param red_in    The red channel.
   * @param green_in  The green channel.
   * @param blue_in   The blue channel.
   */
  rgb_color(channel red_in, channel green_in, channel blue_in) noexcept;

  color_t code() const noexcept override;

  std::unique_ptr<color> clone() const override;
};
