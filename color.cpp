/*
ANSI 8-bit 256 color representations.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2020. Siwei Wang.
*/
#include "color.h"
#include <limits>
using std::numeric_limits;

/* STANDARD COLOR */

standard_color::standard_color(palette color_in) : m_color(color_in) {}

color_t standard_color::get() const { return underlying(m_color); }

/* HIGH INTENSITY COLOR */

high_intensity_color::high_intensity_color(palette color_in)
    : standard_color(color_in) {}

color_t high_intensity_color::get() const {
  constexpr static auto offset = 8;
  return static_cast<color_t>(standard_color::get() + offset);
}

/* RGB COLOR */

rgb_color::rgb_color(color_t red_in, color_t green_in, color_t blue_in)
    : red(squeeze(red_in)), green(squeeze(green_in)), blue(squeeze(blue_in)) {}

color_t rgb_color::squeeze(color_t original) {
  return static_cast<color_t>(original * MAX_DIM /
                              numeric_limits<color_t>::max());
}

color_t rgb_color::get() const {
  constexpr static auto offset = 16;
  return static_cast<color_t>(offset + MAX_DIM * MAX_DIM * red +
                              MAX_DIM * green + blue);
}

/* GREYSCALE COLOR */

greyscale_color::greyscale_color(grey color_in) : m_color(color_in) {}

color_t greyscale_color::get() const {
  constexpr static auto offset = 232;
  return static_cast<color_t>(underlying(m_color) + offset);
}
