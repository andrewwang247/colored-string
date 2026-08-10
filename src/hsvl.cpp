/*
Cylindrical coordinate color repsentations.

Copyright 2026. Andrew Wang.
*/
#include "hsvl.h"

#include <algorithm>
#include <cmath>

#include "base_color.h"
#include "rgb_color.h"
#include "util.h"

cylindrical::cylindrical(channel red, channel green, channel blue) {
  generic_construct(red, green, blue);
}

cylindrical::cylindrical(color_t red, color_t green, color_t blue) {
  generic_construct(red, green, blue);
}

double cylindrical::hue() const noexcept { return m_hue; }
double cylindrical::chroma() const noexcept { return m_chroma; }
double cylindrical::saturation() const noexcept { return m_saturation; }
double cylindrical::value() const noexcept { return m_value; }
double cylindrical::lightness() const noexcept { return m_lightness; }

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
  m_saturation = std::abs(m_chroma / m_value);
}

rgb_color hsv::to_rgb() const {
  static const auto shape = [this](int n) constexpr {
    const auto div = n + m_hue / 60.;
    const auto k = std::fmod(div, 6.);
    const auto tri = std::min({k, 4. - k, 1.});
    return m_value - m_value * m_saturation * std::max(0., tri);
  };
  const auto r = util::denormalize(shape(5));
  const auto g = util::denormalize(shape(3));
  const auto b = util::denormalize(shape(1));
  return rgb_color{r, g, b};
}

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
  m_saturation = std::abs((m_value - m_lightness) /
                          std::min(m_lightness, 1. - m_lightness));
}

rgb_color hsl::to_rgb() const {
  static const auto shape = [this](int n) constexpr {
    const auto div = n + m_hue / 30.;
    const auto k = std::fmod(div, 12.);
    const auto a = m_saturation * std::min(m_lightness, 1 - m_lightness);
    const auto tri = std::min({k - 3., 9. - k, 1.});
    return m_lightness - a * std::max(-1., tri);
  };
  const auto r = util::denormalize(shape(0));
  const auto g = util::denormalize(shape(8));
  const auto b = util::denormalize(shape(4));
  return rgb_color{r, g, b};
}
