/*
Abstract base colors.

Copyright 2026. Andrew Wang.
*/
#include "base_color.h"

#include <compare>

using std::strong_ordering;

color::color(color_t offset) noexcept : m_offset(offset) {}

strong_ordering color::compare(const color& other) const noexcept {
  return code() <=> other.code();
}

bool operator==(const color& lhs, const color& rhs) noexcept {
  return lhs.code() == rhs.code();
}

strong_ordering operator<=>(const color& lhs, const color& rhs) noexcept {
  return lhs.compare(rhs);
}
