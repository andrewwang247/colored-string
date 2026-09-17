/*
Standard colors.

Copyright 2026. Andrew Wang.
*/
#include "standard_color.h"

#include "base_color.h"
#include "singular_color.h"

standard_color::standard_color(palette palette_in) noexcept
    : singular_color(color_cast(palette_in), standard_color::OFFSET) {}
