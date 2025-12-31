/*
Greyscale colors.

Copyright 2026. Andrew Wang.
*/
#include "greyscale_color.h"

#include <memory>

using std::make_unique;
using std::unique_ptr;

greyscale_color::greyscale_color(grey grey_in)
    : singular_color(color_cast(grey_in), greyscale_color::OFFSET) {}

unique_ptr<color> greyscale_color::clone() const {
  return make_unique<greyscale_color>(*this);
}
