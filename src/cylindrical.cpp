/*
Cylindrical coordinate color representation.

Copyright 2026. Andrew Wang.
*/
#include "cylindrical.h"

#include <algorithm>
#include <cmath>
#include <compare>
#include <iterator>
#include <utility>

#include "channel.h"
#include "true_color.h"

using std::abs;
using std::fmod;
using std::max;
using std::min;

using channel::almost_eq;

namespace ranges = std::ranges;

cylindrical::cylindrical(true_color tc) noexcept {
  const auto red = channel::normalize(tc.red);
  const auto green = channel::normalize(tc.green);
  const auto blue = channel::normalize(tc.blue);
  const auto rgb_list = {red, green, blue};

  const auto x_max = max(rgb_list);
  const auto x_min = min(rgb_list);

  value = x_max;
  chroma = x_max - x_min;
  lightness = (x_min + x_max) / 2.;

  if (chroma == 0.) return;

  const auto* const max_iter = ranges::max_element(rgb_list);
  const auto var_argmax = ranges::distance(rgb_list.begin(), max_iter);

  switch (var_argmax) {
    case 0:  // red
      hue = fmod((green - blue) / chroma, 6.);
      hue += hue < 0. ? 6. : 0.;
      break;
    case 1:  // green
      hue = 2. + (blue - red) / chroma;
      break;
    case 2:  // blue
      hue = 4. + (red - green) / chroma;
      break;
    default:
      std::unreachable();
  }
  hue = 60 * abs(hue);
}

cylindrical::cylindrical(double hue_in, double sat_in) noexcept
    : hue(hue_in), saturation(sat_in) {
  channel::validate_range<0, 360>(hue_in);
  channel::validate_range<0, 1>(sat_in);
}

bool operator==(const cylindrical& lhs, const cylindrical& rhs) noexcept {
  return almost_eq(lhs.hue, rhs.hue) && almost_eq(lhs.chroma, rhs.chroma) &&
         almost_eq(lhs.value, rhs.value) &&
         almost_eq(lhs.lightness, rhs.lightness);
}

std::partial_ordering operator<=>(const cylindrical& lhs,
                                  const cylindrical& rhs) noexcept {
  if (!channel::almost_eq(lhs.lightness, rhs.lightness)) {
    return lhs.lightness <=> rhs.lightness;
  }
  if (!channel::almost_eq(lhs.hue, rhs.hue)) {
    return lhs.hue <=> rhs.hue;
  }
  if (!channel::almost_eq(lhs.chroma, rhs.chroma)) {
    return lhs.chroma <=> rhs.chroma;
  }
  return lhs.value <=> rhs.value;
}

cylindrical::~cylindrical() = default;
