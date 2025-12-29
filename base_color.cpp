/*
Pure virtual base color interface.

Copyright 2026. Andrew Wang.
*/
#include "base_color.h"

color::color(int offset) : m_offset(offset) {}

singular_color::singular_color(color_t color_in, int offset_in)
    : color(offset_in), m_color(color_in) {}

color_t singular_color::code() const {
  return static_cast<color_t>(m_color + m_offset);
}
