/*
Grayscale colors.

Copyright 2026. Andrew Wang.
*/
#include "grayscale_color.h"

#include "base_color.h"
#include "singular_color.h"

grayscale_color::grayscale_color(gray gray_in) noexcept
    : singular_color(color_cast(gray_in), grayscale_color::OFFSET) {}
