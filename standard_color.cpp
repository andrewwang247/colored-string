/*
Standard palette colors.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "standard_color.h"

standard_color::standard_color(palette color_in) : m_color(color_in) {}

color_t standard_color::code() const noexcept { return underlying(m_color); }

color* standard_color::clone() const { return new standard_color(*this); }
