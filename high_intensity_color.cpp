/*
High intensity palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "high_intensity_color.h"

high_intensity_color::high_intensity_color(palette color_in)
    : m_color(color_in) {}

color_t high_intensity_color::code() const {
  constexpr static auto offset = 8;
  return static_cast<color_t>(underlying(m_color) + offset);
}

color* high_intensity_color::clone() const {
  return new high_intensity_color(*this);
}
