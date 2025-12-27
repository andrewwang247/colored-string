/*
ANSI 8-bit 256 color representations.
See https://en.wikipedia.org/wiki/ANSI_escape_code#8-bit

Copyright 2026. Andrew Wang.
*/
#include "color.h"

color_t operator"" _c(unsigned long long arg) noexcept {
  return static_cast<color_t>(arg);
}
