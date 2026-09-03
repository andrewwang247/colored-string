/*
Pure virtual base color interface.

Copyright 2026. Andrew Wang.
*/
#include "base_color.h"

color::color(color_t offset) noexcept : m_offset(offset) {}

color::color(const color& other) noexcept = default;

color& color::operator=(const color& other) noexcept = default;

color::~color() noexcept = default;

singular_color::singular_color(color_t color_in, color_t offset_in) noexcept
    : color(offset_in), m_color(color_in) {}

color_t singular_color::code() const noexcept { return m_color + m_offset; }
