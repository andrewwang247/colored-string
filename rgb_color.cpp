/*
RGB colors.

Copyright 2026. Andrew Wang.
*/
#include "rgb_color.h"

#include <memory>

using std::make_unique;
using std::unique_ptr;

channel rgb_color::squeeze(color_t original) noexcept {
  return static_cast<channel>(original * RGB_CHANNELS / 256);
}

rgb_color::rgb_color(channel red_in, channel green_in, channel blue_in)
    : color(rgb_color::OFFSET),
      m_red(red_in),
      m_green(green_in),
      m_blue(blue_in) {}

rgb_color::rgb_color(color_t red_in, color_t green_in, color_t blue_in)
    : color(rgb_color::OFFSET),
      m_red(squeeze(red_in)),
      m_green(squeeze(green_in)),
      m_blue(squeeze(blue_in)) {}

color_t rgb_color::code() const {
  const auto red = RGB_CHANNELS * RGB_CHANNELS * static_cast<color_t>(m_red);
  const auto green = RGB_CHANNELS * static_cast<color_t>(m_green);
  const auto blue = static_cast<color_t>(m_blue);
  return static_cast<color_t>(m_offset + red + green + blue);
}

unique_ptr<color> rgb_color::clone() const {
  return make_unique<rgb_color>(*this);
}
