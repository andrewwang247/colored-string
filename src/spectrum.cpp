/*
Operations for drawing rainbows.

Copyright 2026. Andrew Wang.
*/
#include "spectrum.h"

#include "hsvl.h"
#include "util.h"

bool rainbow::operator()(const cylindrical& lhs, const cylindrical& rhs) const {
  if (!util::almost_eq(lhs.lightness(), rhs.lightness())) {
    return lhs.lightness() < rhs.lightness();
  }
  if (!util::almost_eq(lhs.hue(), rhs.hue())) {
    return lhs.hue() < rhs.hue();
  }
  if (!util::almost_eq(lhs.chroma(), rhs.chroma())) {
    return lhs.chroma() < rhs.chroma();
  }
  if (!util::almost_eq(lhs.value(), rhs.value())) {
    return lhs.value() < rhs.value();
  }
  return lhs.saturation() < rhs.saturation();
}
