/*
Cylindrical coordinate color representation.

Copyright 2026. Andrew Wang.
*/
#include "hsvl.h"

#include <algorithm>
#include <cmath>

#include "base_color.h"
#include "rgb_color.h"
#include "util.h"

using std::abs;
using std::fmod;
using std::max;
using std::min;

using util::almost_eq;
using util::denormalize;

cylindrical::cylindrical(channel red, channel green, channel blue) noexcept {
  generic_construct(red, green, blue);
}

cylindrical::cylindrical(color_t red, color_t green, color_t blue) noexcept {
  generic_construct(red, green, blue);
}

hsv::hsv(channel red, channel green, channel blue) noexcept
    : cylindrical(red, green, blue) {
  set_saturation();
}

hsv::hsv(color_t red, color_t green, color_t blue) noexcept
    : cylindrical(red, green, blue) {
  set_saturation();
}

void hsv::set_saturation() noexcept {
  if (almost_eq(m_chroma, 0.)) return;
  m_saturation = abs(m_chroma / m_value);
}

rgb_color hsv::to_rgb() const noexcept {
  static const auto shape = [this](int n) constexpr {
    const auto div = n + m_hue / 60.;
    const auto k = fmod(div, 6.);
    const auto tri = min({k, 4. - k, 1.});
    return m_value - m_value * m_saturation * max(0., tri);
  };
  const auto r = denormalize(shape(5));
  const auto g = denormalize(shape(3));
  const auto b = denormalize(shape(1));
  return rgb_color{r, g, b};
}

hsl::hsl(channel red, channel green, channel blue) noexcept
    : cylindrical(red, green, blue) {
  set_saturation();
}

hsl::hsl(color_t red, color_t green, color_t blue) noexcept
    : cylindrical(red, green, blue) {
  set_saturation();
}

void hsl::set_saturation() noexcept {
  if (almost_eq(m_lightness, 0.) || almost_eq(m_lightness, 1.)) return;
  m_saturation =
      abs((m_value - m_lightness) / min(m_lightness, 1. - m_lightness));
}

rgb_color hsl::to_rgb() const noexcept {
  static const auto shape = [this](int n) constexpr {
    const auto div = n + m_hue / 30.;
    const auto k = fmod(div, 12.);
    const auto a = m_saturation * min(m_lightness, 1 - m_lightness);
    const auto tri = min({k - 3., 9. - k, 1.});
    return m_lightness - a * max(-1., tri);
  };
  const auto r = denormalize(shape(0));
  const auto g = denormalize(shape(8));
  const auto b = denormalize(shape(4));
  return rgb_color{r, g, b};
}
