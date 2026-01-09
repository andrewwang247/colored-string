/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#include "spectrum.h"

#include "colored_string.h"
#include "hsvl.h"
#include "rgb_color.h"

bool rainbow::operator()(const cylindrical& lhs, const cylindrical& rhs) const {
  if (!util::almost_eq(lhs.lightness(), rhs.lightness())) {
    return lhs.lightness() < rhs.lightness();

  } else if (!util::almost_eq(lhs.hue(), rhs.hue())) {
    return lhs.hue() < rhs.hue();

  } else if (!util::almost_eq(lhs.chroma(), rhs.chroma())) {
    return lhs.chroma() < rhs.chroma();

  } else if (!util::almost_eq(lhs.value(), rhs.value())) {
    return lhs.value() < rhs.value();

  } else {
    return lhs.saturation() < rhs.saturation();
  }
}
