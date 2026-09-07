/*
Standard colors.

Copyright 2026. Andrew Wang.
*/
#include "standard_color.h"

#include <memory>

#include "base_color.h"
#include "singular_color.h"

using std::make_unique;
using std::unique_ptr;

standard_color::standard_color(palette palette_in) noexcept
    : singular_color(color_cast(palette_in), standard_color::OFFSET) {}

unique_ptr<color> standard_color::clone() const {
  return make_unique<standard_color>(*this);
}
