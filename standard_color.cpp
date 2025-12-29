/*
Standard palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#include "standard_color.h"

#include <memory>
using std::make_unique;
using std::unique_ptr;

standard_color::standard_color(palette color_in) : m_color(color_in) {}

color_t standard_color::code() const noexcept { return underlying(m_color); }

unique_ptr<color> standard_color::clone() const {
  return make_unique<standard_color>(*this);
}
