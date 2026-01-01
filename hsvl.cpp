/*
Cylindrical coordinate color repsentations.

Copyright 2026. Andrew Wang.
*/
#include "hsvl.h"

#include <algorithm>
#include <cmath>

#include "util.h"

using std::abs;
using std::min;

cylindrical::cylindrical()
    : m_hue(0.), m_chroma(0.), m_saturation(0.), m_value(0.), m_lightness(0.) {}

cylindrical::cylindrical(channel red, channel green, channel blue)
    : cylindrical() {
  generic_construct(red, green, blue);
}

cylindrical::cylindrical(color_t red, color_t green, color_t blue)
    : cylindrical() {
  generic_construct(red, green, blue);
}

double cylindrical::hue() const noexcept { return m_hue; }
double cylindrical::chroma() const noexcept { return m_chroma; }
double cylindrical::saturation() const noexcept { return m_saturation; }
double cylindrical::value() const noexcept { return m_value; }
double cylindrical::lightness() const noexcept { return m_lightness; }

hsv::hsv() : cylindrical() {}

hsv::hsv(channel red, channel green, channel blue)
    : cylindrical(red, green, blue) {
  set_saturation();
}

hsv::hsv(color_t red, color_t green, color_t blue)
    : cylindrical(red, green, blue) {
  set_saturation();
}

void hsv::set_saturation() {
  if (util::almost_eq(m_chroma, 0.)) return;
  m_saturation = abs(m_chroma / m_value);
}

hsl::hsl() : cylindrical() {}

hsl::hsl(channel red, channel green, channel blue)
    : cylindrical(red, green, blue) {
  set_saturation();
}

hsl::hsl(color_t red, color_t green, color_t blue)
    : cylindrical(red, green, blue) {
  set_saturation();
}

void hsl::set_saturation() {
  if (util::almost_eq(m_lightness, 0.) || util::almost_eq(m_lightness, 1.))
    return;
  m_saturation =
      abs((m_value - m_lightness) / min(m_lightness, 1. - m_lightness));
}
