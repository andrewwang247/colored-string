/*
Hue Saturation Lightness

Copyright 2026. Andrew Wang.
*/
#include "hsl_color.h"

#include <algorithm>
#include <cmath>

#include "channel.h"
#include "cylindrical.h"
#include "true_color.h"

using channel::denormalize;
using std::abs;
using std::fmod;
using std::max;
using std::min;

hsl_color::hsl_color(true_color tc) noexcept : cylindrical(tc) {
  if (lightness == 0. || lightness == 1.) return;
  saturation = (value - lightness) / min(lightness, 1. - lightness);
}

hsl_color::hsl_color(double hue_in, double sat_in, double light_in) noexcept
    : cylindrical(hue_in, sat_in) {
  channel::validate_range<0, 1>(light_in);

  lightness = light_in;
  chroma = sat_in * (1. - abs(2 * light_in - 1));
  value = light_in + sat_in * min(light_in, 1. - light_in);
}

true_color hsl_color::to_rgb() const noexcept {
  const auto shape = [this](int n) {
    const auto div = n + hue / 30.;
    const auto k = fmod(div, 12.);
    const auto a = saturation * min(lightness, 1. - lightness);
    const auto tri = min({k - 3., 9. - k, 1.});
    return lightness - a * max(-1., tri);
  };
  return {.red = denormalize(shape(0)),
          .green = denormalize(shape(8)),
          .blue = denormalize(shape(4))};
}
