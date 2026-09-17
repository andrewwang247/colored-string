/*
Abstract base colors.

Copyright 2026. Andrew Wang.
*/
#include "base_color.h"

color::color(color_t offset) noexcept : m_offset(offset) {}

bool operator==(const color& lhs, const color& rhs) noexcept {
  return lhs.code() == rhs.code();
}
