/*
RGB colors.

Copyright 2026. Andrew Wang.
*/
#include "rgb_color.h"

#include <memory>

#include "base_color.h"

using std::make_unique;
using std::unique_ptr;

rgb_color::rgb_color(channel red_in, channel green_in, channel blue_in) noexcept
    : color(rgb_color::OFFSET),
      m_red(red_in),
      m_green(green_in),
      m_blue(blue_in) {}

color_t rgb_color::code() const noexcept {
  constexpr auto channel_max = color_cast(channel::END);
  const auto red = channel_max * channel_max * color_cast(m_red);
  const auto green = channel_max * color_cast(m_green);
  const auto blue = color_cast(m_blue);
  return static_cast<color_t>(red + green + blue + m_offset);
}

unique_ptr<color> rgb_color::clone() const {
  return make_unique<rgb_color>(*this);
}
