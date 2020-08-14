/*
Greyscale colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "greyscale_color.h"

greyscale_color::greyscale_color(grey color_in) : m_color(color_in) {}

color_t greyscale_color::code() const {
  constexpr static auto offset = 232;
  return static_cast<color_t>(static_cast<color_t>(m_color) + offset);
}

color* greyscale_color::clone() const { return new greyscale_color(*this); }
