/*
Singular colors.

Copyright 2026. Andrew Wang.
*/
#include "singular_color.h"

#include "base_color.h"

singular_color::singular_color(color_t color_in, color_t offset_in) noexcept
    : color(offset_in), m_color(color_in) {}

color_t singular_color::code() const noexcept { return m_color + m_offset; }
