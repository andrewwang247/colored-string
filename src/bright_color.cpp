/*
Bright colors.

Copyright 2026. Andrew Wang.
*/
#include "bright_color.h"

#include "base_color.h"
#include "singular_color.h"

bright_color::bright_color(palette palette_in) noexcept
    : singular_color(color_cast(palette_in), bright_color::OFFSET) {}
