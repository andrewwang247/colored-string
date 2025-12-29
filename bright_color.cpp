/*
Bright colors.

Copyright 2026. Andrew Wang.
*/
#include "bright_color.h"

#include <memory>

using std::make_unique;
using std::unique_ptr;

bright_color::bright_color(palette color_in)
    : singular_color(static_cast<color_t>(color_in), bright_color::OFFSET) {}

unique_ptr<color> bright_color::clone() const {
  return make_unique<bright_color>(*this);
}
