/*
High intensity palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#include "bright_color.h"

#include <memory>
using std::make_unique;
using std::unique_ptr;

bright_color::bright_color(palette color_in) : m_color(color_in) {}

color_t bright_color::code() const noexcept {
  static constexpr auto offset = 8;
  return static_cast<color_t>(underlying(m_color) + offset);
}

unique_ptr<color> bright_color::clone() const {
  return make_unique<bright_color>(*this);
}
