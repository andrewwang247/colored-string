/*
RGB colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "rgb_color.h"
#include <stdexcept>
using std::range_error;

color_t rgb_color::squeeze(color_t original) noexcept {
  return static_cast<color_t>(original * rgb_color::CHANNEL_END / 256);
}

rgb_color::rgb_color(color_t red_in, color_t green_in, color_t blue_in,
                     bool convert)
    : m_red(convert ? squeeze(red_in) : red_in),
      m_green(convert ? squeeze(green_in) : green_in),
      m_blue(convert ? squeeze(blue_in) : blue_in) {
  if (convert) return;
  if (!(m_red < CHANNEL_END && m_green < CHANNEL_END && m_blue < CHANNEL_END)) {
    throw std::range_error("RGB channel value(s) is/are out of range.");
  }
}

color_t rgb_color::code() const {
  constexpr static auto offset = 16;
  return static_cast<color_t>(offset + CHANNEL_END * CHANNEL_END * m_red +
                              CHANNEL_END * m_green + m_blue);
}

color* rgb_color::clone() const { return new rgb_color(*this); }
