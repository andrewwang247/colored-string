/*
Grayscale colors.

Copyright 2026. Andrew Wang.
*/
#include "grayscale_color.h"

#include <memory>

using std::make_unique;
using std::unique_ptr;

grayscale_color::grayscale_color(gray gray_in)
    : singular_color(color_cast(gray_in), grayscale_color::OFFSET) {}

unique_ptr<color> grayscale_color::clone() const {
  return make_unique<grayscale_color>(*this);
}
