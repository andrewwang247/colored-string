/*
Hue Saturation Value

Copyright 2026. Andrew Wang.
*/
#include "hsv_color.h"

#include <algorithm>
#include <cmath>

#include "channel.h"
#include "cylindrical.h"
#include "true_color.h"

using channel::denormalize;
using std::abs;
using std::max;
using std::min;

hsv_color::hsv_color(true_color tc) noexcept : cylindrical(tc) {
  if (chroma == 0.) return;
  saturation = chroma / value;
}

hsv_color::hsv_color(double hue_in, double sat_in, double val_in) noexcept
    : cylindrical(hue_in, sat_in) {
  channel::validate_range<0, 1>(val_in);

  value = val_in;
  chroma = sat_in * val_in;
  lightness = abs(val_in * (1. - sat_in / 2.));
}

true_color hsv_color::to_rgb() const noexcept {
  const auto shape = [this](int n) {
    const auto div = n + hue / 60.;
    const auto k = fmod(div, 6.);
    const auto tri = min({k, 4. - k, 1.});
    return value - value * saturation * max(0., tri);
  };
  return {.red = denormalize(shape(5)),
          .green = denormalize(shape(3)),
          .blue = denormalize(shape(1))};
}
